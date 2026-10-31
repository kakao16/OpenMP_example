#include <omp.h>
#include <cstdio>
#include <cmath>

int main() {
    omp_set_num_threads(5);
    #pragma omp parallel
    {
        #pragma omp masked // == #pragma omp master
        {
            printf("Thread [%d]: Hello from primary thread!\n", omp_get_thread_num());
        }

        #pragma omp masked filter(2)
        {
            printf("Thread [%d]: Hello from thread with id=2!\n", omp_get_thread_num());
        }

        #pragma omp masked filter(omp_get_thread_num()/2*2)
        {
            printf("Thread [%d]: Hello from thread with even id!\n", omp_get_thread_num());
        }

        #pragma omp masked filter(omp_get_thread_num()/2*2+1)
        {
            printf("Thread [%d]: Hello from thread with odd id!\n", omp_get_thread_num());
        }

        #pragma omp masked filter(omp_get_thread_num()%3)
        {
            printf("Thread [%d]: Hello from thread from 0 to 2!\n", omp_get_thread_num());
        }
    }
    return 0;
}
