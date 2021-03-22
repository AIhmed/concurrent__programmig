#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<wait.h>
int drap[2];
int tour =0;
// void donner_tour_a (int* x ){
//         drap[*x]=1;
//         tour=*x;
//         while (drap[1-(*x)]==1 && tour==1-(*x)){printf("sleeping%d",1-(*x));sleep(2);}
//     }
void donner_tour_a (int x ){
	if (x==1){
		drap[x]=1;tour=0;
		while (drap[0]==1&&tour==0){sleep(2);}
	}else if (x==0){
		drap[x]=1;tour=1;
		while (drap[1]==1&&tour==1){sleep(2);}
	}
}
    void init_t (int n,int* t,int* tid){
		donner_tour_a(&tid);
	for (int i = 0; i < n; ++i){*(t+i)=123456;}
		liberer(tid);
}
void afficher_t (int n ,int* t){
	for (int i = 0; i < n; ++i)
	{
		printf("t[%d]=%d le thread courrant :%ld \n",i,*(t+i),pthread_self());
	}
}
void liberer (int x ){drap[x]=0;}
void* set_var(void* arg){
	int* tid = (int*) arg;
	int* a=malloc(6*sizeof(int));
				printf("je suis le thread %ld\n",pthread_self());
				init_t(6,a,tid);
				afficher_t(6,a);
return &a;
}
int main (){
pthread_t tid,tid_;
pthread_create (&tid,NULL,set_var,(int ) 0);
pthread_create (&tid_,NULL,set_var,(int ) 1);
pthread_join(tid,NULL); 
pthread_join(tid_,NULL);
return 0;
}
