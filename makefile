CC=g++
CFLAGS=-Wall -lm  -std=c++0x -I/usr/X11R6/include -L/usr/local/include
LIBS= -lglfw -lGL -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lGLEW -lSOIL
EXECUTABLE=output
SOURCES=src/main.cpp src/loadshaders.cpp

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LIBS)


# g++ main.o -o main.exec -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
