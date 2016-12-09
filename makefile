CC=g++
CFLAGS=-Wall -lm  -std=c++0x -I/usr/X11R6/include -L/usr/local/include
LIBS= -lglfw -lGL -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lGLEW -lSOIL -I/usr/include/glm
EXECUTABLE=asteroids
SOURCES=src/main.cpp src/loadshaders.cpp

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LIBS)

