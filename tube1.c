#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define BUFF 256
#define OBUFFER 16
char bfw[BUFF];
int main(int argc, char const *argv[])
{
	printf("buffer a envoyer\n");
	scanf("%s",bfw);
int pipe= mkfifo("pipy",2000);
int pipe_responce = mkfifo("pipe_answer",4000);
int desc=open("pipy",O_WRONLY);
int desc_of_res= open("pipe_answer",O_RDONLY);
write(desc,bfw,sizeof(bfw));
close(desc);
sleep(10);
char bfr[OBUFFER];

	read(desc_of_res,bfr,OBUFFER);

	close(desc_of_res);
printf("la reponce du deuixiem processus  : %s \n",bfr );
	return 0;
}
