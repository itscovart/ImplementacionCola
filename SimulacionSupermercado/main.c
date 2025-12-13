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

// CONSTANTES
#define TAMAÑO_NOMBRE 80

// Funcion Principal
int main(int argc, char *argv[]){
  char *nombreSupermercado = malloc(TAMAÑO_NOMBRE * sizeof(char));
  int cajas, tiempoClientes, *tiemposCajas, tamañoTitulo, abrirSupermercado, *posicionesCajas;

  if(argc != 3){
    printf("Error en los datos de la ejecucion.\nEjemplo: %s ESCOMarket 6", argv[0]);
    exit(1);
  }

  tamañoTitulo = snprintf(
    nombreSupermercado,
    TAMAÑO_NOMBRE,
    "%s",
    argv[1]
  );

  cajas = atoi(argv[2]);
  if(cajas <= 0 || cajas > 10){
    printf("El numero de cajas tiene que estar entre 1 y 10");
    exit(1);
  }

  tiemposCajas = malloc(cajas * sizeof(int));
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

  printf("Ingresa el tiempo(ms * 10) que se tardan en llegar los clientes: ");
  scanf("%d", &tiempoClientes);
  if(tiempoClientes < 0){
    printf("No se pueden ingresar tiempos negativos");
    exit(1);
  }

  ImprimirInicioSupermercado(nombreSupermercado, tamañoTitulo, cajas, posicionesCajas);
  printf("1. Si\n2. No\nDeseas abrir %s?: ", nombreSupermercado);
  scanf("%d", &abrirSupermercado);
  if(abrirSupermercado == 1){
    AbrirSupermercado(cajas, tiemposCajas, posicionesCajas, tiempoClientes, nombreSupermercado);
  } else {
    printf("Destruyendo %s...", nombreSupermercado);
    exit(0);
  }

  free(tiemposCajas);
  free(posicionesCajas);
  exit(0);
}
