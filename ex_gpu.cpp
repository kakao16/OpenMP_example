#include <omp.h>
#include <iostream>
#include <vector>

int main()
{
    int on_gpu = 0;
    #pragma omp target map(from: on_gpu)
    {
        on_gpu = !omp_is_initial_device();
    }

    if (on_gpu)
        std::cout << "Target: GPU\n";
    else
        std::cout << "Target: CPU\n";
}
