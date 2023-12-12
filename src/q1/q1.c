#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#define BUFFER_SIZE 10240
int main(int argc, char *argv[])
{
    //argv[1]=file
    //argv[2]=number of strings
    //argv[3]=size of string
    /* check if exactly one argument is present */
    if (argc != 4)
    {
        printf("missing paramatres\n");
        return EXIT_FAILURE;
    }
    /* check if file can be opened and is readable */
    FILE *fptr;
    fptr = fopen(argv[1],"r");
    if(fptr==NULL){
        printf("error: cannot open %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    /* print the contents in blocks */
    int n=atoi(argv[2]);
    int size=atoi(argv[3]);
    int randval[n];
    fseek(fptr, 0, SEEK_END);
    int fsize = ftell(fptr);
    time_t t;
    time(&t);
    srandom((unsigned) time(&t));
    for(int it=0;it<n;it++){
        int temp=0;
        int r=random() % fsize-n;
        while(temp<it){
            temp++;
            if(randval[temp]==r){
                r=random() % fsize-n;
                temp=0;
            }
        }
        randval[it]=r;
        fseek( fptr, r, SEEK_SET );
        printf(">");
        for(int iter=0;iter<size;iter++){
            char c=fgetc(fptr);
            if(c=='\n'){
                c=fgetc(fptr);
            }
            printf("%c", c);
        }
        printf("<\n");

    }
    /* close file */
    fclose(fptr);
    return EXIT_SUCCESS;
}