#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>

#include "markov.h"
#include "song.h"
#include "loadFiles.h"


#define MAXLINE 100
#define MAXARGS 5

//TODO: have peek also do queue
//TODO: Handle Ctrl Z's

//music shell
//command line interpreter
//peek function - take current song and generate n number n is input
//way to get times
//also have it show which song would be playing next


/* Globals: */
pid_t pid;
Song * previous, * current, * next;
Song * songList;
int numSongs;
char * path;


/* Signal handlers for background mp3 playing */
void catchint(int sig);
void sigchld_handler(int sig);
void sigquit_handler(int sig); 


/* music shell functions */
void playSong(char *songName);
void eval(char *cmdline); 
int builtin_cmd(char **argv); 
int parseline(const char *cmdline, char **argv); 
void killCurrent();

/* used for sorting the songs with qsort */
int compare(const void *one, const void *two)
{
	return (strcmp(*(char **)one, *(char **)two));
}

main(int argc, char * argv[])
{
    srand(time(NULL));
    //testGetNextSong();
	
/*Code that loads at beginning*/
	//array of songs
	char songNames[NUMBER_OF_SONGS][LENGTH];	

	//Song songs[numSongs];

	char input;
	int validInput = 0;
	char directory[100];

	/* Ask user if they would like to load their saved data */
	do {
		printf("Load Binary File? y/n\n");
		input = fgetc(stdin);
		while (getchar() != '\n');

		if (input == 'y') {
	
			numSongs = readBinarySongs("t1.bin");
			printAllSongs();
			validInput = 1;
		}
		else if (input == 'n') {

			getDirectory(songNames, &numSongs);
			initializeSongs(numSongs, songNames);

			/*Create new save file*/
			writeBinarySongs(numSongs, "t1.bin");

			validInput = 1;
		}
	}
	while (!validInput);


	signal(SIGINT, catchint);
	signal(SIGCHLD, sigchld_handler); 
    	signal(SIGQUIT, sigquit_handler); 

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

		if(cmdline == NULL || cmdline[0] == '\n')
			continue;

		eval(cmdline);
		sleep(4);
		fflush(stdout);
   	 } 

	return;
}


void eval(char *cmdline) 
{

	char *argv[MAXARGS];
	int bg;
	pid_t pid; 
	
	parseline(cmdline, argv);

	if(!builtin_cmd(argv)) {
		printf("error: not a command.\n");
	}

    return;
}

int builtin_cmd(char **argv) 
{

	if(!argv[0])
		return 0;

	if (strcmp(argv[0], "quit") == 0) {
		//TODO: check if process exists before killing
		kill(pid, SIGKILL); 
		exit(0);
	}

	if (strcmp(argv[0], "play") == 0) {
		playSong(argv[1]);
		return 1;
	}

	//skip command
	if (strcmp(argv[0], "s") == 0) {
			//TODO: print out help function
		killCurrent();
		return 1;
	}

	if (strcmp(argv[0], "help") == 0) {
			//TODO: print out help function
	}
	
    	return 0;     /* not a command */
}

void playSong(char *songName)
{
	if((pid = fork()) == 0)
	{
		setpgid(0,0);

		/* build command line for mpg123 */		
		int n = 4;
		char **argv = (char **) malloc( n * sizeof(char *));
		int i;
		for (i=0; i < n; i++) {
			argv[i] = (char *) malloc (70*sizeof(char));
		}

		argv[0] = "mpg123";
		argv[1] = "-q";
		strcpy(argv[2], path);
		strcat(argv[2], "/");
		strcat(argv[2], songName);

		argv[3] = NULL;
		execvp("mpg123", argv);
	}
	else
	{
		current = getSongByString(songName);
		next = getNextSong((previous!=NULL) ? previous : current);
		printStatus();
	}
	
}

//void lookUpSong(char *songName)
//{
//
//
//}

void catchint (int sig) {	

	kill(pid, SIGINT);
	exit(0);
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


void sigchld_handler(int sig) 
{

	//TODO: fix this section, code not tested
	/* Wait for dead processes.
	 * Use non-blocking call to be sure this signal handler will not
	 * block if a child was cleaned up in another part of the program. */
	if (waitpid(pid, NULL, WNOHANG) < 0) {
		fprintf(stderr, "waitpid error");
	}
	
	if(previous!=NULL&&current!=NULL){
		int i;
		i = songToId(current);
		if (i>=0) {
			previous->markov[i]++;
			writeBinarySongs(numSongs, "t1.bin");
		}
	}
	if(current!=NULL)
		previous = current;
	playSong(next->name); 
	fflush(stdout);
	
	
    	return;
	
}

/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void sigquit_handler(int sig) 
{
    printf("Terminating after receipt of SIGQUIT signal\n");
    exit(1);
}

//TODO: comment out the previous in the printStatus
void killCurrent()
{
	kill(pid, SIGKILL);
	current = NULL;
}








