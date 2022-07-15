#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int cantidad, decremento;

void tareaHiloA();
void tareaHiloB();
void tareaHiloC();

pthread_mutex_t mA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mC = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mNuevaIteracionHiloB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mNuevaIteracionHiloC = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) {

	if (argc == 2 && (!strncmp(argv[1],"0",1) || atoi(argv[1]) != 0)) {
		cantidad = atoi(argv[1]);
	} else {
		printf("ERROR: Se debe ingresar un solo argumento y debe ser numérico\n");
		return (-1);
	}

	pthread_t hiloA;
	pthread_t hiloB;
	pthread_t hiloC;

	pthread_create(&hiloA, NULL, (void *) tareaHiloA, NULL);
	pthread_create(&hiloB, NULL, (void *) tareaHiloB, NULL);
	pthread_create(&hiloC, NULL, (void *) tareaHiloC, NULL);

	pthread_mutex_lock(&mB);
	pthread_mutex_lock(&mC);
	pthread_mutex_lock(&mNuevaIteracionHiloB);
	pthread_mutex_lock(&mNuevaIteracionHiloC);

	pthread_join(hiloC, NULL);
	pthread_join(hiloB, NULL);
	pthread_join(hiloA, NULL);

	while(cantidad>0);
	return 0;
}

void tareaHiloA() {

	while(cantidad > 0) {

		pthread_mutex_lock(&mA);

		printf("\nA");

		pthread_mutex_unlock(&mB);

		pthread_mutex_lock(&mA);
		printf("\nA");
		pthread_mutex_unlock(&mC);
		cantidad = cantidad - 1;
		pthread_mutex_unlock(&mNuevaIteracionHiloB);
		pthread_mutex_unlock(&mNuevaIteracionHiloC);

	}
	printf("\nSe terminó el hiloA\n");
	pthread_exit(NULL);
}

void tareaHiloB() {

	while(cantidad > 0) {
		pthread_mutex_lock(&mB);
		printf("\nB");
		pthread_mutex_unlock(&mA);

		pthread_mutex_lock(&mNuevaIteracionHiloB);

	}
	printf("\nSe terminó el hiloB\n");
	pthread_exit(NULL);
}

void tareaHiloC() {

	while((int) cantidad > 0) {
		pthread_mutex_lock(&mC);
		printf("\nC\n");
		pthread_mutex_unlock(&mA);
		pthread_mutex_lock(&mNuevaIteracionHiloC);

	}
	printf("\nSe terminó el hiloC\n");
	pthread_exit(NULL);
}
