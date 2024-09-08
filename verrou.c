#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int varPar = 0;

pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;//Création et initialisation d'un verrou 

void *afficher1(){
	int tid = pthread_self();
	printf("Je suis le thread 01, mon TID: %d\t", tid);
	pthread_mutex_lock(&verrou);//verrouiler le verrou pour accéder a la sectiion critique
	varPar = varPar + 1;
	printf("varPar = %d\n", varPar);
	pthread_mutex_unlock(&verrou);//déverrouiler le verrou pour libèrer la siction critique
}

void *afficher2(){
	int tid = pthread_self();
	printf("Je suis le thread 02, mon TID: %d\t", tid);
	pthread_mutex_lock(&verrou);//verrouiler le verrou pour accéder a la sectiion critique
	varPar = varPar + 2;
	printf("varPar = %d\n", varPar);
	pthread_mutex_unlock(&verrou);//déverrouiler le verrou pour libèrer la siction critique
}
void *afficher3(){
	int tid = pthread_self();
	printf("Je suis le thread 03, mon TID: %d\t", tid);
	pthread_mutex_lock(&verrou);//verrouiler le verrou pour accéder a la sectiion critique
	varPar = varPar + 3;
	printf("varPar = %d\n", varPar);
	pthread_mutex_unlock(&verrou);//déverrouiler le verrou pour libèrer la siction critique
}

int main(){
	pthread_t th1, th2, th3;
	
	int res1 = pthread_create(&th1, NULL, afficher1, NULL);
	int res2 = pthread_create(&th2, NULL, afficher2, NULL);
	int res3 = pthread_create(&th3, NULL, afficher3, NULL);
	
	if(res1 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);
	}
	
	if(res2 != 0){
		perror("EXHEC");
		exit(EXIT_FAILURE);	
	}
	
	if(res3 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);
	}
	
	res1 = pthread_join(th1, NULL);
	res2 = pthread_join(th2, NULL);
	res3 = pthread_join(th3, NULL);
	
	pthread_mutex_destroy(&verrou);//destructiondu mutex une fois qu'il n'es plus necéssaire
	
	exit(EXIT_SUCCESS);
}
