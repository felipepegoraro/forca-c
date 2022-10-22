#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include "./src/readwords.h"
#include "./src/maskword.h"

#define  WIDTH 1000
#define HEIGHT 400
#define   NAME "Jogo da Forca"

int main(void)
{
	char **words = malloc(sizeof(char *)*LIN);
	for (int i=0; i<LIN; i++) words[i] = malloc(sizeof(char)*COL);

	if (!words){
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	readWord(words);

	char *wordToDiscover = malloc(sizeof(char)*COL);

	strcpy(wordToDiscover, getWord(words));

	free(words);
	size_t ws = strlen(wordToDiscover);
	char *maskedWord = malloc(sizeof(char)*ws+1);

	strcpy(maskedWord, mask(wordToDiscover));
	maskedWord[ws]='\0';

	InitWindow(WIDTH, HEIGHT, NAME);

	while (!WindowShouldClose()){
		ClearBackground(BLACK);
		BeginDrawing();
			DrawText(NAME, WIDTH/2-40, 10, 15, WHITE);
			DrawText(wordToDiscover, WIDTH/2-40, HEIGHT/2, 20, WHITE);
			DrawText(TextFormat("[%zu] %s", ws, maskedWord), WIDTH/2-45, HEIGHT/2+40, 20, WHITE);
		EndDrawing();
	}

	free(wordToDiscover);
	free(maskedWord);
	
	CloseWindow();
	return(EXIT_SUCCESS);
}
