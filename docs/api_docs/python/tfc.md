description: Data compression in TensorFlow.

<div itemscope itemtype="http://developers.google.com/ReferenceObject">
<meta itemprop="name" content="tfc" />
<meta itemprop="path" content="Stable" />
</div>

# Module: tfc

<!-- Insert buttons and diff -->

<table class="tfo-notebook-buttons tfo-api nocontent" align="left">
<td>
  <a target="_blank" href="https://github.com/tensorflow/compression/tree/master/tensorflow_compression/__init__.py">
    <img src="https://www.tensorflow.org/images/GitHub-Mark-32px.png" />
    View source on GitHub
  </a>
</td>
</table>



Data compression in TensorFlow.



## Classes

[`class ContinuousBatchedEntropyModel`](./tfc/ContinuousBatchedEntropyModel.md): Batched entropy model for continuous random variables.

[`class ContinuousIndexedEntropyModel`](./tfc/ContinuousIndexedEntropyModel.md): Indexed entropy model for continuous random variables.

[`class DeepFactorized`](./tfc/DeepFactorized.md): Fully factorized distribution based on neural network cumulative.

[`class GDN`](./tfc/GDN.md): Generalized divisive normalization layer.

[`class GDNParameter`](./tfc/GDNParameter.md): Nonnegative parameterization as needed for GDN parameters.

[`class IdentityInitializer`](./tfc/IdentityInitializer.md): Initialize to the identity kernel with the given shape.

[`class LocationScaleIndexedEntropyModel`](./tfc/LocationScaleIndexedEntropyModel.md): Indexed entropy model for location-scale family of random variables.

[`class MonotonicAdapter`](./tfc/MonotonicAdapter.md): Adapt a continuous distribution via an ascending monotonic function.

[`class NoisyDeepFactorized`](./tfc/NoisyDeepFactorized.md): DeepFactorized that is convolved with uniform noise.

[`class NoisyLogistic`](./tfc/NoisyLogistic.md): Logistic distribution with additive i.i.d. uniform noise.

[`class NoisyLogisticMixture`](./tfc/NoisyLogisticMixture.md): Mixture of logistic distributions with additive i.i.d. uniform noise.

[`class NoisyMixtureSameFamily`](./tfc/NoisyMixtureSameFamily.md): Mixture of distributions with additive i.i.d. uniform noise.

[`class NoisyNormal`](./tfc/NoisyNormal.md): Gaussian distribution with additive i.i.d. uniform noise.

[`class NoisyNormalMixture`](./tfc/NoisyNormalMixture.md): Mixture of normal distributions with additive i.i.d. uniform noise.

[`class NoisyRoundedDeepFactorized`](./tfc/NoisyRoundedDeepFactorized.md): Rounded DeepFactorized + uniform noise.

[`class NoisyRoundedNormal`](./tfc/NoisyRoundedNormal.md): Rounded normal distribution + uniform noise.

[`class NoisySoftRoundedDeepFactorized`](./tfc/NoisySoftRoundedDeepFactorized.md): Soft rounded deep factorized distribution + uniform noise.

[`class NoisySoftRoundedNormal`](./tfc/NoisySoftRoundedNormal.md): Soft rounded normal distribution + uniform noise.

[`class PackedTensors`](./tfc/PackedTensors.md): Packed representation of compressed tensors.

[`class Parameter`](./tfc/Parameter.md): Reparameterized `Layer` variable.

[`class RDFTParameter`](./tfc/RDFTParameter.md): RDFT reparameterization of a convolution kernel.

[`class RoundAdapter`](./tfc/RoundAdapter.md): Continuous density function + round.

[`class SignalConv1D`](./tfc/SignalConv1D.md): 1D convolution layer.

[`class SignalConv2D`](./tfc/SignalConv2D.md): 2D convolution layer.

[`class SignalConv3D`](./tfc/SignalConv3D.md): 3D convolution layer.

