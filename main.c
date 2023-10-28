#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include "dataStructures.h"

#define WIDTH 640
#define HEIGHT 480

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font;
int fontPosition;
char * input;
DStrArray stringArr;

char * concatStrings(const char * s1, const char * s2);
int init();
int kill();
void initDStrArray(DStrArray * arr, size_t initialSize);
void insertDStrArray(DStrArray * arr, const char * element);
void deleteDStrArray(DStrArray * arr, size_t pos);
void freeDStrArray(DStrArray * arr);
void loadTextForRendering(char * input, int posx, int posy);

int main(int argc, char ** argv)
{
	init();	
	initDStrArray(&stringArr, 2);
	input = "";

	while(1)
	{
		int finished = 0;
		SDL_Event event;

		SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
		SDL_RenderClear( renderer );

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					finished = 1;
					break;
				case SDL_TEXTINPUT:
					input = concatStrings(input, event.text.text);
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_BACKSPACE && strlen(input)){
						input[strlen(input) - 1] = '\0';
						if(strlen(input) <= 0)
						{
							 
						}
					}
					break;
			}
		}
		
		if(finished)
		{
			break;
		}

		int w,h;
		int size = TTF_SizeText(font, input, &w, &h); 
		int y = h;

		if(w - 1 >= WIDTH)
		{
			insertDStrArray(&stringArr, input);
			printf("size of array: %ld\n", stringArr.used);
			input[0] = input[strlen(input) - 1];
			input[1] = '\0';
		}
		
		
		for(int i = 0; i < stringArr.used; i++)
		{
			if(strlen(stringArr.array[i]))
			{
				loadTextForRendering(stringArr.array[i], 0, y);
				y+=h;
			}
		}

		if(strlen(input))
		{
			loadTextForRendering(input, 0, y);
		}
			SDL_RenderPresent(renderer);
	}

	kill();
}

int init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("Issue when initializing SDL: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0)
	{
		SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	if(TTF_Init() < 0)
	{
		SDL_Log("Failed to initialize ttf: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	font = TTF_OpenFont("lazy.ttf", 24); 
	if(!font)
	{
		SDL_Log("Failed to set up font: %s", SDL_GetError());
		SDL_Log("TTF_OpenFont issue: %s", TTF_GetError());
		SDL_Quit();
		return -1;
	}
	
	SDL_SetWindowTitle(window, "thesmallpad");
	SDL_StartTextInput();
	return 0;	
}

int kill()
{
	SDL_StopTextInput();
	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	renderer = NULL;
	window = NULL;

	TTF_Quit();
	SDL_Quit();
	free(input);

	return 0;
}

void loadTextForRendering(char * input, int posx, int posy)
{
	SDL_Color foreground = {0,0,0};
	SDL_Rect dest;

	SDL_Surface* text_surf = TTF_RenderText_Solid(font, input, foreground);

	if(text_surf == NULL)
	{
		printf("Shits fucked2\n");
	}

	SDL_Texture * text = SDL_CreateTextureFromSurface(renderer, text_surf);

	dest.w = text_surf->w;
	dest.h = text_surf->h;
	dest.x = posx;
	dest.y = posy;

	SDL_RenderCopy(renderer, text, NULL, &dest);

	SDL_DestroyTexture(text);
	SDL_FreeSurface(text_surf);

}


