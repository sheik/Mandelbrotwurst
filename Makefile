


CPPFILES=FractalViewer.cpp Mandelbrot.cpp

OBJS=$(CPPFILES:.cpp=.o)

CC = gcc
CXX = g++

CXXFLAGS = -ggdb -lSDL

Mandelbrotwurst : $(OBJS) 
	g++ -o Mandelbrotwurst Mandelbrotwurst.cpp -lSDL -lGL $(OBJS)
FractalViewer.o : FractalViewer.cpp


clean:
	rm -rf *.o
	rm Mandelbrotwurst
