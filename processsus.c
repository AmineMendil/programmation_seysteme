#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*La fonction execl("chemin", "nom_commande", "option", NULL) permet de remplacer le processus en cours d'exécution par un nouveau processus*/

int main (void){
	
	int status;
	int pid1 = fork();
	
	if(pid1 == 0){
	
		printf("je suis le fils 01, mon pid est: %d\n", getpid());
		execl("/bin/ps", "ps", "-l", NULL);
		exit(0);
	}else if(pid1 > 0){
	
		int pid2 = fork();
		
		if(pid2 == 0){
		
			printf("Je suis le fils 02, mon pid est: %d\n", getpid());
			execl("/bin/ls", "ls", "-l", NULL);
			exit(0);
		}else if(pid2 > 0){
			int a = wait(&status);
			printf("je suis le père, mon pid est: %d\n", getpid());
			
		}else{
			printf("ECHEC");
		}
	
		
	}else{
		printf("ECHEC");
	}
	
	
	
	
	return 0;
}
