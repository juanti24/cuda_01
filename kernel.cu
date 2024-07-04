#include<iostream>

__global__
void addVecKernel(float* a, float* b, float* c, int size) {
    int index = threadIdx.x+blockDim.x*blockIdx.x;

    if(index<size){
        c[index]= a[index]+ b[index];
    }
}

extern "C"
void addVec(float* a, float* b, float* c, int size) {

    int thread_num = 1024;
    int num_bloques = std::ceil(size/thread_num);
    printf("num_bloques=%d, num_threads=%d\n",num_bloques,thread_num);
    addVecKernel<<<num_bloques,thread_num>>>(a,b,c,size);
}
