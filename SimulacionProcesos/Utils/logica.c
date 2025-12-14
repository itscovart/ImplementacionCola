/*

*/

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif
#include "logica.h"

// Funcion que borra la pantalla y cambia el script dependiendo de que entorno se ejecute
void BorrarPantalla(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void EsperarMilisegundos(int t){
  #ifdef _WIN32
    Sleep(t);
  #else
    usleep(t*1000);
  #endif
}

#ifdef COLAESTATICA_DISPONIBLE
void ImprimirCola(cola *c, int tipoCola, int tiempo){
  int cantElementos = Size(c);
  elemento proceso;

  for(int i = 0; i < cantElementos; i++){
    proceso = c->valores[i];
    if(tipoCola){
      printf("%d. %s finalizado despues de %dms\n", (i + 1), proceso.nombreProceso, proceso.tiempoProcesoMS);
    } else {
      if(i == 0) continue;
      printf("%d. %s en espera de ejecucion\n", i, proceso.nombreProceso);
    }
  }
}
#else
void ImprimirCola(cola *c, int tipoCola, int tiempo){
  int cantElementos = Size(c);
  nodo *proceso;
  elemento nodoActual;
  proceso = c->frente;

  for(int i = 0; i < cantElementos; i++){
    nodoActual = proceso->valor;
    if(tipoCola){
      printf("%d. %s finalizado despues de %dms\n", (i + 1), nodoActual.nombreProceso, nodoActual.tiempoProcesoMS);
    } else {
      if(i != 0){
        printf("%d. %s en espera de ejecucion\n", i, nodoActual.nombreProceso);
      }
    }
    proceso = proceso->sig;
  }
}
#endif