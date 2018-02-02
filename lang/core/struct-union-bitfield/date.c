#include <stdio.h>
#include "songs.h"

/*
 * dateAsString: convert struct Date to format 'mm/dd/yyyy'
 */
const char *dateAsString(struct Date d)
{
	static char strDate[12];
	sprintf(strDate, "%02d/%02d%04d", d.month, d.day, d.year);
	return strDate;
}

/*
 * printSong: output Song_t date
 */
void printSong(const Song_t *pSong)
{
	int m = pSong->duration / 60;
	int s = pSong->duration % 60;
	printf("-------------------------------------------\n"
         "Title:         %s\n"
         "Artist:        %s\n"
         "Composer:      %s\n"
         "Playing time:  %d:%02d\n"
         "Date:          %s\n",
         pSong->title, pSong->artist, pSong->composer, m, s,
         dateAsString(pSong->published));
}
