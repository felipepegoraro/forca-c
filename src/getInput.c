#include <raylib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int getLetter(void){
	int key;

	if ((key = GetCharPressed()) >= 32 && key <= 126){
		return key;
	}
	if (IsKeyPressed(KEY_BACKSPACE))
		key = 0;

	return key;
}

int verifyLetter(char *wordToDiscover, char *maskedWord, int key){
	int ret = 0;
	size_t word_size = strlen(maskedWord);

	if (key == 0){
		return -1;
	}

	for (size_t i=0; i<word_size; i++){
		if (wordToDiscover[i] == (char)key){
			printf("find\n");
			(maskedWord[i] = (char)key);
			ret++;
		}
	}

	return ret;
}

void 
fillWord(char *wordToDiscover, char *maskedWord, int *pos, int *try)
{
	int key = getLetter();
	int res = verifyLetter(wordToDiscover, maskedWord, key);;
	size_t word_size = strlen(maskedWord);

	switch (res) {
		case -1:
			*(wordToDiscover+*pos) = 0;
			(*pos)--;
			break;
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
