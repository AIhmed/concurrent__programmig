#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define BUFF 256
#define OBUFFER 256
char bfr[BUFF];
char bfw[OBUFFER];
int main(int argc, char const *argv[]){
	int pipe=mkfifo("pipy",4000);
int pipe_responce=mkfifo("pipe_answer",2000);
	int desc= open("pipy",O_RDONLY);
int desc_of_res=open("pipe_answer",O_WRONLY);
	read(desc,bfr,sizeof(bfr));
	close(desc);
	printf("mot recu du premier processus : %s \n",bfr );
	FILE* fp =fopen("fichier.txt","r");
int x,y=0;
char **str=malloc((BUFF)*sizeof(char*));
char* str1= malloc(10*sizeof(char));
while((x=fscanf(fp,"%s",str1))!=EOF){
	str[y]=str1;
printf("the buffer lu est : %s \n \n \n ",bfr );
printf("caracthere lu du fichier %s \n \n \n",str1);
printf("chaine de tout les caracthere lu du fichier %s \n \n \n",str[y]);
	sleep(2);
	if(str1==bfr){
		sprintf(bfw,"le message de reponce a le 1ére processus %s ", "1");
	}else {
		sprintf(bfw,"le message de reponce a le 1ére processus %s ", "O");
	}
	printf(" %s\n",bfw );
	
		write(desc_of_res,bfw,OBUFFER);
	y++;
	}
		
		close(desc_of_res);
	return 0;
}