/*
  Implementacion de la logica correspondiente a las definiciones de una cola que contiene ColaEstatica.h
  Autor: Covarrubias Sanchez Arturo
*/

// LIBRERIAS
#include "ColaDin.h"
#include <stdio.h>
#include <stdlib.h>

// FUNCIONES

/*
  void Inicializar(cola *c);
  Recibe: Una referencia a una cola que se ocupara para operar
*/
void Inicializar(cola *c){
  c->frente = NULL;
  c->final = NULL;
  c->tamaño = 0;
}

/*
  void Queue(cola *c, elemento valor);
  Recibe: La referencia de una cola y un elemento que desea encolar
  Logica: Encolar el elemento dado por el usuario en el unico caso de que todavia haya espacio en la cola
  Devuelve: Un valor TRUE o FALSE en caso de que pudo encolar o no
*/
boleano Queue(cola *c, elemento valor){
  char respuesta = TRUE;
  nodo *aux;
  aux = malloc(sizeof(nodo));
  if(aux == NULL){
    printf("No se pudo reservar mas memoria para este nodo");
    exit(1);
  }
  if(c->frente == NULL){
    c->frente = aux;
    c->final = aux;
  } else {
    c->final->sig = aux;
    c->final = aux;
  }
  aux->valor = valor;
  aux->sig = NULL;
  c->tamaño++;
  return respuesta;
}

/*
  elemento Dequeue(cola *c);
  Recibe: La referencia a una cola
  Logica: Desencola el elemento del frente de la cola y lo devuelve, despues recorre todos los valores restantes y los reordena.
  Devuelve: Elemento en el frente de la cola
*/
elemento Dequeue(cola *c){
  elemento valor;
  nodo *aux;
  if(c->tamaño <= 0){
    printf("No se puede desencolar en algo lo cual no hay nada encolado");
    exit(1);
  }
  valor = c->frente->valor;
  if(c->tamaño == 1){
    free(c->frente);
    c->frente = NULL;
    c->final = NULL;
    c->tamaño = 0;
  } else {
    aux = c->frente;
    c->frente = c->frente->sig;
    free(aux);
    c->tamaño--;
  }
  return valor;
}

/*
  boleano Empty(cola *c);
  Recibe: Direccion de una cola
  Devuelve: Verdadero o Falso de acuerdo a si la cola esta vacia o no
*/
boleano Empty(cola *c){
  return (c->tamaño == 0)?TRUE:FALSE;
}

/*
  elemento Front(cola *c);
  Recibe: Una referencia a una cola
  Logica: Verifica si la cola ha sido inicializado y si contiene elementos
  Devuelve: El elemento hasta el frente de la cola sin afectarlo dentro de esta
*/
elemento Front(cola *c){
  elemento valor;
  if(c->tamaño <= 0){
    printf("Error en la cola: Cola sin elementos o no incializada\n");
    exit(1);
  } else {
    valor = c->frente->valor;
  }
  return valor;
}

/*
  elemento Final(cola *c);
  Recibe: Una referencia a una cola
  Logica: Verifica si la cola ha sido inicializado y si contiene elementos
  Devuelve: El elemento hasta el final de la cola sin afectarlo dentro de esta
*/
elemento Final(cola *c){
  elemento valor;
  if(c->tamaño <= 0){
    printf("Error en la cola: Cola no inicializada o sin elementos\n");
  } else {
    valor = c->final->valor;
  }
  return valor;
}

/*
  int Size(cola *c);
  Recibe: Referencia de una cola
  Devuelve: En caso de no estar inicializada 0 y en caso contrario la cantidad de elementos dentro de la cola
*/
int Size(cola *c){
  return c->tamaño;
}

/*
  elemento Element(cola *c, int indice);
  Recibe: Una referencia de una cola y un indice
  Logica: Valida si el indice esta dentro del rango de la cola existente
  Devuelve: Elemento en la posicion del indice
*/
elemento Element(cola *c, int indice){
  nodo *aux;
  if(indice > 0 && indice <= c->tamaño){
    aux = c->frente;
    for(int i = 1; i < indice; i++){
      aux = aux->sig;
    }
  } else {
    printf("Error en la cola: Inexistencia de elementos en la cola o no esta incializada\n");
    exit(1);
  }
  return aux->valor;
}

/*
  void Destroy(cola *c);
  Recibe: Una referencia de una cola
  Logica: Restablece los valores de frente, final y tamaño como una cola incializada
*/
void Destroy(cola *c){
  nodo *aux;
  while(c->frente != NULL){
    aux = c->frente->sig;
    free(c->frente);
    c->frente = aux;
  }
  c->tamaño = 0;
  c->final = NULL;
}