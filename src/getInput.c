#include <raylib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

char *repeatedLetters(char *rep, char current){
	bool flag = false;

	size_t rsize = strlen(rep);

	for (size_t i=0; i<rsize; i++){
		if (rep[i] == current){
			flag = true;
			break;
		}
	}

	if (!flag){
		auto char to_app[2] = {current, '\0'};
		strcat(rep, to_app);
	}

	return rep;
}

int verifyLetter(char *wordToDiscover, char *maskedWord, char *rep, int key){
	int ret = 0;
	size_t word_size = strlen(maskedWord);

	for (size_t i=0; i<word_size; i++){
		if (wordToDiscover[i] == (char)key){
			/* printf("find\n"); */
			maskedWord[i] = (char)key;
			ret++;
		}
	}

	if (ret == 0) repeatedLetters(rep, key);

	return ret;
}

void 
fillWord(char *wordToDiscover, char *maskedWord, char *rep, int *pos, int *try, int key)
{
	char *s = rep;

	int res = verifyLetter(wordToDiscover, maskedWord, rep, key);;
	size_t word_size = strlen(maskedWord);

	if (strcmp(s, rep)!=0) (*try)++;

	switch (res) {
		case 0:
			(*try)--;
			break;
		default: {
			for (size_t i=0; i<word_size; i++){
				if (*(maskedWord+i)=='_'){
					*pos = i;
					break;
				}
			}
			break;
		}
	}
}
