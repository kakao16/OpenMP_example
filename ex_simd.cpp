#include <omp.h>
#include <iostream>
#include <vector>
#include <cstring>

void print_vector_n(std::vector<float> v, int n, std::string name) {
    std::cout << name << " = { ";
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "... }\n";
}

int main()
{
    const int N = 100000000;
    double t_start, t_end;

    std::vector<float> A(N);
    std::vector<float> B(N);
    std::vector<float> C(N);
    std::vector<float> C_simd(N);

    for (int i = 0; i < N; ++i)
    {
        A[i] = i;
        B[i] = i * 2;
    }

    //  Without SIMD
    t_start = omp_get_wtime();
    for (int i = 0; i < N; ++i)
    {
        C[i] = A[i] * B[i];
    }
    t_end = omp_get_wtime();

    print_vector_n(A, 5, "A");
    print_vector_n(B, 5, "B");
    print_vector_n(C, 5, "C");
    
    std::cout << "time taken without simd: " << t_end - t_start << "s\n";

    // SIMD version
    t_start = omp_get_wtime();
    #pragma omp simd
    for (int i = 0; i < N; ++i)
    {
        C_simd[i] = A[i] * B[i];
    }
    t_end = omp_get_wtime();

    print_vector_n(A, 5, "A");
    print_vector_n(B, 5, "B");
    print_vector_n(C_simd, 5, "C_simd");
    
    std::cout << "time taken with simd: " << t_end - t_start << "s\n";

    // parallel SIMD version
    omp_set_num_threads(6);
    std::vector<float> C_simd_par(N);

    t_start = omp_get_wtime();
    #pragma omp parallel for simd
    for (int i = 0; i < N; ++i)
    {
        C_simd_par[i] = A[i] * B[i];
    }
    t_end = omp_get_wtime();

    print_vector_n(A, 5, "A");
    print_vector_n(B, 5, "B");
    print_vector_n(C_simd_par, 5, "C_simd_par");
    
    std::cout << "time taken with parallel simd: " << t_end - t_start << "s\n";
}
