/*
  Archivo donde se definen funciones que se ocuparan en el programa para hacerlo visualmente
  Autor: Covarrubias Sanchez Arturo
*/

// LIBRERIAS
#include "../Cola/ColaEstatica.h"

//CONSTANTES
#define FILAS 40
#define COLUMNAS 84
#define TIEMPO_BASE 100

// Funcion para imprimir vista del supermercado cerrado
void ImprimirInicioSupermercado(char *nombreSupermercado, int tamañoTitulo, int cajas, int *posicionesCajas);

// Funcion para mostrar los cambios en las filas de las cajas
void ImprimirCambiosCajas(cola **arrColasCajas, int cajas, int *arrPosicionesCajas);

// Funcion para obtener los indices donde se tienen que poner los nombres de las cajas en la consola
void PosicionesCajas(int *arrPosicionesCajas, int cajas);

// Funcion que tiene toda la logica mientras el supermercado esta abierto
void AbrirSupermercado(int cajas, int *tiemposCajas, int *arrPosicionesCajas, int tiempoClientes);

// Funcion para hacer esperar al programa por un tiempo constante
void EsperarMiliSeg(int t);

// Funcion para borrar pantalla en la salida del programa
void BorrarPantalla();

// Funcion para limpar informacion sobre las colas en la pantalla
void LimpiarInformacionColas();

// Funcion para desplazar el cursor a una coordenada en especifico de la salida
void MoverCursor(int x, int y);

// Funcion para generar un numero aleatorio entre un rango en especifico
int NumeroAleatorio(int min, int max);

// Funcion para validar si todas las cajas estan llenas
int ColasLlenas(cola **colasCajas, int cajas);