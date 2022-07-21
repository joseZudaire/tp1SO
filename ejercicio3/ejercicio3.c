#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Ejercicio 3: Implementación de una sincronización de los hilos A, B y C de forma tal, que la secuencia de ejecución y acceso a su sección crítica sea la siguiente: ABAC... detener el proceso luego de N iteraciones completas (el número N se ingresa por línea de comandos). Resolver la sincronización con variables Mutex (librería pthread).

// Compilacion: gcc -Wall -o ejercicio3 ejercicio3.c -pthread

int cantidad = 0;
int deboFinalizar = 0;

void tareaHiloA();
void tareaHiloB();
void tareaHiloC();

pthread_mutex_t mA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mC = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) {

	if (argc == 2 && (!strncmp(argv[1],"0",1) || atoi(argv[1]) != 0)) {
		cantidad = atoi(argv[1]);
	} else {
		printf("ERROR: Se debe ingresar un solo argumento y debe ser numérico\n");
		return (-1);
	}
	
	pthread_mutex_lock(&mB);
	pthread_mutex_lock(&mC);

	pthread_t hiloA;
	pthread_t hiloB;
	pthread_t hiloC;

	pthread_create(&hiloA, NULL, (void *) tareaHiloA, NULL);
	pthread_create(&hiloB, NULL, (void *) tareaHiloB, NULL);
	pthread_create(&hiloC, NULL, (void *) tareaHiloC, NULL);

	pthread_join(hiloA, NULL);

	printf("\n");
	
	return 0;
}

void tareaHiloA() {

	while (cantidad > 0) {
		pthread_mutex_lock(&mA);
		if (deboFinalizar) { break; }
		printf("A");
		pthread_mutex_unlock(&mB);
		pthread_mutex_lock(&mA);
		
		printf("A");
		pthread_mutex_unlock(&mC);
	}
}

void tareaHiloB() {

	while (cantidad > 0) {
		pthread_mutex_lock(&mB);
		if (deboFinalizar) { break; }
		printf("B");
		pthread_mutex_unlock(&mA);
	}
}

void tareaHiloC() {

	while (cantidad > 0) {
		pthread_mutex_lock(&mC);
		printf("C ");
		cantidad--;
		if (cantidad == 0) {
			deboFinalizar = 1;
			pthread_mutex_unlock(&mA);
			pthread_mutex_unlock(&mB);
			break;
		} else {
			pthread_mutex_unlock(&mA);
		}
	}
}
