#include <iostream>
#include <vector>
#include <omp.h>

int main()
{
    const int N = 1000000;

    std::vector<float> A(N);
    std::vector<float> B(N);
    std::vector<float> C(N);

    float* a = A.data();
    float* b = B.data();
    float* c = C.data();

    for (int i = 0; i < N; ++i)
    {
        a[i] = i;
        b[i] = i * 2;
    }

    int on_gpu = 0;
    #pragma omp target map(from: on_gpu)
    {
        on_gpu = !omp_is_initial_device();
    }

    if (on_gpu)
        std::cout << "Target: GPU\n";
    else
        std::cout << "Target: CPU\n";

    
    double start = omp_get_wtime();
    #pragma omp target teams distribute parallel for \
        map(to: a[0:N], b[0:N]) \
        map(from: c[0:N])
    for (int i = 0; i < N; ++i)
    {
        c[i] = a[i] * b[i];
    }
    double end = omp_get_wtime();

    std::cout << "time taken on gpu: " << end - start << "s\n"

    return 0;
}