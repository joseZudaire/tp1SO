#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <errno.h>

int cantidad;
int terminado;

void P(int,int);
void V(int,int);

int main(int argc, char **argv) {

	cantidad = atoi(argv[1]);
	int semid = semget(1200,3,IPC_CREAT|IPC_EXCL|0600);
	if(errno == EEXIST) {
		printf("\nYa existe un conjunto de semáforos para la clave\n");
	}
	else {
		printf("\nSemid = %d\n", semid);
	}

	semctl(semid,0,SETVAL,1);
	semctl(semid,1,SETVAL,0);
	semctl(semid,2,SETVAL,0);

	if (semid == -1) {
		printf("\nError semget\n");
	}

	while(cantidad > 0){
		P(semid,0);
		cantidad--;
		printf("\nSección crítica del proceso A\n");
		sleep(1);
		V(semid,1);
		P(semid,0);
		printf("\nSección crítica del proceso A\n");
		sleep(1);
		V(semid,2);
	}

	semctl(semid,0,IPC_RMID);
	semctl(semid,1,IPC_RMID);
	semctl(semid,2,IPC_RMID);

	exit(0);

}

void P(int semid, int sem)
{
	struct sembuf buf;
	buf.sem_num = sem;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	semop(semid,&buf,1);
}

void V(int semid, int sem)
{
	struct sembuf buf;
	buf.sem_num = sem;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	semop(semid,&buf,1);
}

