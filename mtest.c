#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <dirent.h>

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
        /*read in a string from pipe*/
        size_t size;
        //while (getline(&line, &size, 0) != -1) {
        //    printf("child got string: %s\n",line);
        //}
        execlp("mpg123","mpg123", "-C", "./music/Chopin.mp3", NULL);
        return 0;
    }
    else
    {
        /*parent closes input side of pipe*/
        close(fd[0]);
        //write(fd[1],s,strlen(s)+1);
        char * str = NULL;
        size_t size;
        int cont = 1;
        while(cont!=0)
        {
            printf("type quit or something you want mpg123 to do\n");
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
        }
        free(str);
    }
    
    return(0);
}
