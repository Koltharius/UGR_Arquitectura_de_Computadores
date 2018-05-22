#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  int i, n = 20, a[n], suma = 0, sumalocal;
  if (argc < 2) {
    fprintf(stderr, "\nFalta iteraciones\n");
    exit(-1);
  }

  n = atoi(argv[1]);
  if (n > 20) {
    n = 20;
  }

  for (i = 0; i < n; i++) {
    a[i] = i;
  }

#pragma omp parallel private(sumalocal)
  {
    sumalocal = 0;
#pragma omp for schedule(static)
    for (i = 0; i < n; i++) {
      sumalocal += a[i];
      printf("thread %d suma de a[%d] = %d sumalocal = %d\n",
             omp_get_thread_num(), i, a[i], sumalocal);
    }
#pragma omp atomic
    suma += sumalocal;
  }

  printf("Fuera de 'paralell' suma = %d\n", suma);
  return 0;
}