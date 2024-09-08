#include <stdlib.h> //Exit    //wait
#include <stdio.h>  //printf  //sacnf
#include <pthread.h> //pthred_t  pthread_self   //pthread_create  //pthread_join
#include <semaphore.h>

int varPar = 0;
sem_t sem;

void *additionner1(){
	int tid = pthread_self();
	printf("Je suis le Thread 01, mon TID est: %d\t", tid);
	sem_wait(&sem);//attente sur le sémaphore(décrimente le sémaphore).
	varPar = varPar + 1;
	printf("varPar = %d\n", varPar);
	sem_post(&sem);//poste sur le sémaphore (incrémente le sémaphore).
}

void *additionner2(){
	int tid = pthread_self();
	printf("Je suis le thread 02, mon TID est: %d\t", tid);
	sem_wait(&sem);
	varPar = varPar + 2;
	printf("varPar = %d\n", varPar);
	sem_post(&sem);
}

void *additionner3(){
	int tid = pthread_self();
	printf("Je suis le thread 03, mon TID est: %d\t", tid);
	sem_wait(&sem);
	varPar = varPar + 3;
	printf("varPar = %d\n", varPar);
	sem_post(&sem);
}

int main(){
	pthread_t th1, th2, th3;
	sem_init(&sem, 0, 1);//initialisation du sémaphore avec une valeur 1
	
	int res1 = pthread_create(&th1, NULL, additionner1, NULL);
	int res2 = pthread_create(&th2, NULL, additionner2, NULL);
	int res3 = pthread_create(&th3, NULL, additionner3, NULL);
	
	if(res1 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);
	}
	
	if(res2 != 0){
		printf("ECHEC");
		exit(EXIT_FAILURE);
	}
	
	if(res3 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);
	}
	
	res1 = pthread_join(th1, NULL);
	res2 = pthread_join(th2, NULL);
	res3 = pthread_join(th3, NULL);
	
	sem_destroy(&sem);//destruction de sémaphore.
	
	exit(EXIT_SUCCESS);

}
