#include <stdio.h>
#include <sys/sem.h>

// Compilacion: gcc -Wall -o ejercicio6Sem_del ejercicio6Sem_del.c

int main(void) {
	int semid = semget(0xa, 0, 0);
	
	if (semid != (-1)) {
		printf("\nDestrucción de los semáforos con éxito\n");
		printf("semid %d\n\n",semid);
		semctl(semid,0 , IPC_RMID);
		return 0;     
	} else {
		printf("Error de semget en la dirección 0xa. Verificar existencia de semáforos\n");
		return (-1);
	}
	
	return 0;
}


