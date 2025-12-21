/*
  Este archivo contiene todas las declaraciones de constantes, tipos de datos y funciones necesarios para un uso correcto de una cola
  Autor: Covarrubias Sanchez Arturo
*/

// CONSTANTES
#define TAMAÑO_MAXIMO 150
#define TRUE 1
#define FALSE 0

// TIPOS DE DATOS

// Variable para entender mas facil cuando usaremos un estado alto o bajo
typedef unsigned char boleano;

// Struct para determinar que informacion contendra un elemento que el usuario o el mismo programa ingrese a la cola
typedef struct elemento {
  char nombreProceso[45];
  char actividad[200];
  char ID[45];
  int tiempoProcesoMS;
  int tiempoProcesoMSActualizado;
} elemento;

// Definicion de la estructura que tendra la cola donde se incluyen los elementos que tendra, un frente, un final y un contador para el tamaño de la cola
typedef struct cola{
  elemento valores[TAMAÑO_MAXIMO];
  int frente;
  int final;
  int tamaño;
} cola;

// FUNCIONES

// Inicializar: Recibe una cola y la define para un uso correcto
void Inicializar(cola *c);

// Queue: Recibe una cola y un elemento el cual se encolara en la cola indicada en el caso que todavia tenga espacio, regresa un TRUE o FALSE si pudo encolar o no
boleano Queue(cola *c, elemento valor);

// Dequeue: Recibe una cola y regresa el elemento al frente de la cola y asi mismo elimina este elemento de la cola
elemento Dequeue(cola *c);

// Empty: Recibe una cola y regresa un valor alto o bajo de acuerdo a si la cola esta vacia o no
boleano Empty(cola *c);

// Front: Recibe una cola y unicamente regresa el elemento del frente
elemento Front(cola *c);

// Final: Recibe una cola y regresa su elemento del final
elemento Final(cola *c);

// Size: Recibe una cola y devuelve la cantidad de elementos que esta contiene
int Size(cola *c);

// Element: Recibe una cola y un indice dentro de la cola, regresa el elemento en la posicion proporcionada
elemento Element(cola *c, int indice);

// Destroy: Recibe una cola y elimina todos los elementos que contiene
void Destroy(cola *c);

#ifndef COLAESTATICA_DISPONIBLE
#define COLAESTATICA_DISPONIBLE
#endif