/*
  Codigo que simula el funciomiento de atencion de clientes dentro de un supermercado usando como pilar de funcionamiento una estructura de datos en este caso una cola
  Autor: Covarrubias Sanchez Arturo
  Fecha: 12/12/25
*/

// LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./utils/logica.h"

// Funcion Principal
int main(int argc, char *argv[]){
  char nombreBanco[5] = "BANCO";
  char *tipoCliente[3] = {"Normal", "Usuario", "Preferente"};
  int cajas, *tiemposCajas, tamañoTitulo, abrirBanco, *posicionesCajas, *tiemposClientes;

  if(argc != 2){
    printf("Error en los datos de la ejecucion.\nEjemplo: %s 6", argv[0]);
    exit(1);
  }

  cajas = atoi(argv[1]);
  if(cajas <= 0 || cajas > 10){
    printf("El numero de cajas tiene que estar entre 1 y 10");
    exit(1);
  }

  tiemposCajas = malloc(cajas * sizeof(int));
  if(!tiemposCajas){
    printf("Error al reservar memoria");
    exit(1);
  }

  tiemposClientes = malloc(cajas * sizeof(int));
  if(!tiemposCajas){
    printf("Error al reservar memoria");
    exit(1);
  }

  posicionesCajas = malloc(cajas * sizeof(int));
  if(!posicionesCajas){
    printf("Error al reservar memoria para posicionesCajas\n");
    exit(1);
  }

  for(int i = 0; i < cajas; i++){
    printf("Ingresa el tiempo(ms * 10) en que la caja %d se tarda en atender un cliente: ", (i + 1));
    scanf("%d", &tiemposCajas[i]);
    if(tiemposCajas[i] < 0){
      printf("No se pueden ingresar tiempos negativos");
      exit(1);
    }
  }

  for(int i = 0; i < 3; i++){
    printf("Ingresa el tiempo(ms * 10) en que el cliente %s se tarda en atender en llegar: ", tipoCliente[i]);
    scanf("%d", &tiemposClientes[i]);
    if(tiemposClientes[i] < 0){
      printf("No se pueden ingresar tiempos negativos");
      exit(1);
    }
  }

  ImprimirInicioBanco(nombreBanco, tamañoTitulo, cajas, posicionesCajas);
  printf("1. Si\n2. No\nDeseas abrir %s?: ", nombreBanco);
  scanf("%d", &abrirBanco);
  if(abrirBanco == 1){
    AbrirBanco(cajas, tiemposCajas, posicionesCajas, tiemposClientes, nombreBanco);
  } else {
    printf("Destruyendo %s...", nombreBanco);
    exit(0);
  }

  free(tiemposCajas);
  free(posicionesCajas);
  exit(0);
}
