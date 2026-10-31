#include <omp.h>
#include <cstdio>

int main() {
    int sum = 0;
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        #pragma omp scope reduction(+:sum)
        {
            sum += omp_get_thread_num();
        }
    }
    // 0 + 1 + 2 + 3 = 6
    printf("sum = %d\n", sum);
    return 0;
}
