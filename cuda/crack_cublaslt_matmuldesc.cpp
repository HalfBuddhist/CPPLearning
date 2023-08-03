#include <cublasLt.h>

int main {
  cublasLtMatmulDesc_t operationDesc = NULL;
  // create operation desciriptor; see cublasLtMatmulDescAttributes_t for
  // details about defaults; here we just need to set the transforms for A and B
  checkCublasStatus(
      cublasLtMatmulDescCreate(&operationDesc, CUBLAS_COMPUTE_32F, CUDA_R_32F));
}