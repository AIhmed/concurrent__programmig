#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define BUFFER_SIZE 256
int main(void){
pid_t pid_fils;
int tube[2];
unsigned char bufferR[256], bufferW[256];
puts("creation d’un tube");
if (pipe(tube) !=0){
fprintf(stderr, "erreur dans pipe\n");
exit(1);
}
pid_fils=fork();
if (pid_fils == -1){
	fprintf(stderr, "erreur dans pipe\n");
	exit(1);
}
if (pid_fils == 0)
/*processus fils*/
{
printf("fermeture entrée dans le fils (pid = %d)\n", getpid());
close(tube[1]);
read(tube[0], bufferR, BUFFER_SIZE);
printf ("le fils (%d) a lu : %s\n", getpid(), bufferR);
}
else
{
printf ("fermeture sortie dans le père (pid=%d)\n",getpid());
close(tube[0]) ;
sprintf(bufferW, " Message du père (%d) au fils", getpid()) ;
write(tube[1], bufferW, BUFFER_SIZE);
wait(NULL);
}
return 0 ;
}/*
printf("%d\n",y );
int pip=mkfifo("pipy",0644);
int desc=open("pipy",O_WRONLY);
int send_taille= write(desc,(char) y,BUFF);*/
