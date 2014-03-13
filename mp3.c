#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "song.h"

#include <dirent.h>

#define NUMBER_OF_SONGS 100
#define LENGTH 40
#define MAXLINE 100
#define MAXARGS 5

//music shell
//command line interpreter
//peek function - take current song and generate n number n is input
//way to get times



pid_t pid;
void catchint(int sig);
int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded);
void writeBinarySongs(Song songs[], int numSongs, char fName[]);
void readBinarySongs(Song songs[], int numSongs, char fName[]);
void printSongs(Song songs[], int numSongs);
void initializeSongs(Song songs[], int numSongs, char songNames[][LENGTH]);

//music shell functions
void playSong(char *songName);
void eval(char *cmdline); 
int builtin_cmd(char **argv); 
int parseline(const char *cmdline, char **argv); 

int compare(const void *one, const void *two)
{

            return (strcmp(*(char **)one, *(char **)two));
}

main(int argc, char * argv[])
{

	
/*Code that loads at beginning*/
	//array of songs
	int numSongs = 3;
	char songNames[NUMBER_OF_SONGS][LENGTH];	

	//have user 
	getDirectory(songNames, &numSongs);
	Song songs[numSongs];
	Song songs2[numSongs];

	char input;
	printf("Is this your first time? y/n\n");
	input = fgetc(stdin);
		while (getchar() != '\n');

	if (input == 'y') {
	
		initializeSongs(songs, numSongs, songNames);
		printf("here1\n");
		writeBinarySongs(songs, numSongs, "t1.bin");
		printf("here2\n");
		printSongs(songs,numSongs);
		//printf("delete some songs\n");
		//strcpy(songs[2].name,"songName");
	}
	else {
		numSongs = 3;
		readBinarySongs(songs2, numSongs, "t1.bin");
		//printf("here4\n");
		//printSongs(songs2, numSongs);
	}


//peek
//shuffle
//smartshuffle
//play -songname
//pause
//unpause
	int emit_prompt = 1;
	char cmdline[MAXLINE];

	while (1) {


		if (emit_prompt) {
		    printf("%s", "mp3 >");
		    fflush(stdout);
		}

		if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
		    printf("fgets error\n");
		if (feof(stdin)) { 
		    fflush(stdout);
		    exit(0);
		}

		if(cmdline == NULL)
			continue;
		eval(cmdline);
		fflush(stdout);
		fflush(stdout);
   	 } 



	//if((pid = fork()) == 0)
	//{
	//	setpgid(0,0);
	//	execvp(argv[1], &argv[1]);
	//	execvp(argv[1], argv);
	//	  execvp("mpg123", argv);
	//}

	//signal(SIGINT, catchint);
	//int status;
	//if (waitpid(pid, &status, 0) < 0)
	//	printf("waitfg: waitpid error");


	return;
}


void eval(char *cmdline) 
{

	char *argv[MAXARGS];
	int bg;
	pid_t pid; 
	
	//check if command is background so we know not to wait for it
	parseline(cmdline, argv);

	//sigset_t signals;
	//sigemptyset(&signals);

	

	if(!builtin_cmd(argv)) {
		printf("error1:\n");
	}


    return;
}

int builtin_cmd(char **argv) 
{

//printf("here\n");
printf("argv: %s\n", argv[0]);
	if (strcmp(argv[0], "quit") == 0)
		exit(0);
//printf("here\n");
	if (strcmp(argv[0], "play") == 0) {
		playSong(argv[1]);
		return 1;
	}
	//if (strcmp(argv[0], "bg") == 0) {
	//	if(argv[1] == NULL) //make sure user supplies arguments
	//		printf("bg command requires PID or %%jobid argument\n");
	//	else
	//		do_bgfg(argv);
	//	return 1;
	//}	
    return 0;     /* not a builtin command */
}

void playSong(char *songName)
{
	if((pid = fork()) == 0)
	{
		setpgid(0,0);
		//execvp(argv[1], &argv[1]);
		//execvp(argv[1], argv);
		//printf("\n\n%s\n", songName);
			//while (getchar() != '\n');
		//char * argv[50];
		
		int n = 4;
		char **argv = (char **) malloc( n * sizeof(char *));
		int i;
		for (i=0; i < n; i++) {
			argv[i] = (char *) malloc (70);
		}
			
		argv[0] = "mpg123";
		argv[1] = "-q";
		argv[2] = "/home/jab489/Music/Chopin.mp3";
		argv[3] = NULL;
		execvp("mpg123", argv);
	}
	
	
}



