// #include <Windows.h>
#include <stdio.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void Add(int i, int j) {
  int count;
  count = i + j;
  printf("\nNum is %d\n", count);
}

int main(void) {
  Add<<<1, 1>>>(10, 15);
  cudaDeviceReset();  //重置CUDA设备释放程序占用的资源
  system("pause");
  return 0;
}