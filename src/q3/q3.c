#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>

int n;
#define BUFFER_SIZE 1024

void pipeDeleter(){
    char pipeName[BUFFER_SIZE];
     for(int i = 1; i <= n; i++){
        if(i != n)snprintf(pipeName, BUFFER_SIZE, "pipe%dto%d", i, i+1);
        else snprintf(pipeName, BUFFER_SIZE, "pipe%dto%d", i, 1);
        unlink(pipeName);
    }
    kill(-1*getpid(), SIGKILL);
}

int main(int argc, char *argv[]){
    n = atoi(argv[1]);
    float p = atof(argv[2]);
    int t = atoi(argv[3]);
    int token = 0;
    int pid = 0;
    char pipeName[BUFFER_SIZE];
    int readPipe[BUFFER_SIZE];
    int k;
    bool canWrite = false;

    

    for(int i = 1; i <= n; i++){
        if(i != n)snprintf(pipeName, BUFFER_SIZE, "pipe%dto%d", i, i+1);
        else snprintf(pipeName, BUFFER_SIZE, "pipe%dto%d", i, 1);
        mkfifo(pipeName, 0777);
    }

    for(int i = 1; i < n; i++){
        if(pid != 0){
            pid = fork();
            k = i;
        }
    }
    
    if (k==1) canWrite=true;
    
    while(true){
        if(canWrite){
            if(k == n){
                snprintf(readPipe, BUFFER_SIZE, "pipe%dto%d", k, 1);
                write(readPipe, &token, sizeof(int));
                k= 1;
            }
            else{
                snprintf(readPipe, BUFFER_SIZE, "pipe%dto%d", k, k+1);
                write(readPipe, &token, sizeof(int));
                k++;
            }
            canWrite = false;
        }
        else{
            if(k == 1){
                snprintf(readPipe, BUFFER_SIZE, "pipe%dto%d", n, k);
                while(read(readPipe, &token, sizeof(int)) == 0);
            }
            else{
                snprintf(readPipe, BUFFER_SIZE, "pipe%dto%d", k-1, k);
                while(read(readPipe, &token, sizeof(int)) == 0);
            }
            
            float try = (float)(random()%100) /100;
                if(try <= p){
                    printf("[p%d] lock on token (val = %d)\n", k, token);
                    sleep(t);
                    printf("[p%d] unlock token \n", k);
                }
                token++;
                canWrite = true;
        }
        signal(SIGINT, pipeDeleter);
    }
    wait(NULL);
    return EXIT_SUCCESS;
}
