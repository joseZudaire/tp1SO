#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Compilacion: gcc -Wall -o ejercicio9 ejercicio9.c

int main(int argc, char **argv) {
	int pipe1[2]; // pipe1[0] -> lectura | pipe1[1] -> escritura
	
	pipe(pipe1);
	
	pid_t pid = fork();
	if(pid == 0){
		// Hijo
		close(pipe1[0]);
		char *args[argc];

		for (int i = 0; i < (argc - 1); i++) {
			args[i] = argv[i+1];		
		}
		
		args[argc-1] = NULL;
		dup2(pipe1[1], STDOUT_FILENO);
		execvp(args[0], args);
		close(pipe1[1]);
		exit(0);
	} else {
		// Padre
		close(pipe1[1]);
		wait(0);
		char linea[255];
		int n;
		n = read(pipe1[0],linea,255);
		linea[n]='\0';
		printf("Lei del pipe: \n%s", linea);
		close(pipe1[0]);
	}
	return 0;
}
