#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


pid_t pid;
void catchint(int sig);

main(int argc, char * argv[])
{

	if((pid = fork()) == 0)
	{
		setpgid(0,0);
		//execvp(argv[1], &argv[1]);
		//execvp(argv[1], argv);
		  execvp("mpg123", argv);
	}

	signal(SIGINT, catchint);
	int status;
	if (waitpid(pid, &status, 0) < 0)
		printf("waitfg: waitpid error");

	return;
}

void catchint (int sig) {	

	printf("Do you want to quit program?!\n");
	char input[100];
	fgets(input, 100, stdin);	

	if( strcmp(input, "yes"))
	{
		kill(pid, SIGINT);
		exit(0);
	}
	else
		return;
	
}
