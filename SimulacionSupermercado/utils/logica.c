/*
  Archivo donde se plantea la logica de las definiciones visuales para el programa
  Autor: Covarrubias Sanchez Arturo
*/

// LIBRERIA
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  
#include "logica.h"

//FUNCIONES
void EsperarMiliSeg(int t){
  usleep(t*1000);
}

void BorrarPantalla(){
  system("clear");
}

void MoverCursor( int x, int y ) 
{
	printf("\033[%d;%dH", y, x);
}

void LimpiarInformacionColas(){
  MoverCursor(0, 5);
  printf("\033[J");
}

int NumeroAleatorio(int min, int max){
  static int seeded = 0;
  if(!seeded){
    srand((unsigned)time(NULL));
    seeded = 1;
  }
  return min + rand() % (max - min + 1);
}

void ImprimirInicioSupermercado(char *nombreSupermercado, int tamañoTitulo, int cajas, int *posicionesCajas){
  BorrarPantalla();

  int primerCaracterTitulo = (COLUMNAS / 2) - ((tamañoTitulo) / 2), numeroCaja = 0;

  if(!posicionesCajas){
    printf("Error al reservar memoria");
    exit(1);
  }

  PosicionesCajas(posicionesCajas, cajas);

  for(int i = 0; i < FILAS; i++){
    for(int j = 0; j < COLUMNAS; j++){
      if(i == 0) {
        if(j == primerCaracterTitulo){
        printf("%s", nombreSupermercado);
        j += tamañoTitulo;
        } else {
          printf("-");
        }
      } else if (i == FILAS - 1){
        printf("_");
      } else if(i == 2){
        if(j == posicionesCajas[numeroCaja]){
          numeroCaja++;
          printf(" CAJA %d ", numeroCaja);
          j += (numeroCaja != 10) ? 7 : 8;
        } else {
          printf(" ");
        }
      }
    }
    printf("\n");
  }
}

void ImprimirCambiosCajas(cola **arrColasCajas, int cajas, int *arrPosicionesCajas){
  LimpiarInformacionColas();
  for(int i = 0; i < cajas; i++){
    cola *direccionCola = arrColasCajas[i];
    if(!Empty(direccionCola)){
      for(int j = 0; j < Size(direccionCola); j++){
        if(j < FILAS){
          MoverCursor(arrPosicionesCajas[i] + 3, j + 4);
          printf("%d", Element(direccionCola, j + 1).valor);
        }
      }
    }
  }
}

void PosicionesCajas(int *arrPosicionesCajas, int cajas){
  int primerIndice = ((COLUMNAS)/(cajas + 1));
  for (int i = 0; i < cajas; i++){
    if(i == 0){
      arrPosicionesCajas[i] = primerIndice - 4;
    } else {
      arrPosicionesCajas[i] = arrPosicionesCajas[i - 1] + 8;
    }
  }
}

void AbrirSupermercado(int cajas, int *tiemposCajas, int *arrPosicionesCajas, int tiempoClientes){
  EsperarMiliSeg(TIEMPO_BASE);

  elemento clienteAtendidos, clientesNuevos;
  int tiempo = 0, numeroCaja;

  cola **colasCajas = malloc(cajas * sizeof(cola*)), *direccionMemoriaCaja;
  if(!colasCajas){
    printf("Error al reservar memoria para el arreglo de las colas");
    exit(1);
  }

  clientesNuevos.valor = 1;
  for(int i = 0; i < cajas; i++){
    colasCajas[i] = (cola*)malloc(sizeof(cola));
    if(!colasCajas[i]){
      printf("Error al reservar memoria para la cola %d\n", i + 1);
      exit(1);
    }
    Inicializar(colasCajas[i]);
  }

  while(1){
    tiempo += 10;

    if(tiempo % tiempoClientes == 0){
      if(ColasLlenas(colasCajas, cajas)){
        printf("Todas las colas estan llenas");
        exit(0);
      } else {
        do{
          numeroCaja = NumeroAleatorio(1, cajas);
        } while (!Queue(colasCajas[numeroCaja - 1], clientesNuevos));
        clientesNuevos.valor++;
      }
    }

    for(int i = 0; i < cajas; i++){
      direccionMemoriaCaja = colasCajas[i];
      if(tiempo % tiemposCajas[i] == 0 && !Empty(direccionMemoriaCaja)){
        clienteAtendidos = Dequeue(direccionMemoriaCaja);
        ImprimirCambiosCajas(colasCajas, cajas, arrPosicionesCajas);
        printf("\nUltimo cliente atendido: Numero.%d en la caja %d\n", clienteAtendidos.valor, i + 1);
      }
    }
  }
}

int ColasLlenas(cola **colasCajas, int cajas){
  int cajasLlenas = 0;
  for(int i = 0; i < cajas; i++){
    if(Size(colasCajas[i]) == TAMAÑO_MAXIMO) cajasLlenas++;
  }
  return cajasLlenas == cajas;
}