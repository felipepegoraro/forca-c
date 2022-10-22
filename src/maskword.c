#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./maskword.h"

char *mask(char *word)
{
	size_t i, word_size = strlen(word);
	char *masked = malloc(sizeof(char)*word_size);

	if (!masked){
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	for (i=0; i<word_size; i++)
		masked[i] = '_';

	return masked;
}
