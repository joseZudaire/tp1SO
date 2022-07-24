#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void P ( int semid, int sem ) // semWait
{
	struct sembuf buf ;
	buf.sem_num = sem ;
	buf.sem_op = -1 ;
	buf.sem_flg = 0 ;
	semop (semid,&buf,1) ;
}

void V ( int semid, int sem )  // semSignal
{
	struct sembuf buf ;
	buf.sem_num = sem ;
	buf.sem_op = 1 ;
	buf.sem_flg = 0 ;
	semop (semid,&buf,1) ;
}

