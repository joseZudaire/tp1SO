#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int cantidad = 0;

int main(int argc, char **argv) {

	cantidad = atoi(argv[1]);

	printf("\nEl valor que le pasamos para imprimir es: %i\n", cantidad);

	return 0;
}


