#ifndef MANDELBROT_H
#define MANDELBROT_H

class Mandelbrot {
	private:
		int max_iterations;
	public:
		Mandelbrot();
		int in_set(double x, double y);
};

#endif
