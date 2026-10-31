#include <omp.h>
#include <stdio.h>
void report_num_threads()
{
    #pragma omp single
    {
        printf("Level %d: number of threads in the team - %d\n",
                omp_get_level(), omp_get_num_threads());
    }
}

int main()
{
    omp_set_max_active_levels(3);
    #pragma omp parallel num_threads(2)
    {
        // Level 1: 2 threads 
        report_num_threads(); 
        #pragma omp parallel num_threads(2)
        {
            // Level 2: 2x2 threads 
            report_num_threads(); 
            #pragma omp parallel num_threads(2)
            {
                // Level 3: 2x2x2 threads 
                report_num_threads(); 
            }
        }
    }
    return(0);
}
