#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

int cantidad;
int terminado;

void f_sigint(int);

int main(int argc, char **argv) {

	pid_t pid;
	terminado = 0;
	cantidad = atoi(argv[1]);

	signal(SIGINT,(void*)f_sigint);
	signal(SIGUSR1,(void*)f_sigint);

	for(int i = 0; i < cantidad; i++) {
		pid = fork();
		if(pid == 0) {
			printf("\nProceso nuevo creado: mi PID es %i\n", getpid());
			break;
		}
	}

	if(pid != 0){
		int sumaTotal = 0;
		int resultadoProceso = 0;

		for(int i = 0; i < cantidad; i++) {
			resultadoProceso = waitpid(0,0,0);
			sumaTotal = sumaTotal + resultadoProceso;
		}
		printf("\nLa sumatoria de los resultados de cada proceso es: %i\n", sumaTotal);
	}
	else {
		while(terminado == 0);
	}

	return getpid();

}

void f_sigint(int s) {
	//printf("\nSeñal de interrupción está activada\n");
	terminado = 1;
}

