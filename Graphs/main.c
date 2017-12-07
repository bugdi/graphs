#include <SDL.h>
#include <stdio.h>
#include <SDL_syswm.h>
#include "resource.h"


#include "window.h"
#include "loop.h"

#include "textures.h"
#include "draw.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TRUE 1;
#define FALSE 0;

SDL_Surface* gScreenSurface = NULL;



int init()
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return FALSE;
	}
	else
	{
		//Create window
		SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
		gWindow = SDL_CreateWindow("New - Graphs", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, /*SDL_WINDOW_SHOWN*/ NULL);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return FALSE;
		}
		else
		{

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return FALSE;
			}
				//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		
		}
	}

	load_global_font("E:\\Marci\\source\\repos\\IntroToSDL\\Debug\\font2.ttf");

	return TRUE;
}




void close()
{

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	
	//Quit SDL subsystems
	SDL_Quit();
}
int main(int argc, char** argv)
{
	int quit, ticks, lastTicks;
	if (!init())
	{
		printf("Failed to initialize!\n");
		return 1;
	}
	lastTicks = SDL_GetTicks();
	quit = 0;
	gameInit();
	while (!quit)
	{
		SDL_Event e;
		//e.type = SDL_CREATE
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = 1;
				break;
			}
			else if (e.type == SDL_SYSWMEVENT) {

				switch (e.syswm.msg->msg.win.msg)
				{
				case WM_CREATE:
					create_menu(e.syswm.msg->msg.win.hwnd);
					break;

				case WM_COMMAND:
					window_command(e.syswm.msg->msg.win.hwnd, LOWORD(e.syswm.msg->msg.win.wParam));
					break;
				}

			}
			else {
				update(e);
			}
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);
			draw();
			SDL_RenderPresent(gRenderer);
		}
	}
	
	gameClose();
	return 0;
}