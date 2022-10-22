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
	int pos=0, try=5, key;
	int spd_frames = 8, acc_frames = 0, curr_frame = 0;

	int actry = try;

	bool flag = true;

	char *rep = malloc(sizeof(char)*6); 
	if (!rep){
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", rep);

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

	free(words);
	size_t ws = strlen(wordToDiscover);
	char *maskedWord = malloc(sizeof(char)*ws+1);

	strcpy(maskedWord, mask(wordToDiscover));
	maskedWord[ws]='\0';

	InitWindow(WIDTH, HEIGHT, NAME);

	Texture2D hangman = LoadTexture("./img/boneco_6_grupo_no_bg.png");
	float hgm_width  = hangman.width;
	float hgm_height = hangman.height;

	Vector2 position = { (float)WIDTH/3+35, (float)HEIGHT/3-50 };
	Rectangle frame_rec = { 0.0f, 0.0f, (float)hgm_width/6, (float)hgm_height };

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		acc_frames++;
		if (try < actry && acc_frames >= (60/spd_frames)){
			acc_frames = 0;
			curr_frame++;
			if (curr_frame > 5) curr_frame = 0;
			frame_rec.x = (float)curr_frame*(float)hgm_width/6;
			actry--;
		}

		BeginDrawing();
			if (!flag) break;

			// DrawText(wordToDiscover, WIDTH/2-40, HEIGHT/2, 20, WHITE);
			DrawText(NAME, WIDTH/3, 10, 30, WHITE);
			DrawText(TextFormat("[%d] %s", try, maskedWord),
					WIDTH/2-40-(3*strlen(maskedWord)), HEIGHT/2+70, 20, WHITE);

			DrawText(TextFormat("r: %s", rep),
					WIDTH/2-40-(2*strlen(rep)), HEIGHT-50, 20, WHITE);

			if (try <= 0){
				DrawText("voce perdeu: zero tentativas!", WIDTH/3-50, HEIGHT/2+10, 20, WHITE );
				DrawText(TextFormat("%s", wordToDiscover), 
						WIDTH/3+30+(2*strlen(maskedWord)), HEIGHT/2+30, 20, WHITE );
				flag = false;
			}

			if (strcmp(maskedWord, wordToDiscover) == 0){
				DrawText("voce acertou", WIDTH/3+30, HEIGHT/2+20, 20, WHITE );
				flag = false;
			}

			ClearBackground(BLACK);

			if ((key = GetCharPressed()) >= 32 && key <= 126)
				fillWord(wordToDiscover, maskedWord, rep, &pos, &try, key);

			DrawTextureRec(hangman, frame_rec, position, WHITE);
		EndDrawing();
	}

	sleep(2);
	
	UnloadTexture(hangman);
	CloseWindow();

	printf("T: %s\n", wordToDiscover);
	printf("R: %s\n", maskedWord);
	printf("E: %s\n", rep);

	return(EXIT_SUCCESS);
}
