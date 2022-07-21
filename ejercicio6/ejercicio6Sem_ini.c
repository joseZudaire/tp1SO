#include <stdio.h>
#include <sys/sem.h>

// Compilacion: gcc -Wall -o ejercicio6Sem_ini ejercicio6Sem_ini.c

int main(void) {
	int semid = semget(0xa, 3 , IPC_CREAT | IPC_EXCL | 0700);
	
	if (semid != (-1)) {
		printf("\nInicialización de semáforos con éxito\n");
		printf("semid = %d\n",semid);
		semctl(semid, 0, SETVAL, 1);
		semctl(semid, 1, SETVAL, 0);
		semctl(semid, 2, SETVAL ,0);
		printf("sem_A = %d\n",semctl(semid,0,GETVAL));
		printf("sem_B = %d\n",semctl(semid,1,GETVAL));
		printf("sem_C = %d\n\n",semctl(semid,2,GETVAL));
	} else {
		printf("Error de semget en la dirección 0xa. Verificar existencia de semáforos\n");
		return (-1);
	}

	return 0;
}
