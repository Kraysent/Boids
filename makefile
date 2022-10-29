.PHONY: all clean

CXX=g++
SDLCFLAGS=`sdl2-config --cflags --libs` -lSDL2_image

all: result

Vector.o: Vector.cpp Vector.h
	$(CXX) -c -o Vector.o Vector.cpp

Boid.o: Boid.cpp Boid.h Vector.h
	$(CXX) -c -o Boid.o Boid.cpp

boids.o: boids.cpp Boid.h Vector.h
	$(CXX) -c -o boids.o boids.cpp $(SDLCFLAGS)

result: boids.o Boid.o Vector.o
	$(CXX) -o result boids.o Boid.o Vector.o $(SDLCFLAGS)
