#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int cantidad, decremento;

void llenarMatriz();
void sumarColumna(int);
void mostrarTotalGeneral();

pthread_mutex_t mColumna1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mColumna2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mColumna3 = PTHREAD_MUTEX_INITIALIZER;

int M[4][3];
int T[3];
int variableV;
int salir;

int main(int argc, char **argv) {

	pthread_t hiloQueLlenaMatriz;
	pthread_t hiloQueSumaColumna1;
	pthread_t hiloQueSumaColumna2;
	pthread_t hiloQueSumaColumna3;
	pthread_t hiloQueMuestraTotalGeneral;

	for(int i = 0; i < 3; i++){
		T[i] = 0;
	}

	variableV = 0;
	salir = 0;

	pthread_create(&hiloQueLlenaMatriz, NULL, (void *) llenarMatriz, NULL);
	pthread_create(&hiloQueSumaColumna1, NULL, (void *) sumarColumna, (void*) 0);
	pthread_create(&hiloQueSumaColumna2, NULL, (void *) sumarColumna, (void*) 1);
	pthread_create(&hiloQueSumaColumna3, NULL, (void *) sumarColumna, (void*) 2);
	pthread_create(&hiloQueMuestraTotalGeneral, NULL, (void *) mostrarTotalGeneral, NULL);

	pthread_mutex_lock(&mColumna1);
	pthread_mutex_lock(&mColumna2);
	pthread_mutex_lock(&mColumna3);

	pthread_join(hiloQueLlenaMatriz, NULL);
	pthread_join(hiloQueSumaColumna1, NULL);
	pthread_join(hiloQueSumaColumna2, NULL);
	pthread_join(hiloQueSumaColumna3, NULL);
	pthread_join(hiloQueMuestraTotalGeneral, NULL);

	while(salir == 0);

	return 0;
}

void llenarMatriz() {
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++) {
			M[i][j] = (random()%100) + (random()%10);
			printf("\nEn la matriz M[%i][%i] el valor contenido es: %i", i, j, M[i][j]);
		}
	}
	pthread_mutex_unlock(&mColumna1);
	pthread_mutex_unlock(&mColumna2);
	pthread_mutex_unlock(&mColumna3);

	printf("\nSe terminó el hilo de llenado de Matrices\n");
	pthread_exit(NULL);
}

void sumarColumna(int nroColumna) {
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
		exit(NULL);
	}

	for(int i = 0; i < 4; i++) {
		T[nroColumna] = T[nroColumna] + M[i][nroColumna];
	}

	int columnasCompletadas = 0;

	for(int j = 0; j < 3; j++) {
		if(T[j] != 0){
			columnasCompletadas++;
		}
	}

	if(columnasCompletadas == 3) {
		variableV = 1;
	}

	printf("\nSe terminó el hilo de suma de Columnas %i\n", nroColumna);
	pthread_exit(NULL);
}

void mostrarTotalGeneral() {
	while(variableV == 0);

	int sumaTotal = 0;

	for(int i = 0; i < 3; i++){
		printf("\nEl valor de la sumatoria de la columna %i es: %i\n", i, T[i]);
		sumaTotal = sumaTotal + T[i];
	}

	printf("\nEl valor de la suma de las 3 columnas es: %i", sumaTotal);
	printf("\nSe terminó el hilo de muestra del Total General\n");
	salir = 1;
	pthread_exit(NULL);

}



