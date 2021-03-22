#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <wait.h>
int main(int argc, char const *argv[]){
	int mem_sh = shmget(IPC_PRIVATE,3*sizeof(int), IPC_CREAT | IPC_EXCL | 0666) ;
	int* shmt =(int*) shmat(mem_sh,0,0);
shmt[0]=0;//on represente le tour des deux processus avec 0 pour le pere ou 1 pour le fils 
shmt[1]=0;//drapeau[1] drapeau du pere 
shmt[2]=0;//drapeau[2] drapeau du fils 
int var;
pid_t pid ;
	pid=fork();
	if (pid==0)
	{
	shmt[2]=1;shmt[0]=0;// tour du processus concurent (pere) et flag egale a 1 
	while (shmt[1]==1&&shmt[0]==1){printf("the process child  0 will wait : %d \n",getpid());}
	var=10;
	printf("yeeeeeeeeeeeeeeeeeeeeeeeeees i'm son %d\n\n\n",var);
	for (int i = 0; i < 7; ++i)
	{
		printf("the son pid : %d \n\n\n",getpid());
	}
	shmt[1]=0;
	}else{
	shmt[1]=1;shmt[0]=1;// tour du processus concurent (fils)) et flag egale a 0  
	while (shmt[2]==1&&shmt[0]==0){printf("the father  1 will wait : %d \n",getpid());}
	var=5;
	printf("yeeeeeeeeeeeeeeeeeeeeeeeees i'm the father %d\n\n\n",var);
	for (int i = 0; i < 7; ++i)
	{
		printf(" the father pid : %d \n\n\n",getpid());
	}
	shmt[2]=0;
	}
	return 0;
	printf("%d\n",var);
}