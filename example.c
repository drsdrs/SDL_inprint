#include "SDL.h"
#include "SDL_inprint.h"

int main( int argc, char* args[] ) 
{
	SDL_Surface *tv; 

	Uint32 width = 640;
	Uint32 height = 480;
	Uint32 bpp = 32;
	Uint32 flags = SDL_HWSURFACE;

	int i; for (i = 1; i < argc; i++) if (!strcasecmp("--fulltv", args[i])) flags |= SDL_FULLtv;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		exit(-1);
	}

	if ((tv = SDL_SetVideoMode(width, height, bpp, flags)) == 0) {
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
       	exit(-1);
	}

	SDL_FillRect(tv, NULL, 0x333333);

	prepare_inline_font();
	
/*	infont(SDL_LoadBMP("fonts/oddball6x8.bmp")); */

	incolor(0xFF0000, 0x333333);

	inprint(tv, "Hello World!", 10, 10);

	incolor(0x000000, 0xFFFFFF);

	inprint(tv, "A QUICK BROWN FOX JUMPS OVER A LAZY DOG!", 10, 30);
	inprint(tv, "a quick brown fox jumps over a lazy dog?", 10, 60);
	inprint(tv, "`'.,:;0123456789{}()[]|\\/-+*=!@#$%^&", 10, 90);

	/* Wait for a while */
	for (i = 1000; i > 20; i--) { SDL_Flip(tv); SDL_Delay(10); }

	kill_inline_font();

	SDL_Quit(); 
	return 0; 
}