int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded)
{
	char path[100];
	printf("Please enter the directory path with .mp3 files\n");
	//fgets(path, 100, stdin);
	//printf("size: %d", strlen(path));
	 strcpy(path, "/home/jab489/Music");	
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
	qsort(songs, songNumber, LENGTH,
		(int (*)(const void *, const void*)) strcmp);

}

void initializeSongs(Song songs[], int numSongs, char songNames[][LENGTH])
{

	int i,j;
	for (i = 0; i < numSongs; i++) {
		songs[i].name =malloc(sizeof(char) * (strlen(songNames[i]) + 1) ); 
		strcpy((songs[i].name), (songNames[i]));
		songs[i].markov = (int *) calloc (numSongs, sizeof(int));
		for (j = 0; j < numSongs; j++)
			songs[i].markov[j] = 1;
		songs[i].markovLength = numSongs;
		songs[i].nameLength = strlen(songs[i].name) + 1;

	}
	
}

void writeBinarySongs(Song songs[], int numSongs, char fName[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "wb");

	for(i=0;i<numSongs;i++)
	{
		//TODO: make it so it saves each data member
		//      dynamically.
		fwrite(&songs[i].nameLength, sizeof(int), 1, data_file);
		fwrite(&songs[i].markovLength, sizeof(int), 1, data_file);
		int j;
		//for(j= 0; j < songs[i].nameLength; j++)
		//	fwrite(songs[i].name[j], sizeof(char), 1, data_file);
		printf("hereeee\n");
		fwrite(songs[i].name, sizeof(char), songs[i].nameLength, data_file);
		fwrite(songs[i].markov, sizeof(int), songs[i].markovLength, data_file);
	}
	fclose(data_file);
	
}

void readBinarySongs(Song songs[], int numSongs, char fName[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "rb");

	for(i=0;i<numSongs;i++)
	{
		fread(&songs[i].nameLength, sizeof(int), 1, data_file);
		fread(&songs[i].markovLength, sizeof(int), 1, data_file);
		printf("%d %d\n", songs[i].nameLength, songs[i].markovLength);
		songs[i].name = malloc( sizeof(char) * songs[i].nameLength);
		songs[i].markov = malloc( sizeof(int) * songs[i].markovLength);
		printf("here3\n");
		//strcpy(songs[i].name, "test");
		//*(songs[i].markov) = 5;
		//char * test = (char *) malloc(sizeof(char) * 50);
		//fread(test, sizeof(char), songs[i].nameLength, data_file);
		//printf("%c%c\n", test[0],test[1]);
		
		//printf("%s\n", test);
		fread(songs[i].name, sizeof(char), songs[i].nameLength, data_file);
		fread(songs[i].markov, sizeof(int), songs[i].markovLength, data_file);
		//printf("%s\n", songs[i].name);
		//fread(&(songs[i]), sizeof(Song), 1, data_file);
	}
	fclose(data_file);
	
}

void printSongs(Song songs[], int numSongs)
{
	int i;
	for(i=0;i<numSongs;i++)
	{
		printf("song[%d] name: %s\n",i,songs[i].name);
		int j;
		for (j = 0; j < songs[i].markovLength; j++)
			printf("song[%d] markov[%d]: %d\n",i,j,songs[i].markov[j]);
	}
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

int parseline(const char *cmdline, char **argv) 
{
    static char array[MAXLINE]; /* holds local copy of command line */
    char *buf = array;          /* ptr that traverses command line */
    char *delim;                /* points to first space delimiter */
    int argc;                   /* number of args */
    int bg;                     /* background job? */

    strcpy(buf, cmdline);
    buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    if (*buf == '\'') {
	buf++;
	delim = strchr(buf, '\'');
    }
    else {
	delim = strchr(buf, ' ');
    }

    while (delim) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* ignore spaces */
	       buf++;

	if (*buf == '\'') {
	    buf++;
	    delim = strchr(buf, '\'');
	}
	else {
	    delim = strchr(buf, ' ');
	}
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* ignore blank line */
	return 1;

    /* should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0) {
	argv[--argc] = NULL;
    }
    return bg;
}