[`class SoftRound`](./tfc/SoftRound.md): Applies a differentiable approximation of rounding.

[`class SoftRoundAdapter`](./tfc/SoftRoundAdapter.md): Differentiable approximation to round.

[`class SoftRoundConditionalMean`](./tfc/SoftRoundConditionalMean.md): Conditional mean of inputs given noisy soft rounded values.

[`class UniformNoiseAdapter`](./tfc/UniformNoiseAdapter.md): Additive i.i.d. uniform noise adapter distribution.

[`class UniversalBatchedEntropyModel`](./tfc/UniversalBatchedEntropyModel.md): Batched entropy model model which implements Universal Quantization.

[`class UniversalIndexedEntropyModel`](./tfc/UniversalIndexedEntropyModel.md): Indexed entropy model model which implements Universal Quantization.

[`class Y4MDataset`](./tfc/Y4MDataset.md): A `tf.Dataset` of Y'CbCr video frames from '.y4m' files.

## Functions

[`create_range_decoder(...)`](./tfc/create_range_decoder.md): Creates range decoder objects to be used by `EntropyDecode*` ops.

[`create_range_encoder(...)`](./tfc/create_range_encoder.md): Creates range encoder objects to be used by `EntropyEncode*` ops.

[`entropy_decode_channel(...)`](./tfc/entropy_decode_channel.md): Decodes the encoded stream inside `handle`.

[`entropy_decode_finalize(...)`](./tfc/entropy_decode_finalize.md): Finalizes the decoding process. This op performs a *weak* sanity check, and the

[`entropy_decode_index(...)`](./tfc/entropy_decode_index.md): Decodes the encoded stream inside `handle`.

[`entropy_encode_channel(...)`](./tfc/entropy_encode_channel.md): Encodes each input in `value`.

[`entropy_encode_finalize(...)`](./tfc/entropy_encode_finalize.md): Finalizes the encoding process and extracts byte stream from the encoder.

[`entropy_encode_index(...)`](./tfc/entropy_encode_index.md): Encodes each input in `value` according to a distribution selected by `index`.

[`estimate_tails(...)`](./tfc/estimate_tails.md): Estimates approximate tail quantiles.

[`lower_bound(...)`](./tfc/lower_bound.md): Same as `tf.maximum`, but with helpful gradient for `inputs < bound`.

[`lower_tail(...)`](./tfc/lower_tail.md): Approximates lower tail quantile for range coding.

[`perturb_and_apply(...)`](./tfc/perturb_and_apply.md): Perturbs the inputs of a pointwise function.

[`pmf_to_quantized_cdf(...)`](./tfc/pmf_to_quantized_cdf.md): Converts a PMF into a quantized CDF for range coding.

[`quantization_offset(...)`](./tfc/quantization_offset.md): Computes distribution-dependent quantization offset.

[`round_st(...)`](./tfc/round_st.md): Straight-through round with optional quantization offset.

[`run_length_gamma_decode(...)`](./tfc/run_length_gamma_decode.md): Decodes `data` using run-length and Elias gamma coding.

[`run_length_gamma_encode(...)`](./tfc/run_length_gamma_encode.md): Encodes `data` using run-length and Elias gamma coding.

[`same_padding_for_kernel(...)`](./tfc/same_padding_for_kernel.md): Determine correct amount of padding for `same` convolution.

[`soft_round(...)`](./tfc/soft_round.md): Differentiable approximation to round().

[`soft_round_conditional_mean(...)`](./tfc/soft_round_conditional_mean.md): Conditional mean of inputs given noisy soft rounded values.

[`soft_round_inverse(...)`](./tfc/soft_round_inverse.md): Inverse of soft_round().

[`upper_bound(...)`](./tfc/upper_bound.md): Same as `tf.minimum`, but with helpful gradient for `inputs > bound`.

[`upper_tail(...)`](./tfc/upper_tail.md): Approximates upper tail quantile for range coding.

