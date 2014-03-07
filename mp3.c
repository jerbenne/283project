#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <dirent.h>

#define NUMBER_OF_SONGS 100
#define LENGTH 40

pid_t pid;
void catchint(int sig);
int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded);


int compare(const void *one, const void *two)
{

            return (strcmp(*(char **)one, *(char **)two));
}

main(int argc, char * argv[])
{

	//if((pid = fork()) == 0)
	//{
	//	setpgid(0,0);
		//execvp(argv[1], &argv[1]);
		//execvp(argv[1], argv);
	//	  execvp("mpg123", argv);
	//}

	//signal(SIGINT, catchint);
	//int status;
	//if (waitpid(pid, &status, 0) < 0)
	//	printf("waitfg: waitpid error");


	//array of songs
	int numSongs;
	char songs[NUMBER_OF_SONGS][LENGTH];	

	//have user 
	getDirectory(songs, &numSongs);

	printf("%d", numSongs);

	int i;
	for (i = 0; i < numSongs; i++)
	{
		printf("%s\n", songs[i]);
	}


	return;
}




//TODO: SORT 
int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded)
{
	char path[100];
	printf("Please enter the directory path with .mp3 files\n");
	fgets(path, 100, stdin);
	//printf("size: %d", strlen(path));
		
	strtok(path, "\n");
	DIR *dp; //pointer to directory
	struct dirent *ep; // directory entry

	int songNumber = 0;

	if((dp = opendir(path)) == NULL) {
		printf("cant open %s\n", path);
		return(0);
	}
	//type 8 is mp3
	else {
		while ((ep = readdir(dp)) != NULL) {
			if (ep->d_type == 8) {
				strcpy(songs[songNumber], ep->d_name);
				songNumber++;
			}
		}
	}

	*songsAdded = songNumber;
	qsort(songs, 2, LENGTH, compare);

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
