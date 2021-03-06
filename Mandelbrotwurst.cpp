#include <iostream>

#include <SDL/SDL.h>
#include "SDL/SDL_thread.h"
#include <GL/gl.h>
#include "Mandelbrot.h"
#include "FractalViewer.h"

int main(int argc, char *argv[]) {
	SDL_Surface *screen;
	SDL_Event event;

	int options = (
			SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN
			);

	// initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		std::cerr << "Unable to initialize SDL";
	}

	// Try to set video mode
	if( (screen = SDL_SetVideoMode(1366, 768, 32, options)) == NULL) {
		std::cerr << "Unable to create video window: " << SDL_GetError();
	}


	FractalViewer<Mandelbrot> *fv = new FractalViewer<Mandelbrot>(screen);

	while(SDL_WaitEvent(&event)) {

		switch(event.type) {
			case SDL_QUIT:
				return 0;
				break;
		}

		fv->update();
		SDL_Delay(3000);
		return 0;
	}
	return 0;
}


