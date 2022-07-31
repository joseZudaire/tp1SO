#include <stdio.h>
#include <stdlib.h>
#include <operIPC.h>

// Compilacion: gcc -Wall -o ejercicio6ProcesoB ejercicio6ProcesoB.c -I.

int main(int argc, char **argv) {
	int cantidad = 0;

	int semid = semget(0xa, 0, 0);
	if (semid == (-1)) {
		printf("Error de semget en la dirección 0xa. Verificar existencia de semáforos\n");
		return (-1);
	} 
	
	cantidad = atoi(argv[0]);

	while(cantidad > 0) {
		P(semid,1);
		cantidad--;
		printf("B\n");
		V(semid,0);
	}

	return 0;
}
