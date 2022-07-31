#include <stdio.h>
#include <stdlib.h>
#include <operIPC.h>

// Compilacion: gcc -Wall -o ejercicio6ProcesoA ejercicio6ProcesoA.c -I.

int main(int argc, char **argv) {
	int cantidad = 0;

	int semid = semget(0xa, 0, 0);
	if (semid == (-1)) {
		printf("Error de semget en la dirección 0xa. Verificar existencia de semáforos\n");
		return (-1);
	} 
	
	cantidad = atoi(argv[0]);

	while(cantidad > 0) {
		P(semid,0);
		cantidad--;
		printf("A\n");
		V(semid,1);
		P(semid,0);
		printf("A\n");
		V(semid,2);
	}

	return 0;
}
