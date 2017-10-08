#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>



#include "loop.h"
#include "textures.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define EXIT_SUCCESS 1;
#define EXIT_FAILURE 0;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;



int init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return EXIT_FAILURE;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return EXIT_FAILURE;
			}
				//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return EXIT_FAILURE;
			}
		}
	}

	return EXIT_SUCCESS;
}

int loadMedia()
{
	//texture = loadTexture(gRenderer, "C:\\Users\\Marci\\source\\repos\\IntroToSDL\\redball.png");
	return EXIT_SUCCESS;
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
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			*quit = 1;
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
		return EXIT_FAILURE;
	}
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		return EXIT_FAILURE;
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