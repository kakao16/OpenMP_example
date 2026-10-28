#include <omp.h>
#include <cstdio>
#include <cmath>

int main() {
    int i;
    int n = 10;
    double b[n];
    omp_set_num_threads(3);
    #pragma omp parallel
    {
        #pragma omp for ordered schedule(dynamic)
        for (i=0; i<n; i++) {
            b[i] = 1.0f * sqrt(i*12345);
            int id = omp_get_thread_num();
            printf("Working in thread number: %d; iteration: %d\n", id, i);
            #pragma omp ordered
            printf("Finished thread number: %d; iteration: %d\n", id, i);
        }
    }
    return 0;
}
