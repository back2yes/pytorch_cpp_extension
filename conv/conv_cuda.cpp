#include <torch/torch.h>
#include <vector>

int conv_cuda_forward(
    const at::Tensor &input,
    const at::Tensor &weight,
    const at::Tensor &bias,
    at::Tensor &output,
    int KW, int KH,
    int SW, int SH,
    int PW, int PH);

int conv_cuda_backward_grad_in(
    at::Tensor &grad_out,
    at::Tensor &weight,
    at::Tensor &grad_in,
    int KW, int KH,
    int SW, int SH,
    int PW, int PH);

int conv_cuda_backward_grad_weight(
    at::Tensor &grad_out,
    at::Tensor &input,
    at::Tensor &grad_weight,
    int KW, int KH,
    int SW, int SH,
    int PW, int PH);

#define CHECK_CUDA(x) AT_ASSERT((x).type().is_cuda(), #x "must be a CUDA tensor")
#define CHECK_CONTIGUOUS(x) AT_ASSERT((x).type().is_contiguous(), #x "must be contiguous")
#define CHECK_INPUT(x) \
    CHECK_CUDA((x));   \
    CHECK_CONTIGUOUS((x))

int conv_forward(
    const at::Tensor &input,
    const at::Tensor &weight,
    const at::Tensor &bias,
    at::Tensor &output,
    int KW, int KH,
    int SW, int SH,
    int PW, int PH)
{
    // TODO: add checks checks
    return conv_cuda_forward(
        input,
        weight,
        bias,
        output,
        KW, KH,
        SW, SH,
        PW, PH);
}

int conv_backward_input(
    at::Tensor &grad_out,
    at::Tensor &weight,
    at::Tensor &grad_in,
    int KW, int KH,
    int SW, int SH,
    int PW, int PH)
{
    // TODO: add checks checks
    return conv_cuda_backward_grad_in(
        grad_out,
        weight,
        grad_in,
        KW, KH,
        SW, SH,
        PW, PH);
}

int conv_backward_weight(
    at::Tensor &grad_out,
    at::Tensor &input,
    at::Tensor &grad_weight,
    int KW, int KH,
    int SW, int SH,
    int PW, int PH)
{
    // TODO: add checks checks
    return conv_cuda_backward_grad_weight(
        grad_out,
        input,
        grad_weight,
        KW, KH,
        SW, SH,
        PW, PH);
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m)
{
    m.def("forward", &conv_forward, "conv forward (CUDA)");
    m.def("backward_input", &conv_backward_input, "conv backward input (CUDA)");
    m.def("backward_weight", &conv_backward_weight, "conv backward weight (CUDA)");
}