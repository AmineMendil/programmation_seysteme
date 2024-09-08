#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>

//variable partager qui seras modifier par les trois thread.
int varPartager = 0;

//fonction que th1 vas exécuter.
void *incrementer1(){
	int tid = pthread_self();
	printf("Je suis le thread 01, mon TID est: %d\t", tid);
	varPartager = varPartager + 1;
	printf("varPartager = %d\n", varPartager);
} 

//fonction que th2 vas exécuter.
void *incrementer2(){
	int tid = pthread_self();
	printf("Je suis le thread 02, mon TID est: %d\t", tid);
	varPartager = varPartager + 5;
	printf("varPartager = %d\n", varPartager);
} 

//fonction que th3 vas exécuter.
void *incrementer3(){
	int tid = pthread_self();
	printf("Je suis le thread 03, mon TID est: %d\t", tid);
	varPartager = varPartager + 1;
	printf("varPartager = %d\n", varPartager);
} 

int main(){
	
	int tprinc = pthread_self();//Récupération de l'identifiant de thread principal
	pthread_t th1, th2, th3; //déclaration des thread afin de stocker leurs identifiants (TID)
	printf("Je suis le thread principal, mon TID est: %d\n", tprinc);
	
	/*création des thread . qui vont exécuter les fonction*/
	int res1 = pthread_create(&th1, NULL, incrementer1, NULL);
	int res2 = pthread_create(&th2, NULL, incrementer2, NULL);
	int res3 = pthread_create(&th3, NULL, incrementer3, NULL);
	
	
	
	if(res1 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);//permet de terminer immediatement le programme.
	}
	
	if(res2 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);//permet de terminer immediatement le programme.
	}
	
	if(res3 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);//permet de terminer immediatement le programme.
	}
	
	/*sert à la synchronisation entre les threads. elle bloque le thread principal
	en attendant que le thread fils termine son exécution.*/
	res1 = pthread_join(th1, NULL);
	res2 = pthread_join(th2, NULL);
	res3 = pthread_join(th3, NULL);
	
	exit(EXIT_SUCCESS);//terminer l'exécution du programme et d'indiquer une fin d'exécution réussie.

	return 0;
}

















