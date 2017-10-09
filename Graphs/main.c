#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_syswm.h>


#include "window.h"
#include "loop.h"
#include "textures.h"

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
			//if (!init_window(gWindow))
			//{
				//return FALSE;
			//}
			//SDL_ShowWindow(gWindow);
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return FALSE;
			}
				//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return FALSE;
			}
		}
	}

	return TRUE;
}

int loadMedia()
{
	//texture = loadTexture(gRenderer, "C:\\Users\\Marci\\source\\repos\\IntroToSDL\\redball.png");
	return TRUE;
}

SDL_Surface* loadSurface(const char* path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

void close()
{
	//Deallocate surface
	//SDL_FreeSurface(gHelloWorld);
	//gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	
	//Quit SDL subsystems
	SDL_Quit();
}
int my_main(int* quit, int ticks)
{
	SDL_Event e;
	//e.type = SDL_CREATE
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			*quit = 1;
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
			update(e, ticks);
		}
		//Update the surface
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		draw();
		SDL_RenderPresent(gRenderer);
	}
}
int main(int argc, char** argv)
{
	int quit, ticks, lastTicks;
	if (!init())
	{
		printf("Failed to initialize!\n");
		return FALSE;
	}
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		return FALSE;
	}
	lastTicks = SDL_GetTicks();
	quit = 0;
	gameInit();
	while (!quit)
	{
		ticks = SDL_GetTicks();
		my_main(&quit, ticks - lastTicks);
		lastTicks = ticks;
	}
	
	gameClose();
	return 0;
}