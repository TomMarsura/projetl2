CC=gcc
CFLAGS=-c -Wall
OBJECTS=game.o menu.o
EXECUTABLE=game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

game.o: game.c game.h
	$(CC) $(CFLAGS) game.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) menu.c

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
