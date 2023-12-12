#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
    int status = 0;
    pid_t pid;
    char *lastcommand[1024]={"zip","ebooks.zip",'\0'};
    for(int temp=2;temp<1024;temp++){
        lastcommand[temp]=malloc(BUFFER_SIZE);
    }
    for(int filenum=1;filenum<argc;filenum++){
        char filename[BUFFER_SIZE]="";
        strcat(filename,argv[filenum]);
        int n=0;
        while(filename[n]!='.'){
            n++;
        }
        n++;
        filename[n]='e';
        n++;
        filename[n]='p';
        n++;
        filename[n]='u';
        n++;
        filename[n]='b';
        n++;
        filename[n]='\0';
        pid = fork();
        if(pid==0){
            execl("/usr/bin/pandoc","/usr/bin/pandoc",argv[filenum],"-o",filename,"--quiet",NULL);
        }
        if(pid!=0){
            strcpy(lastcommand[filenum+1],filename);
        }
    }
    lastcommand[argc+3]=(char*) NULL;
    lastcommand[argc+2]="-q";
    while ((pid = wait(&status)) > 0);
    execvp("zip",lastcommand);
    return EXIT_SUCCESS;
}