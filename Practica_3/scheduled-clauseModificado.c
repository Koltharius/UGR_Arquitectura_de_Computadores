#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
    int i, n = 200, chunk, a[n], suma = 0;

    if (argc < 3)
    {
        fprintf(stderr, "\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n > 200)
    {
        n = 200;
    }
    chunk = atoi(argv[2]);

    for (i = 0; i < n; i++)
    {
        a[i] = i;
    }
#pragma omp parallel
    {
#pragma omp for firstprivate(suma) lastprivate(suma) schedule(dynamic, chunk)
        for (i = 0; i < n; i++)
        {
            suma = suma + a[i];
            printf("thread %d suma a[%d]=%d suma=%d \n", omp_get_thread_num(), i,
                   a[i], suma);
        }
        if (omp_get_thread_num() == 0) {
            printf("Dentro de 'parallel':\n");
            printf("\tdyn-var: %d\n", omp_get_dynamic());
            printf("\tnthreads-var: %d\n", omp_get_max_threads());
            printf("\tthread-limit-var: %d\n", omp_get_thread_limit());
            omp_sched_t schedule_type;
            int chunk_size;
            omp_get_schedule(&schedule_type, &chunk_size);
            printf("\run-sched-var: ");
            if (schedule_type == omp_sched_static) {
                printf("omp_sched_static\n");
            } else if (schedule_type == omp_sched_dynamic) {
                printf("omp_sched_dynamic\n");
            } else if (schedule_type == omp_sched_guided) {
                printf("omp_sched_guided\n");
            } else {
                printf("omp_sched_auto\n");
            }
            printf("\tchunk: %d\n", chunk_size);
        }
    }

    printf("Fuera de 'parallel' suma=%d\n", suma);
    printf("\tdyn-var: %d\n", omp_get_dynamic());
    printf("\tnthreads-var: %d\n", omp_get_max_threads());
    printf("\tthread-limit-var: %d\n", omp_get_thread_limit());
    omp_sched_t schedule_type;
    int chunk_size;
    omp_get_schedule(&schedule_type, &chunk_size);
    printf("\trun-sched-var: ");
    if (schedule_type == omp_sched_static) {
        printf("omp_sched_static\n");
    } else if (schedule_type == omp_sched_dynamic) {
        printf("omp_sched_dynamic\n");
    } else if (schedule_type == omp_sched_guided) {
        printf("omp_sched_guided\n");
    } else { /*if (schedule_type == omp_sched_auto)*/
        printf("omp_sched_auto\n");
    }
    printf("\tchunk: %d\n", chunk_size);
}