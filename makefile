CC=gcc
CFLAGS=-c -Wall
OBJECTS=src/game.o src/menu.o
EXECUTABLE=game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

src/game.o: src/game.c lib/game.h
	$(CC) $(CFLAGS) src/game.c

src/menu.o: src/menu.c lib/menu.h
	$(CC) $(CFLAGS) src/menu.c

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
