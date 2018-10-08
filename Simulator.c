//
// Created by Jose on 07/10/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <windows.h>

struct Cliente {
  int numer;
  int tCajero;
  int tCompra;
  int caja;
};

struct Cajeros {
  int numCajero;
  int pila;
} cajas[5];

void establecerCajas(){
  for(int i = 0; i < 5; ++i) {
    cajas[i].numCajero=i;
    cajas[i].pila=0;
  }
}

void *procesarCliente(void *arg) {
  struct Cliente *client = (struct Cliente *) arg;
  printf("Cliente %i: Tiempo de Compra:%i\t Tiempo en Cajero:%i\t Atendiddo en el Cajero:%i\n", client->numer, client->tCompra, client->tCajero,client->caja);
  cajas[client->caja].pila--;
  Sleep((unsigned) 5000);
}

//Selecciona el numero menor de cajas[].pila
int seleccionarCajero(){
  int a=0;
  int min=cajas[0].pila;
  if(min>cajas[1].pila){
    min=cajas[1].pila;
    a=1;
  }
  if(min>cajas[2].pila){
    min=cajas[2].pila;
    a=2;
  }
  if(min>cajas[3].pila){
    min=cajas[3].pila;
    a=3;
  }
  if(min>cajas[4].pila){
    min=cajas[4].pila;
    a=4;
  }
  if(min>cajas[5].pila){
    min=cajas[5].pila;
    a=5;
  }
  return a;

}

int main (char arg, char* args){
  //Establece las cajas, es como un Constructor de la cantidad de cajas
  establecerCajas();
  //Crear un numero random de clientes y de los argumentos q estos poseen
  time_t t;
  srand((unsigned) time(&t));
  int ranN = 10; //para mostrar le puse 10, pero deberian de ser un aleatorio

  //Creamos e iniciamos a todos los clientes
  struct Cliente cliente[ranN];
  for(int i = 0; i < ranN; ++i) {
    cliente[i].numer=i;
    cliente[i].tCajero=((rand()%100)+1);
    cliente[i].tCompra=((rand()%1000)+1);
    cliente[i].caja=-1;
  }

  //Creamos el hilo y le añadimos atributos, Se puede trabajar con atributos NULL tambien
  pthread_t hilo;

  //Create atribute
  pthread_attr_t attri;
  pthread_attr_init(&attri);

  //Preguntamos por cada Cliente y lo mandamos a la caja con menor cantidad en su Cola
  for(int j = 0; j < ranN; ++j) {
    int pil=seleccionarCajero();
    cliente[j].caja=pil;
    cajas[pil].pila++;
    printf("Cliente(%i) entra a la cola del Cajero(%i)\n",cliente[j].numer,pil);
    pthread_create(&hilo, &attri, procesarCliente, &cliente[j]);
  }
  pthread_join(hilo, NULL);


  return 0;
}

