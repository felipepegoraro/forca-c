#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "./src/readwords.h"
#include "./src/maskword.h"
#include "./src/getInput.h"

#define  WIDTH 600
#define HEIGHT 400
#define   NAME "Jogo da Forca"

int main(void)
{
	int pos=0, try=15, key;
	bool flag = true;
	char **words = malloc(sizeof(char *)*LIN);
	for (int i=0; i<LIN; i++) words[i] = malloc(sizeof(char)*COL);

	if (!words){
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	readWord(words);

	char *wordToDiscover = malloc(sizeof(char)*COL);
	if (!wordToDiscover){
		perror("malloc");
		exit(EXIT_FAILURE);
	}

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

		BeginDrawing();
			if (!flag) break;

			DrawText(NAME, WIDTH/3, 10, 30, WHITE);
			DrawText(wordToDiscover, WIDTH/2-40, HEIGHT/2, 20, WHITE);
			DrawText(TextFormat("[%d] %s", try, maskedWord), WIDTH/2-45, HEIGHT/2+40, 20, WHITE);

			if (try <= 0){
				DrawText("voce perdeu: zero tentativas!", WIDTH/3-30, HEIGHT/3, 20, WHITE );
				flag = false;
			}

			if (strcmp(maskedWord, wordToDiscover) == 0){
				DrawText("voce acertou", WIDTH/2-60, HEIGHT/3, 20, WHITE );
				flag = false;
			}

			ClearBackground(BLACK);
			if ((key = GetCharPressed()) >= 32 && key <= 126)
				fillWord(wordToDiscover, maskedWord, &pos, &try, key);

		EndDrawing();
	}

	sleep(2);
	
	CloseWindow();

	printf("T: %s\n", wordToDiscover);
	printf("R: %s\n", maskedWord);

	return(EXIT_SUCCESS);
}
