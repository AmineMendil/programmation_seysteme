#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>


pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_prod;
sem_t sem_cons;

int nbr_objet = 0;
void *producteur(){
	int tid = pthread_self();
	for(int i = 0; i < 10; i++){
		
		///////
		sem_wait(&sem_prod);//prendre un ticket
		///////
		pthread_mutex_lock(&verrou);//verouiller le verrou
		nbr_objet = nbr_objet + 1;
		printf("Producteur ---> %d \tnombre objet = %d\n", tid, nbr_objet);
		///////
		pthread_mutex_unlock(&verrou);//deverouiller le verrou
		///////
		sem_post(&sem_cons);//rendre le ticket.
	}
}

void *consommateur(){
	int tid = pthread_self();
	for(int i = 0; i < 10; i++){
		///////
		sem_wait(&sem_cons);//prendre un ticket 
		//////
		pthread_mutex_lock(&verrou);//verouiller le verrou
		
		nbr_objet = nbr_objet - 1;
		printf("Consommateur ---> %d \tnombre objet = %d\n", tid, nbr_objet);
		//////
		pthread_mutex_unlock(&verrou);//déverouiller le verrou
		/////
		sem_post(&sem_prod);//rendre le ticket
	}	
}


int main(){
	pthread_t th1, th2;
	
	
	//initialisation des sémaphore.
	sem_init(&sem_prod, 0, 5);
	sem_init(&sem_cons, 0, 0);
	
	int res1 = pthread_create(&th1, NULL, &producteur, NULL);
	int res2 = pthread_create(&th2, NULL, &consommateur, NULL);
	
	if(res1 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);
	}
	
	if(res2 != 0){
		perror("ECHEC");
		exit(EXIT_FAILURE);
	}
	
	res1 = pthread_join(th1, NULL);
	res2 = pthread_join(th2, NULL);
	
	//destcrution des semaphore et de verrou
	sem_destroy(&sem_prod);
	sem_destroy(&sem_cons);
	pthread_mutex_destroy(&verrou);

	exit(EXIT_FAILURE);
	
	return 0;
}
