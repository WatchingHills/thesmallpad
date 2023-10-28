#include <stdlib.h>
#include <string.h>
#include "dataStructures.h"


void initDStrArray(DStrArray * arr, size_t initialSize)
{
	arr->array = malloc(initialSize * sizeof(char **));
	arr->used = 0;
	arr->size = initialSize;
}

void insertDStrArray(DStrArray * arr, const char * element)
{
	if(arr->used > arr->size)
	{
		arr->size *= 2;
		arr->array = realloc(arr->array, arr->size * sizeof(char **));
	}
	
	arr->array[arr->used] = malloc(strlen(element) + 1); 
	arr->array[arr->used] = strcpy(arr->array[arr->used], element);
	arr->array[arr->used][strlen(element)] = '\0';
	arr->used += 1;
}

void deleteDStrArray(DStrArray * arr, size_t pos)
{
	if(pos < arr->used)
	{
		for(int i = pos + 1, j = pos; pos < arr->used; i++)
		{
			memset(arr->array[j], 0, strlen(arr->array[j]));
			arr->array[j] = malloc(strlen(arr->array[i]) + 1);
			arr->array[j] = strcpy(arr->array[j], arr->array[i]);
			arr->array[j][strlen(arr->array[i])] = '\0';
			j = i;
		}

		arr->used -= 1;
	}
}

void freeDStrArray(DStrArray * arr)
{
	for(int i = 0; i < arr->size; i++)
	{
		free(arr->array[i]);
	}
	
	free(arr->array);
	arr->used = arr->size = 0;
}

char * concatStrings(const char * s1, const char * s2)
{
	int i = 0; int j = 0;
	char * result = malloc(strlen(s1) + strlen(s2) + 1);

	while(*s1)
	{
		result[i++] = *s1++;
	}

	while(*s2)
	{
		result[i + j++] = *s2++;
	}

	result[i + j] = '\0';
	return result;
}


