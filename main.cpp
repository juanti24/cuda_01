#include <iostream>
//#include <cuda.h>
#include <cuda_runtime.h>

#define VECTOR_SIZE 1024*1024

extern "C"
void  addVec(float *a, float *b, float*c, int size);

int main() {

    //--------------------HOST-----------------------------

    float* h_A = new float [VECTOR_SIZE];

    float* h_B = new float [VECTOR_SIZE];

    float* h_C = new float [VECTOR_SIZE];

    for (int i = 0; i < VECTOR_SIZE; ++i) {
        h_A[i] =1;
        h_B[i] =2;
        h_C[i] =1;
    }


    float* d_A;
    float* d_B;
    float* d_C;

    int size = VECTOR_SIZE*sizeof (float);


    cudaMalloc(&d_A,size);
    cudaMalloc(&d_B,size);
    cudaMalloc(&d_C,size);

    //---------------copiar: host - to - device

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);


    //-----------------invocar al kernel
    //----4 bloques*256 threads/bloque=1024

    addVec(d_A, d_B, d_C, VECTOR_SIZE);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    for (int i = 0; i < 10; ++i) {

        printf("%.0f, ", h_C[i]);

    }


    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    delete[] h_A;
    delete[] h_B;
    delete[] h_C;




    return 0;
}