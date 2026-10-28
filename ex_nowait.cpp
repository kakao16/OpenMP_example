#include <omp.h>
#include <cstdio>

int main() {
    int i;
    int n = 4;
    // int m = 4; 
    double b[n];
    double y[n];
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i=0; i<n; i++) {
            b[i] = 1.0f * i; 
            printf("b[%d] = %f\n", i, b[i]);
        }
           

        #pragma omp for nowait
        for (i=0; i<n; i++) {
            y[i] = 10.0f * b[i];
            printf("y[%d] = %f\n", i, y[i]);
        }
    }
    return 0;
}
