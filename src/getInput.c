#include <raylib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int verifyLetter(char *wordToDiscover, char *maskedWord, int key){
	int ret = 0;
	size_t word_size = strlen(maskedWord);

	for (size_t i=0; i<word_size; i++){
		if (wordToDiscover[i] == (char)key){
			// printf("find\n");
			maskedWord[i] = (char)key;
			ret++;
		}
	}

	return ret;
}

void 
fillWord(char *wordToDiscover, char *maskedWord, int *pos, int *try, int key)
{
	int res = verifyLetter(wordToDiscover, maskedWord, key);;
	size_t word_size = strlen(maskedWord);

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
