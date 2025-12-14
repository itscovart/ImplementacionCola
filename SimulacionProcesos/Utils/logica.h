/*
  Archivo donde se definen funciones que se ocuparan en el programa para hacerlo visualmente
  Autor: Covarrubias Sanchez Arturo
*/

// LIBRERIAS
//#include "../Cola/ColaEstatica.h"
#include "../Cola/ColaDin.h" // En caso de querer usar pila dinamica

// CONSTANTES
#define TIEMPO_BASE 100

// FUNCIONES
void BorrarPantalla();

void EsperarMilisegundos(int t);

void ImprimirCola(cola *c, int tipoCola, int tiempo);