#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include <unistd.h>
#include "./src/readwords.h"
#include "./src/maskword.h"
#include "./src/getInput.h"

#define  WIDTH 600
#define HEIGHT 400
#define   NAME "Jogo da Forca"

int main(void)
{
	int pos=0, try=15;
	char **words = malloc(sizeof(char *)*LIN);
	for (int i=0; i<LIN; i++) words[i] = malloc(sizeof(char)*COL);

	if (!words){
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	readWord(words);

	char *wordToDiscover = malloc(sizeof(char)*COL);
	strcpy(wordToDiscover, getWord(words));

	printf("%s\n", wordToDiscover);

	free(words);
	size_t ws = strlen(wordToDiscover);
	char *maskedWord = malloc(sizeof(char)*ws+1);

	strcpy(maskedWord, mask(wordToDiscover));
	maskedWord[ws]='\0';

	InitWindow(WIDTH, HEIGHT, NAME);
	SetTargetFPS(10);

	while (!WindowShouldClose()){
		fillWord(wordToDiscover, maskedWord, &pos, &try);

		ClearBackground(BLACK);
		BeginDrawing();
			DrawText(NAME, WIDTH/2-40, 10, 15, WHITE);
			DrawText(wordToDiscover, WIDTH/2-40, HEIGHT/2, 20, WHITE);
			DrawText(TextFormat("[%d] %s", try, maskedWord), WIDTH/2-45, HEIGHT/2+40, 20, WHITE);

		if (try <= 0){
			DrawText("voce perdeu: zero tentativas!", 
					WIDTH/3-30, HEIGHT/2, 20, WHITE );
			sleep(1);
			break;
		}

		EndDrawing();
	}


	/* free(wordToDiscover); */
	/* free(maskedWord); */
	
	CloseWindow();
	printf("A: %s\n", wordToDiscover);
	return(EXIT_SUCCESS);
}
