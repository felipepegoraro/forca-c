#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./readwords.h"

int getIndex(void)
{
	srand(time(NULL));
	return (rand() % LIN)-1;
}

void readWord(char **allwords){
	int i=0, j=0;
	char line[BUFFER_SIZE]={};
	FILE *fp; 

	if ((fp = fopen("./data/words.txt", "r")) == NULL){
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while((i = fscanf(fp, " %s ", line)) && i != EOF){
		strcpy(allwords[j], line);
		j++;
	}

	fclose(fp);
}

char *getWord(char **allwords){
	int index = getIndex();
	return allwords[index];
}
