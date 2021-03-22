#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
int main(){
	int shm_id = shmget(IPC_PRIVATE,3*sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
	int* childs = shmat(shm_id,0,0);
	pid_t parent_id = getpid();
	pid_t child_id[3];
	printf("parent id is %i \n\n",getpid());
	for (int i = 0 ; i < 2 ; i++ ){
		child_id[i] = fork();
	}
		printf("my pid is  == %i \n ",getpid());
		printf("child_id[%i] == %i \nchild_id[%i] == %i \n\n\n\n",(int )0,child_id[0],(int )1,child_id[1]);
	if (getpid()==parent_id){
		childs[0]=child_id[0];
		childs[1]=child_id[1];
	}

	if (child_id[0]==0 && child_id[1]==0 ){
	printf("in the last childs my pid is %i my parent id is %i \n\n",getpid(),getppid());
	childs[2]=getpid();
	exit(0);
	}
	if (getpid()==parent_id){
	wait(0);
	printf("in the father section will after waitnig for the child processes \n\n");}
	for (int i = 0 ; i < 3 ; i++ ){
		printf ("child[%i] == %i \n\n",i,childs[i]);
	}
}