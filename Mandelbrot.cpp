
#include "Mandelbrot.h"

Mandelbrot::Mandelbrot() {
	this->max_iterations = 2000;
}

/* Compute whether the complex number x + yi is in
   the mandelbrot set. Return -1 if True, else return
   the number of iterations before being thrown out.
   */

int Mandelbrot::in_set(double y, double x) {
	double zx, zy, x_orig = x, y_orig = y;
	int is_inside = -1;

	for(int n = 0; n < this->max_iterations; ++n) {
		zx = x * x;
		zy = y * y;

		if((zx + zy) > 4) {
			is_inside = n;
			break;
		}

		y = 2 * x * y + y_orig;
		x = zx - zy + x_orig;
	}

	return is_inside;
}

