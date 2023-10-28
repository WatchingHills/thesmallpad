#ifndef __DATA_STRUCTURES__
#define __DATA_STRUCTURES__

#include <stdlib.h>

typedef struct
{
	size_t used;
	size_t size;
	char ** array;
}DStrArray;

void initDStrArray(DStrArray * arr, size_t initialSize);
void insertDStrArray(DStrArray * arr, const char * element);
void deleteDStrArray(DStrArray * arr, size_t pos);
void freeDStrArray(DStrArray * arr);
char * concatStrings(const char * s1, const char * s2);


#endif 
