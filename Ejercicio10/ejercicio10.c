#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main() {

	char comando[50];
	char* unComando = getenv("QUERY_STRING");

	strncpy(comando, unComando, strlen(unComando)+1);

	char* token = strtok(comando, "&");
	strtok(NULL, "=");

	char* tokenArgumentos[10];
	int k = 0;
	tokenArgumentos[k] = strtok(NULL, "+");

	while(tokenArgumentos[k]!=NULL) {
		k++;
		tokenArgumentos[k] = strtok(NULL, "+");
	}

	char* tokenComando = strtok(token, "=");
	tokenComando = strtok(NULL, "=");

	//Defino el tipo de salida HTML
	printf("Content-type: text/html\n\n");
	printf("<html>\n");
	printf("<body>\n");
	printf("<h1>El comando ingresado fue: ");
	printf("%s</h1>\n", tokenComando);
	printf("<h1>Los argumentos ingresados fueron: ");
	int j = 0;
	while(tokenArgumentos[j] != NULL) {
		printf("%s ", tokenArgumentos[j]);
		j++;
	}
	printf("</h1>\n");

	int pipe1[2];
	pipe(pipe1);

	pid_t pid;
	pid = fork();
	if(pid == 0){
		//hijo
		close(pipe1[0]);

		char *args[11];

		args[0] = tokenComando;

		for(int i = 0; i < 10; i++){
			args[i+1] = tokenArgumentos[i];

		}

		dup2(pipe1[1], STDOUT_FILENO);
		execvp(tokenComando, args);
		close(pipe1[1]);
		exit(0);
	}
	else {
		//padre
		close(pipe1[1]);
		wait(0);
		char linea[10000];
		int n;
		n = read(pipe1[0],linea,10000*sizeof(char));
		linea[n]='\0';
		printf("\n<h1>Output: %s</h1>\n", linea);
		close(pipe1[0]);


	}





	//printf("<h1>Los argumentos que tiene son: ");
	//printf("%s</h1>\n", getenv("QUERY_STRING"));

	printf("</body>\n");
	printf("</html>\n");

	return 0;
}





