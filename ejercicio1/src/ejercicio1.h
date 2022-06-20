/*
 ============================================================================
 Name        : ejercicio3.c
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

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


int main(int argc, char **argv) {

	//int iteraciones = atoi(argv[0]);
	//printf("\nArgv: %s", argv[1]);
	//printf("\nArgv: %i", atoi(argv[1]));
	cantidad = atoi(argv[1]);
	//printf("\nIteraciones: %i", cantidad);
	//int iteraciones;// = (int) argv[0];

	//printf("\ncantidad: %i", cantidad);

	//cantidad = iteraciones;

	//printf("Entramos al main2");
	//char comando[256];
	//fgets(comando, 256, stdin);
	//comando[strlen(comando)-1] = '\0';
	//cantidad = atoi(argv[1]);


	pthread_t hiloA;
	pthread_t hiloB;
	pthread_t hiloC;

	pthread_create(&hiloA, NULL, (void *) tareaHiloA, NULL);
	pthread_create(&hiloB, NULL, (void *) tareaHiloB, NULL);
	pthread_create(&hiloC, NULL, (void *) tareaHiloC, NULL);

	pthread_mutex_lock(&mB);
	pthread_mutex_lock(&mC);

	pthread_join(hiloC, NULL);
	pthread_join(hiloB, NULL);
	pthread_join(hiloA, NULL);

	//puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	/*while((int) cantidad > 0){
		printf("\nIteraciones:%i\n", cantidad);
	}*/
	while(cantidad>0);
	//exit(NULL);
	return 0;
}

void tareaHiloA() {

	//printf("\nEn el hilo A el valor que entra es: %i\n", (int) cantidad);
	//printf("\nEn el hilo A el valor que entra es: %i\n", (int) cantidad);
	//printf("\nEn el hilo A el valor que entra es: %i\n", cantidad);

	//int cantIteraciones = (int) cantidad;

	while(cantidad > 0) {


		//printf("\nadentro2\n");
		//printf("\nEntramos3\n");

		//printf("\nEl valor de decremento es: %i\n", decremento);
		pthread_mutex_lock(&mA);
		cantidad = cantidad - 1;
		printf("\nA");

		//fflush(stdin);
		pthread_mutex_unlock(&mB);
		//decremento = 1;
		pthread_mutex_lock(&mA);
		printf("\nA");
		pthread_mutex_unlock(&mC);


		//decremento = 0;
		//printf("\nEl valor de decremento es: %i\n", decremento);

		//printf("\nCantidad:%i\n", (int) cantidad);
	}
	printf("\nSe terminó el hiloA\n");
	pthread_exit(NULL);
	//printf("\nHola desde hilo A\n");
}

void tareaHiloB() {

	while(cantidad > 0) {
		//printf("\nEl valor de B es: %i", (int) cantidad);
		//printf("\nEntramos en while del hiloB\n");
		pthread_mutex_lock(&mB);
		printf("\nB");
		pthread_mutex_unlock(&mA);

		if(cantidad == 0) {
			printf("\nSe terminó el hiloB\n");
			pthread_exit(NULL);
		}

		//while(decremento != 0) {
			//sleep(1);
			//printf("\nHilo B: El valor decremento es: %i\n", decremento);
		//}
		//printf("\nEstamos en B\n");
		//printf("\nEstamos en B en el while\n");
		//cantidad = cantidad - 1;
		//sleep(4);
	}
	printf("\nSe terminó el hiloB\n");
	pthread_exit(NULL);
}

void tareaHiloC() {

	while((int) cantidad > 0) {
		//printf("\nEl valor de C es: %i", (int) cantidad);
		//printf("\nEntramos en while del hiloC\n");
		pthread_mutex_lock(&mC);
		printf("\nC\n");
		pthread_mutex_unlock(&mA);
		if(cantidad == 0) {
			printf("\nSe terminó el hiloC\n");
			pthread_exit(NULL);
		}

		//while(decremento != 0) {
			//sleep(1);
			//printf("\nHilo C: El valor decremento es: %i\n", decremento);
		//}
		//printf("\nEstamos en C en el while\n");
		//cantidad = cantidad - 1;
		//sleep(1);
	}
	printf("\nSe terminó el hiloC\n");
	pthread_exit(NULL);
}
