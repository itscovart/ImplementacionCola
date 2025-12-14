/*
  Implementacion de la logica correspondiente a las definiciones de una cola que contiene ColaEstatica.h
  Autor: Covarrubias Sanchez Arturo
*/

// LIBRERIAS
#include "ColaEstatica.h"
#include <stdio.h>
#include <stdlib.h>

// FUNCIONES

/*
  void Inicializar(cola *c);
  Recibe: Una referencia a una cola que se ocupara para operar
*/
void Inicializar(cola *c){
  c->frente = -1;
  c->final = -1;
  c->tamaño = 0;
}

/*
  void Queue(cola *c, elemento valor);
  Recibe: La referencia de una cola y un elemento que desea encolar
  Logica: Encolar el elemento dado por el usuario en el unico caso de que todavia haya espacio en la cola
  Devuelve: Un valor TRUE o FALSE en caso de que pudo encolar o no
*/
int Queue(cola *c, elemento valor){
  int respuesta = FALSE;
  if(c->tamaño == TAMAÑO_MAXIMO){
    // printf("Error en la cola: Tamaño maximo de la cola alcanzado\n");
    respuesta = FALSE;
  } else {
    c->final++;
    c->valores[c->final] = valor;
    c->tamaño++;
    if(c->frente == -1){
      c->frente++;
    }
    respuesta = TRUE;
  }
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
  if(c->tamaño>0){
    valor = c->valores[c->frente];
    for(int i = 0; i < c->final; i++){
      c->valores[i] = c->valores[i + 1];
    }
    c->tamaño--;
    if(c->tamaño == 0){
      c->frente = -1;
      c->final = -1;
    } else {
      c->final--;
    }
  } else {
    printf("Error en la cola: No hay elementos que desencolar dentro de la cola\n");
    exit(1);
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
    valor = c->valores[c->frente];
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
    valor = c->valores[c->final];
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
  elemento valor;
  if(indice > 0 && indice <= c->tamaño){
    valor = c->valores[indice - 1];
  } else {
    printf("Error en la cola: Inexistencia de elementos en la cola o no esta incializada\n");
    exit(1);
  }
  return valor;
}

/*
  void Destroy(cola *c);
  Recibe: Una referencia de una cola
  Logica: Restablece los valores de frente, final y tamaño como una cola incializada
*/
void Destroy(cola *c){
  c->frente = -1;
  c->final = -1;
  c->tamaño = 0;
}