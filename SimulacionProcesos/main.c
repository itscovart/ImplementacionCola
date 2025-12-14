/*
  Simulador de cola de procesos que se finalizan de forma uno por uno o con un tiempo constante para todos
  Autor: Covarrubias Sanchez Arturo
*/

// LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Utils/logica.h"

int main(int argc, char *argv[]){
  cola *procesosRestantes = malloc(sizeof(cola));
  cola *procesosCompletados = malloc(sizeof(cola));

  if(!procesosRestantes || !procesosCompletados){
    printf("Error al asignar memorio");
    exit(1);
  }
  int cantProcesos, tiempo = 0;

  if(argc != 2){
    printf("Error al ejecutar el programa. Ejemplo: %s 10", argv[0]);
    exit(1);
  }

  cantProcesos = atoi(argv[1]);

  Inicializar(procesosRestantes);

  for(int i = 0; i < cantProcesos; i++){
    elemento infoProceso;

    BorrarPantalla();

    printf("Ingresa la siguiente informacion para el proceso no.%d\n", (i + 1));
    printf("Nombre del proceso: ");
    fgets(infoProceso.nombreProceso, sizeof(infoProceso.nombreProceso), stdin);
    infoProceso.nombreProceso[strcspn(infoProceso.nombreProceso, "\n")] = '\0';
    
    printf("Actividad: ");
    fgets(infoProceso.actividad, sizeof(infoProceso.actividad), stdin);
    infoProceso.actividad[strcspn(infoProceso.actividad, "\n")] = '\0';
    
    printf("ID: ");
    fgets(infoProceso.ID, sizeof(infoProceso.ID), stdin);
    infoProceso.ID[strcspn(infoProceso.ID, "\n")] = '\0';

    printf("Tiempo de proceso (ms): ");
    scanf("%d", &infoProceso.tiempoProcesoMS);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if(!Queue(procesosRestantes, infoProceso)){
      printf("Error al encolar el proceso no.%d", (i + 1));
    }
  }

    Inicializar(procesosCompletados);

    while(!Empty(procesosRestantes)){
      BorrarPantalla();
      EsperarMilisegundos(TIEMPO_BASE);
      tiempo++;
      
      elemento procesoEjecucion = Front(procesosRestantes), procesoCompletado;
      
      if(tiempo % procesoEjecucion.tiempoProcesoMS == 0){
        procesoCompletado = Dequeue(procesosRestantes);
        printf("Finalizado el proceso de %s\n", procesoCompletado.nombreProceso);
        Queue(procesosCompletados, procesoCompletado);
        tiempo = 0;
      }

      printf("Proceso en Ejecucion:\nNombre: %s\nID: %s\nActividad: %s\nTiempo Restante: %dms\nTiempo Procesado: %dms\n", procesoEjecucion.nombreProceso, procesoEjecucion.ID, procesoEjecucion.actividad, (procesoEjecucion.tiempoProcesoMS - tiempo), tiempo);
      printf("\nProcesos Restantes:\n");
      ImprimirCola(procesosRestantes, 0, tiempo);
      printf("\nProcesos Completados:\n");
      ImprimirCola(procesosCompletados, 1, tiempo);
      
    }
  exit(0);
}