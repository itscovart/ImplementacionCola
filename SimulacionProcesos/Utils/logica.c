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