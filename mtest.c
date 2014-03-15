#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <dirent.h>

#define LENGTH 40

pid_t pid;

main(int argc, char * argv[])
{
    int fd[2], nbytes;
    char s[] = "Hello world!\n";
    char readBuff[80];

    pipe(fd);
    
    if((pid = fork())==-1)
    {
        perror("Bad fork!\n");
        exit(1);
    }
    if(pid==0)
    {
        /*child process right here, close up output side of pipe*/
        close(fd[1]);
        close(0); //close std input child
        /*Duplicate standard input with the pipe*/
        dup(fd[0]);
        char *line = NULL;
        char * str = malloc(LENGTH*sizeof(char));
        /*read in a string from pipe*/
        size_t size;
        //int c;
        //c = getchar();
        //while(c!=EOF)
        //{
        //    putchar(c);
        //    c=getchar();
        //}
        execlp("mpg123","mpg123", "-C", "./music/Chopin.mp3", NULL);
        return 0;
    }
    else
    {
        /*parent closes input side of pipe*/
        close(fd[0]);
        //write(fd[1],s,strlen(s)+1);
        char * str = malloc(LENGTH*sizeof(char));
        size_t size;
        int cont = 1;
        while(cont!=0)
        {
            printf("type quit or something you want mpg123 to do\n");
<<<<<<< HEAD
            fgets(str,LENGTH,stdin);
            write(fd[1],str,strlen(str)+1);
=======
            getline(&str,&size,stdin);
           // if(getline(&str,&size,stdin)==-1) //|| strcmp(str,"quit")==0 ) 
           // {
           //     printf("here I am\n");
           //     strcpy(str,"quit");
           // }
           // else
           // {
           //     printf("this branch\n"); 
                write(fd[1],str,size-1);
           // }
>>>>>>> ff0dbb1c9743cc8abe88f5b934c6aed96470543e
        }
        free(str);
    }
    
    return(0);
}
