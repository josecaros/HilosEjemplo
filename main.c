#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


static void *funcionEjemplo1(void * arg);
static void *funcionEjemplo2(void * arg);
#define LOOP_DATA 10000
static int contador=0;
int main() {
  pthread_t hilo1, hilo2;

  pthread_create(&hilo1,NULL, *funcionEjemplo1, NULL);
  pthread_create(&hilo1,NULL, *funcionEjemplo2, NULL);

  pthread_join(hilo1,NULL);
  pthread_join(hilo2,NULL);

  printf("Valor contador:%d \n",contador);
  return 0;
}

static void *funcionEjemplo1(void * arg){
  for (int i = 0; i < LOOP_DATA ; i++) {
    contador++;
    //printf("Valor desde Ejemplo1 contador:%d \n",contador);
  }
}
static void *funcionEjemplo2(void * arg){
  for (int i = 0; i < LOOP_DATA; i++) {
    contador--;
    //printf("Valor desde Ejemplo2 contador:%d \n",contador);
  }
}