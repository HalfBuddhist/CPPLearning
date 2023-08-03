#include <stdio.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

void addWithCuda(int *c);  // 1.定义传入的函数c

int main(void) {
  int c;
  c = 10;
  addWithCuda(&c);           // 2.传入参数变量（地址）
  cudaDeviceReset();         // 6.重置CUDA设备释放程序占用的资源
  printf("Value is %d", c);  // 7.主机上打印显示数据

  system("pause");
  return 0;
}

__global__ void Decrease(int a, int b, int *c) { *c = a - b; }

void addWithCuda(int *c) {
  int *dev_c = 0;  //这个相当于内存和显存有一样的
  // 3.请求CUDA设备的内存（显存），执行CUDA函数
  cudaMalloc((void **)&dev_c, sizeof(int));
  Decrease<<<1, 1>>>(15, 30, dev_c);
  // 4.等待设备所有线程任务执行完毕
  cudaDeviceSynchronize();
  // 5.数据复制到主机，释放占用空间
  cudaMemcpy(c, dev_c, sizeof(int), cudaMemcpyDeviceToHost);
  cudaFree(dev_c);
}
