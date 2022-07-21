#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*
Ejercicio 8: Dada una matriz de números enteros M de 4 filas y 3 columnas, dado el vector T de 3 elementos que guardará la sumatoria de cada columna para todas las filas, cada elemento del vector T esta inicializado con -1. 
El programa principal lanza los siguientes hilos: 
hiloQueLlenaMatriz -> hilo que utiliza función random() y llena la matriz con números enteros aleatorios de dos cifras
hiloQueSumaColumna1 -> no puede comenzar su ejecución hasta que hiloQueLlenaMatriz finalice, guarda total en T[0] y chequea los otros totales de T, si están todos disponibles, entonces señala variable de condición V
hiloQueSumaColumna2 -> no puede comenzar su ejecución hasta que hiloQueLlenaMatriz finalice, guarda total en T[1] y chequea los otros totales de T, si están todos disponibles, entonces señala variable de condición V
hiloQueSumaColumna3 -> no puede comenzar su ejecución hasta que hiloQueLlenaMatriz finalice, guarda total en T[2] y chequea los otros totales de T, si están todos disponibles, entonces señala variable de condición V
hiloQueMuestraTotalGeneral -> muestra la sumatoria de T[0..2] , este hilo espera por la variable de condición V
*/

// Compilacion: gcc -Wall -o ejercicio8 ejercicio8.c -pthread

void llenarMatriz();
void sumarColumna(int);
void mostrarTotalGeneral();

pthread_mutex_t mColumna1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mColumna2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mColumna3 = PTHREAD_MUTEX_INITIALIZER;

int M[4][3];
int T[3];
int variableV = 0;

int main(int argc, char **argv) {

	for(int i = 0; i < 3; i++){
		T[i] = (-1);
	}
	
	pthread_mutex_lock(&mColumna1);
	pthread_mutex_lock(&mColumna2);
	pthread_mutex_lock(&mColumna3);
	
	pthread_t hiloQueLlenaMatriz;
	pthread_t hiloQueSumaColumna1;
	pthread_t hiloQueSumaColumna2;
	pthread_t hiloQueSumaColumna3;
	pthread_t hiloQueMuestraTotalGeneral;

	pthread_create(&hiloQueLlenaMatriz, NULL, (void *) llenarMatriz, NULL);
	pthread_create(&hiloQueSumaColumna1, NULL, (void *) sumarColumna, (void*) 0);
	pthread_create(&hiloQueSumaColumna2, NULL, (void *) sumarColumna, (void*) 1);
	pthread_create(&hiloQueSumaColumna3, NULL, (void *) sumarColumna, (void*) 2);
	pthread_create(&hiloQueMuestraTotalGeneral, NULL, (void *) mostrarTotalGeneral, NULL);

	pthread_join(hiloQueLlenaMatriz, NULL);
	pthread_join(hiloQueSumaColumna1, NULL);
	pthread_join(hiloQueSumaColumna2, NULL);
	pthread_join(hiloQueSumaColumna3, NULL);
	pthread_join(hiloQueMuestraTotalGeneral, NULL);

	return 0;
}

void llenarMatriz() {
	int valorAleatorioEntre10Y99 = 0;
	srand(time(0));
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++) {
			valorAleatorioEntre10Y99 = random() % (99 + 1 - 10) + 10;
			M[i][j] = valorAleatorioEntre10Y99;
			printf("En la matriz M[%i][%i] el valor contenido es: %i\n", i, j, M[i][j]);
		}
	}
	
	pthread_mutex_unlock(&mColumna1);
	pthread_mutex_unlock(&mColumna2);
	pthread_mutex_unlock(&mColumna3);
}

void sumarColumna(int nroColumna) {
	int columnasCompletadas = 0;
	
	if (nroColumna == 0) {
		pthread_mutex_lock(&mColumna1);
	}
	else if (nroColumna == 1) {
		pthread_mutex_lock(&mColumna2);
	}
	else if (nroColumna == 2) {
		pthread_mutex_lock(&mColumna3);
	}
	else {
		exit(0);
	}

	for(int i = 0; i < 4; i++) {
		T[nroColumna] = T[nroColumna] + M[i][nroColumna];
	}



	for(int j = 0; j < 3; j++) {
		if(T[j] != 0) {
			columnasCompletadas++;
		}
	}

	if (columnasCompletadas == 3) {
		variableV = 1;
	}
}

void mostrarTotalGeneral() {
	int sumaTotal = 0;
	
	while (variableV == 0);

	for(int i = 0; i < 3; i++){
		printf("\nEl valor de la sumatoria de la columna %i es: %i\n", i, T[i]);
		sumaTotal = sumaTotal + T[i];
	}

	printf("\nEl valor de la suma de las 3 columnas es: %i\n", sumaTotal);
}

