#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int cantidad, decremento;

pid_t pid;
int salir;

int main(int argc, char **argv) {

	int pipe1[2]; // pipe1[0] -> lectura  pipe1[1] -> escritura
	pipe(pipe1);

	pid = fork();
	if(pid == 0){
		//hijo
		close(pipe1[0]);
		char *args[argc];

		for(int i = 0; i < (argc - 1); i++){
			args[i] = argv[i+1];
			
		}
		args[argc-1] = NULL;

		dup2(pipe1[1], STDOUT_FILENO);
		execvp(args[0], args);
		close(pipe1[1]);
		exit(0);
	}
	else {
		//padre
		close(pipe1[1]);
		wait(0);
		char linea[255];
		int n;
		n = read(pipe1[0],linea,255);
		linea[n]='\0';
		printf("\nLei del pipe: %s\n", linea);
		close(pipe1[0]);


	}


	return 0;
}





