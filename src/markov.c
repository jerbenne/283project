#include "markov.h"


/**
 * randLim returns a random number between 0 and limit.
 * @param limit The max number.
 * @return Random number in [0, limit]
 */
int randLim(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

/**
 * Finds the total number of song counts in the song's markov chain.
 * @param song Song to count up the number of markov chains.
 * @return Total number of song counts in the markov chain.
 */
int getTotalSongsChained(Song *song)
{
    //the total number of songs that have been played after the current song
    int numSongsChained = 0;
    int i;

    for(i=0;i<numSongs;i++)
    {
        numSongsChained += song->markov[i];
    }
	return numSongsChained;
}

/**
 * getNextSong finds the next song to play based on probability of the markov chain.
 * @param song Current song to calculate probabilities of.
 * @return pointer to the next song.
 */
Song * getNextSong(Song *song)
{

	int numSongsChained=getTotalSongsChained(song);
    int r;  //choose a random song between 0 and numSongsChained
    r = rand()%numSongsChained;

    int songsSoFar = 0;  //how many songs chained through so far
    int i = 0;

    //iterate through to find the random song
    for(i=0;i<song->markovLength;i++)
    {
        songsSoFar += song->markov[i];
        if(r<songsSoFar)
        {

	    printf("gns: %s\n", songList[i].name);

            return &songList[i];
        }
    }

    //something bad happened and we didn't get a song
    return NULL;
}


/**
 * 
 * @param a The first character.
 * @param b The character to compare to a.
 * @return negative value if 
 */
//return the top numReturn songs in sorted order
Song * getMostLikelySongs(Song * song, int numReturn)
{
    int i  //iterate over all songs in markov chain
        , j;  //iterate over rv values
    int songLocs[numReturn];
    int markovValues[numReturn];

    //initialize all to zero
    for(i=0;i<numReturn;i++)
    {
        songLocs[i] = 0;
        markovValues[i] = 0;
    }
    
    //actually go get the numReturn highest
    for(i=0;i<song->markovLength;i++)
    {
        for(j=0;j<numReturn;j++)
        {
            //store the largest value in rv[0], lowest in rv[numReturn]
            if(song->markov[i]>markovValues[j])
            {
                insertValue(songLocs,numReturn,i,j);
                insertValue(markovValues,numReturn,song->markov[i],j);
                break;
            }
        }
    }

    //return actual songs rather than songLocs
    Song * rv = malloc(numReturn*sizeof(Song));
    for(i=0;i<numReturn;i++)
    {
        rv[i] = songList[songLocs[i]];
    }
    return rv;
}

/**
 * 
 * @param a The first character.
 * @param b The character to compare to a.
 * @return negative value if 
 */
void peek(int x)
{
	if(x>numSongs)
		x = numSongs;

	//get top X number songs
	Song * targetSong = (previous!=NULL) ? previous : current;
	Song * mostLikely = getMostLikelySongs(targetSong, x);
	int i;	

	int numChained = getTotalSongsChained(targetSong);
	printf("num chained %d:\n", numChained);
	printf("target song: %s\n", targetSong->name);

	for(i=0;i<x;i++)
	{
		float percentage;


		int songId = songToId(&mostLikely[i]);

		percentage = 100.0 *targetSong->markov[songId]/(numChained*1.0);
		printf("[%d]: (%5.2f%%) %s \n",i+1, percentage, mostLikely[i].name);
	}

	printf("Number (Enter 0 for no change): ");
	
	int userChoice;
	scanf("%d", &userChoice);

	if( !(userChoice > x || userChoice < 1)) {
		next = &mostLikely[userChoice-1];
	}
	else
		printf("Next song unchanged\n");

	//clear standard in
	while (getchar() != '\n');

	printStatus();
	
}

/**
 * 
 * @param a The first character.
 * @param b The character to compare to a.
 * @return negative value if 
 */
//insert value at position p, pushing back other values
void insertValue(int * arr, int size, int value, int p)
{
    int i;
    for(i=size-1;i>p;i--)
    {
        arr[i] = arr[i-1];
    }
    arr[p] = value;
}

