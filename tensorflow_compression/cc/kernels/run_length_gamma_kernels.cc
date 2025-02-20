/* Copyright 2022 Google LLC. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#define EIGEN_USE_THREADS

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>
#include <vector>

#include "absl/types/span.h"
#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/tensor_types.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/status.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/macros.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow_compression/cc/lib/bit_coder.h"

namespace tensorflow_compression {
namespace {
namespace errors = tensorflow::errors;
using tensorflow::DEVICE_CPU;
using tensorflow::OpKernel;
using tensorflow::OpKernelConstruction;
using tensorflow::OpKernelContext;
using tensorflow::string;
using tensorflow::Tensor;
using tensorflow::TensorShape;
using tensorflow::TensorShapeUtils;
using tensorflow::tstring;

class RunLengthGammaEncodeOp : public OpKernel {
 public:
  explicit RunLengthGammaEncodeOp(OpKernelConstruction* context)
      : OpKernel(context) {}

  void Compute(OpKernelContext* context) override {
    const Tensor& data_tensor = context->input(0);
    auto data = data_tensor.flat<int32_t>();

    Tensor* code_tensor;
    OP_REQUIRES_OK(context,
                   context->allocate_output(0, TensorShape{}, &code_tensor));
    tstring* code = &code_tensor->scalar<tstring>()();

    // Initialize bit encoder and ensure it allocates more than enough bits.
    // The maximum code length is achieved when there are no zeros in the input
    // array. The encoded size of each value is 2 + kMaxGammaBits (1 bit for
    // no leading zeros, 1 bit for sign and kMaxGammaBits for magnitude). If
    // any zeros were present in the input array, then the encoded size would be
    // strictly smaller by kMaxGammaBits and bigger by the difference in
    // encoding (the existing zero run length + 1).
    BitWriter enc;
    enc.Allocate(data.size() * (2 + enc.kMaxGammaBits));
    // Save number of zeros + 1 preceding next non-zero element.
    uint32_t zero_ct = 1;

    // Iterate through data tensor.
    for (size_t i = 0; i < data.size(); i++) {
      // Increment zero count.
      if (data(i) == 0) {
        zero_ct += 1;
      } else {
        // Encode run length of zeros.
        enc.WriteGamma(zero_ct);
        // Encode sign of value.
        enc.WriteOneBit(data(i) > 0);
        // Encode magnitude of value.
        DCHECK_NE(data(i), std::numeric_limits<int32_t>::min());
        enc.WriteGamma(std::abs(data(i)));
        // Reset zero count (1 because Gamma cannot encode 0).
        zero_ct = 1;
      }
    }
    if (zero_ct > 1) {
      enc.WriteGamma(zero_ct);
    }

    // Pad any remaining bits in last byte with 0.
    enc.ZeroPadToByte();
    // Write encoded bitstring to code.
    code->assign(enc.GetData(), enc.GetBytesWritten());
  }
};

REGISTER_KERNEL_BUILDER(Name("RunLengthGammaEncode").Device(DEVICE_CPU),
                        RunLengthGammaEncodeOp);

class RunLengthGammaDecodeOp : public OpKernel {
 public:
  explicit RunLengthGammaDecodeOp(OpKernelConstruction* context)
      : OpKernel(context) {}

  void Compute(OpKernelContext* context) override {
    const Tensor& code_tensor = context->input(0);
    const Tensor& shape_tensor = context->input(1);

    OP_REQUIRES(
        context, TensorShapeUtils::IsScalar(code_tensor.shape()),
        errors::InvalidArgument("Invalid `code` shape: ", code_tensor.shape()));
    OP_REQUIRES(context, TensorShapeUtils::IsVector(shape_tensor.shape()),
                errors::InvalidArgument("Invalid `shape` shape: ",
                                        shape_tensor.shape()));

    const tstring& code = code_tensor.scalar<tstring>()();

    TensorShape data_shape;
    OP_REQUIRES_OK(context, TensorShapeUtils::MakeShape(
                                shape_tensor.vec<int32_t>(), &data_shape));
    Tensor* data_tensor;
    OP_REQUIRES_OK(context,
                   context->allocate_output(0, data_shape, &data_tensor));
    auto data = data_tensor->flat<int32_t>();

    // Initialize bit decoder to point at the code and expect code size bytes.
    BitReader dec(code);

    // Fill data tensor with zeros.
    std::memset(data.data(), 0, data.size() * sizeof(data(0)));

    for (size_t i = 0; i < data.size(); i++) {
      // Get number of zeros.
      uint32_t num_zeros = dec.ReadGamma();
      // Advance the index to the next non-zero element.
      i += num_zeros - 1;

      // Account for case where the last element is zero.
      if (i == data.size()) {
        break;
      }
      // TODO(nicolemitchell): return error status instead of crashing
      DCHECK_LT(i, data.size());

      // Get sign of value.
      uint32_t positive = dec.ReadOneBit();

      // Get value.
      uint32_t value = dec.ReadGamma();

      // Write value to data tensor element at index.
      DCHECK_LE(value, std::numeric_limits<int32_t>::max());
      data(i) = positive ? value : -static_cast<int32_t>(value);
    }

    OP_REQUIRES(context, dec.Close().ok(),
                tensorflow::errors::DataLoss("Decoding error."));
  }
};

REGISTER_KERNEL_BUILDER(Name("RunLengthGammaDecode").Device(DEVICE_CPU),
                        RunLengthGammaDecodeOp);

}  // namespace
}  // namespace tensorflow_compression
