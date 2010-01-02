/* TODO:
   Fill in the rest of the video formats
   check for redundancy in storing height and width information
   */


#ifndef FRACTALVIEWER_H
#define FRACTALVIEWER_H

#include "SDL/SDL.h"

template<class FractalAlgorithm> class FractalViewer {

	private:
		SDL_Surface *screen;
		int width, height;
		int *pixel_data;
		double center_x, center_y;
		double increment;
		FractalAlgorithm fa;

		/* Draws a pixel on the screen (RGB) */
		void pixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);

	public:

		/* Uses an existing screen */
		FractalViewer(SDL_Surface *screen);

		/* updates the screen with the new fractal */
		void update();
};

/* Draws a pixel on the screen (RGB) */
template <class FractalAlgorithm>
void FractalViewer<FractalAlgorithm>::pixel(int x, int y, Uint8 R, Uint8 G, Uint8 B) {
	Uint32 color = SDL_MapRGB(this->screen->format, R, G, B);

	if(SDL_MUSTLOCK(screen)) {
		if(SDL_LockSurface(screen) < 0) {
			return;
		}
	}

	/* Try different screen formats */
	switch(this->screen->format->BytesPerPixel) {
		case 1:
		case 2:
		case 3:
		case 4: {
					Uint32 *bufp;
					bufp = (Uint32 *)this->screen->pixels + y*this->screen->pitch/4 + x;
					*bufp = color;
				}
				break;
	}

	if(SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}

	SDL_UpdateRect(this->screen, x, y, 1, 1);
}


/* Uses an existing screen */
template <class FractalAlgorithm>
FractalViewer<FractalAlgorithm>::FractalViewer(SDL_Surface *screen) {
	this->screen = screen;
	this->width = screen->w;
	this->height = screen->h;
	this->fa = fa;
	this->center_x = 0.64; 
	this->center_y = -0.5;
	this->increment = 0.1;
}

/* updates the screen with the new fractal */
template <class FractalAlgorithm>
void FractalViewer<FractalAlgorithm>::update() {
	int x, y, iters;
	double x_min, x_max, y_min, y_max, x_scale, y_scale, z_x, z_y;

	x_min = this->center_x - this->increment;
	x_max = this->center_x + this->increment;

	y_min = this->center_y - this->increment;
	y_max = this->center_y + this->increment;

	x_scale = (x_max - x_min) / (this->height - 1);
	y_scale = (y_max - y_min) / (this->width - 1);

	for(y = 0; y < this->width; y++) {
		z_y = y_max - y * y_scale;
		for(x = 0; x < this->height; x++) {
			z_x = x_max - x * x_scale;

			if((iters = fa.in_set(z_x, z_y)) == -1) {
				pixel(y, x, 16, 16, 16);
			} else {
				pixel(y, x, iters % 255, iters / 255, iters / 255);
			}

		}
	}
}
#endif

