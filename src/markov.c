#include "markov.h"

void testInsertValue()
{
    int n = 10;
    int * arr = calloc(n,sizeof(int));
    int i;
    for(i=0;i<n;i++)
    {
        insertValue(arr,n,i,i);
    }
    insertValue(arr,n,-1,0);
    for(i=0;i<n;i++)
    {
        printf("arr[%d]: %d\n",i,arr[i]);
    }
}

Song * makeExampleSongs(int * len)
{
    int n = (*len) = 3;
    Song * songs = malloc(n*sizeof(Song));

    //initialize all the markov chains
    int i;
    for(i=0;i<n;i++)
    {
        songs[i].markov = calloc(n,sizeof(int));
        songs[i].markovLength=n;
    }

    //initialize first song
    songs[0].name = "Cats";
    songs[0].markov[0] = 5;
    songs[0].markov[1] = 2;
    songs[0].markov[2] = 1;

    //init 2nd song
    songs[1].name = "Chillax";
    songs[1].markov[0] = 2;
    songs[1].markov[1] = 1;
    songs[1].markov[2] = 4;

    //init 3rd song
    songs[2].name = "Classical";
    songs[2].markov[0] = 1;
    songs[2].markov[1] = 4;
    songs[2].markov[2] = 3;

    return songs;
}

void testLikelySongs()
{
    int n;
    Song * songs = makeExampleSongs(&n);
    printf("Here's the example songs list:\n");
    printSongs(songs,n);

    int numLikely = 2;
    Song * mostLikely = getMostLikelySongs(songs,n,songs[2],numLikely);
    printf("Here's the %d songs we think are most likely for %s\n",
            numLikely,songs[2].name);
    printSongs(mostLikely,numLikely);
}
//~ 
//~ void testGetNextSong()
//~ {
    //~ int n;
    //~ Song * songs = makeExampleSongs(&n);
    //~ Song * rSong = getNextSong(songs,n,songs[0]);
    //~ printf("rSong: %s\n",rSong->name);
//~ }

int randLim(int limit) {
/* return a random number between 0 and limit inclusive.
 * from awesome stackoverflow man Jerry Coffin
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

Song * getNextSong(Song *song)
{
    //the total number of songs that have been played after the current song
    int numSongsChained = 0;
    int i;
    for(i=0;i<song->markovLength;i++)
    {
        numSongsChained += song->markov[i];
    }

    int r;  //choose a random song between 0 and numSongsChained
    r = rand()%numSongsChained;

    int songsSoFar = 0;  //how many songs chained through so far

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



//return the top numReturn songs in sorted order
Song * getMostLikelySongs(Song songs[], int numSongs, Song song, int numReturn)
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
    for(i=0;i<song.markovLength;i++)
    {
        for(j=0;j<numReturn;j++)
        {
            //store the largest value in rv[0], lowest in rv[numReturn]
            if(song.markov[i]>markovValues[j])
            {
                insertValue(songLocs,numReturn,i,j);
                insertValue(markovValues,numReturn,song.markov[i],j);
                break;
            }
        }
    }

    //return actual songs rather than songLocs
    Song * rv = malloc(numReturn*sizeof(Song));
    for(i=0;i<numReturn;i++)
    {
        rv[i] = songs[songLocs[i]];
    }
    return rv;
}


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

/*int songToId(Song * song) {
	int i;
	for (i=0; i<numSongs; i++) {
		if (strcmp(song->name, songList[i].name))
				return i;
	}
	return -1;
}*/
