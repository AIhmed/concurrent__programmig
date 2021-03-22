#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#define BUFF_SIZE 100
typedef struct Message {
	int id ;
	char* ingredient;
	pid_t parent_id;
}Message;
sem_t Sagent;//semaphores pour l'agent 
sem_t mutex;//entre les classes des fumeurs 
int main(){
	int pip[2];
	if (pipe(pip)!=0){
		fprintf(stderr,"erreur opening the pipe \n");
		exit (0);
	}
	char buffer_read [BUFF_SIZE];
	char buffer_write [BUFF_SIZE];
	int child_ids[2];
	Message agent ;
	agent.id = getpid();
	agent.ingredient = "agent";
	int* tab = (int* ) malloc (3*sizeof (int));
	int mem_sh = shmget(IPC_PRIVATE,3*sizeof(Message),IPC_CREAT | IPC_EXCL | 0666);
	Message* smokers =(Message* ) shmat(mem_sh,0,0);
	smokers[0].ingredient = "papers";
	smokers[1].ingredient = "weed";
	smokers[2].ingredient = "lighter";
	sem_init(&Sagent,1,0);
	sem_init(&mutex,6,1);
	printf("creation of processes (smokers) holding either the paper or lighter or the weed \n\n");
		for (int i = 0 ; i < 2 ; i++ ){child_ids[i] = fork();}
		printf("my id is %i my childs ids are : \n child[0]== %i \n child[1]==%i \n\n\n",getpid(),child_ids[0],child_ids[1]);sleep(1);
	if (getpid()==agent.id){smokers[1].id = child_ids[1];}
	if ( child_ids[0]==0 && child_ids[1]==0 ){
		smokers[2].id=getpid();smokers[0].id=getppid();
		sem_wait(&mutex);
		sprintf(buffer_write,"i ask for some %s",smokers[2].ingredient);
		printf("in the critical section gonne be sendind the parent process this message %s \n",buffer_write);
		close(pip[0]);
		sem_post(&Sagent);
		write(pip[1],buffer_write,BUFF_SIZE);
		printf("done writing in the pipe asking for a %s \n",smokers[2].ingredient);
		sem_post(&mutex);
		printf("the writer about to exit \n\n");
		exit(0);
	}
	if ( ( child_ids[0]==0 && child_ids[1]!=0 ) || ( child_ids[0]!=0 && child_ids[1]==0 ) ){
			if (getpid()==smokers[0].id){
				sem_wait(&mutex);
				sprintf(buffer_write,"i ask for some %s",smokers[0].ingredient);
				printf("in the critical section gonne be sendind the parent process this message %s \n",buffer_write);
				close(pip[0]);
				sem_post(&Sagent);
				write(pip[1],buffer_write,BUFF_SIZE);
				printf("done writing on the pipe for asking for %s \n",smokers[0].ingredient);
				sem_post(&mutex);
				printf("the writer about to exit \n\n");
				exit(0);
			}else{
				sem_wait(&mutex);
				sprintf(buffer_write,"i ask for some %s",smokers[1].ingredient);
				printf("in the critical section gonne be sendind the parent process this message %s \n",buffer_write);
				close(pip[0]);
				sem_post(&Sagent);
				write(pip[1],buffer_write,BUFF_SIZE);
				printf("done writing on a pipe asking for a %s \n",smokers[1].ingredient );
				sem_post(&mutex);
				printf("the writer about to exit \n\n");
				exit(0);
			}
	}
	if (getpid()==agent.id){
		printf("in the parent agent process \n");
		//sem_wait(&Sagent);
		for (int i = 0 ; i < 3 ; i++ ) {
			close(pip[1]);
			read(pip[0],buffer_read,BUFF_SIZE);
			printf("the buffer red from the child is :%s\n\n",buffer_read);
		}
	}

}
