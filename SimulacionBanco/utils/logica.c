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
#ifdef _WIN32
  #include <windows.h>
#endif

//FUNCIONES
void EsperarMiliSeg(int t){
  #ifdef _WIN32
    Sleep(t);
  #else
    usleep(t*1000);
  #endif
}

void BorrarPantalla(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void MoverCursor( int x, int y ) 
{
  #ifdef _WIN32
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y }; 
    SetConsoleCursorPosition( hStdout, position );
  #else
	  printf("\033[%d;%dH", y, x);
  #endif
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

void ImprimirInicioBanco(char nombreBanco[], int tamañoTitulo, int cajas, int *posicionesCajas){
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
        printf("%s", nombreBanco);
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
        if(j < FILAS - 2){
          MoverCursor(arrPosicionesCajas[i] + 3, j + 4);
          printf("%s", Element(direccionCola, j + 1).cliente);
        }
      }
    }
  }
}

void PosicionesCajas(int *arrPosicionesCajas, int cajas){
  int primerIndice = ((COLUMNAS)/(cajas + 1));
  if(cajas == 1){
    arrPosicionesCajas[0] = primerIndice - 4;
  } else {
    for (int i = 0; i < cajas; i++){
      if(i == 0){
        arrPosicionesCajas[i] = primerIndice - 7;
      } else {
        arrPosicionesCajas[i] = arrPosicionesCajas[i - 1] + 8 + arrPosicionesCajas[0];
      }
    }
  }
}

void AbrirBanco(int cajas, int *tiemposCajas, int *arrPosicionesCajas, int *tiemposClientes, char *nombreBanco){
  elemento clienteAtendidos, clientesNuevos;
  int tiempo = 0, numeroCaja, clientesSatisfechos = 0, cantNormal = 1, cantUsuario = 1, cantPreferente = 1;
  
  cola **colasCajas = malloc(cajas * sizeof(cola*)), *direccionMemoriaCaja;
  if(!colasCajas){
    printf("Error al reservar memoria para el arreglo de las colas");
    exit(1);
  }
  
  for(int i = 0; i < cajas; i++){
    colasCajas[i] = (cola*)malloc(sizeof(cola));
    if(!colasCajas[i]){
      printf("Error al reservar memoria para la cola %d\n", i + 1);
      exit(1);
    }
    Inicializar(colasCajas[i]);
  }
  
  while(1){
    EsperarMiliSeg(TIEMPO_BASE);
    tiempo++;

    if(tiempo % tiemposClientes[2] == 0){
      snprintf(clientesNuevos.cliente, sizeof(clientesNuevos.cliente), "P%d", cantPreferente);
      #ifdef COLAESTATICA_DISPONIBLE
      if(ColasLlenas(colasCajas, cajas)){
        printf("Todas las colas estan llenas");
        exit(0);
      } else {
        do{
          numeroCaja = NumeroAleatorio(1, cajas);
        } while (!Queue(colasCajas[numeroCaja - 1], clientesNuevos));
        cantPreferente++;
      }
      #else
      numeroCaja = NumeroAleatorio(1, cajas);
      Queue(colasCajas[numeroCaja - 1], clientesNuevos);
      cantPreferente++;
      #endif
    }

    if(tiempo % tiemposClientes[1] == 0){
      snprintf(clientesNuevos.cliente, sizeof(clientesNuevos.cliente), "U%d", cantUsuario);
      #ifdef COLAESTATICA_DISPONIBLE
      if(ColasLlenas(colasCajas, cajas)){
        printf("Todas las colas estan llenas");
        exit(0);
      } else {
        do{
          numeroCaja = NumeroAleatorio(1, cajas);
        } while (!Queue(colasCajas[numeroCaja - 1], clientesNuevos));
        cantUsuario++;
      }
      #else
      numeroCaja = NumeroAleatorio(1, cajas);
      Queue(colasCajas[numeroCaja - 1], clientesNuevos);
      cantUsuario++;
      #endif
    }

        if(tiempo % tiemposClientes[0] == 0){
      snprintf(clientesNuevos.cliente, sizeof(clientesNuevos.cliente), "N%d", cantNormal);
      #ifdef COLAESTATICA_DISPONIBLE
      if(ColasLlenas(colasCajas, cajas)){
        printf("Todas las colas estan llenas");
        exit(0);
      } else {
        do{
          numeroCaja = NumeroAleatorio(1, cajas);
        } while (!Queue(colasCajas[numeroCaja - 1], clientesNuevos));
        cantNormal++;
      }
      #else
      numeroCaja = NumeroAleatorio(1, cajas);
      Queue(colasCajas[numeroCaja - 1], clientesNuevos);
      cantNormal++;
      #endif
    }

    for(int i = 0; i < cajas; i++){
      direccionMemoriaCaja = colasCajas[i];
      if(tiempo % tiemposCajas[i] == 0 && !Empty(direccionMemoriaCaja)){
        clienteAtendidos = Dequeue(direccionMemoriaCaja);
        clientesSatisfechos++;
        ImprimirCambiosCajas(colasCajas, cajas, arrPosicionesCajas);
        MoverCursor(0, FILAS + 1);
        printf("\nUltimo cliente atendido: Numero.%s en la caja %d\n", clienteAtendidos.cliente, i + 1);
      }
    }
  }
}

#ifdef COLAESTATICA_DISPONIBLE
int ColasLlenas(cola **colasCajas, int cajas){
  int cajasLlenas = 0;
  for(int i = 0; i < cajas; i++){
    if(Size(colasCajas[i]) == TAMAÑO_MAXIMO) cajasLlenas++;
  }
  return cajasLlenas == cajas;
}
#endif