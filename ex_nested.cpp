#include <omp.h>
#include <stdio.h>

int main()
{
    omp_set_max_active_levels(2);
    #pragma omp parallel for num_threads(2)
    for(int i=0; i< 3; i++) {
        #pragma omp parallel for num_threads(3)
        for (int j=0; j< 3; j++) {
            printf("i = %d, j= %d, threadId = %d \n", i, j, omp_get_thread_num());
        }
    }
    return(0);
}
