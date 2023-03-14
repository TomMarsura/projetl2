# Nom des fichiers sources
SOURCES = src/game.c src/menu.c src/sdl.c test/test_main.c test/test_menu.c test/test_game.c

# Nom des fichiers objets
OBJECTS = obj/game.o obj/menu.o obj/sdl.o obj/test_main.o obj/test_menu.o obj/test_game.o

# Nom des fichiers d'en-tête
HEADERS = lib/game.h lib/menu.h lib/sdl.h

# Nom du fichier exécutable
EXECUTABLES = bin/test_game bin/test_menu bin/test_main

# Compilateur et options de compilation
CC = gcc
CFLAGS = -c -Wall -Iinclude 

# Options pour la bibliothèque SDL
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm

# Règle par défaut pour créer tous les fichiers objets et exécutables
all: $(EXECUTABLES)

# Règle pour créer les fichiers objets à partir des fichiers sources
$(OBJECTS): obj/%.o : src/%.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

# Règles pour créer les fichiers exécutables à partir des fichiers objets
bin/test_game: obj/game.o obj/sdl.o obj/test_game.o
	$(CC) $^ $(LDFLAGS) -o $@

bin/test_menu: obj/menu.o obj/sdl.o obj/test_menu.o
	$(CC) $^ $(LDFLAGS) -o $@

bin/test_main: obj/game.o obj/menu.o obj/sdl.o obj/test_main.o
	$(CC) $^ $(LDFLAGS) -o $@

# Règle pour nettoyer le dossier en supprimant les fichiers objets et exécutables
clean:
	rm -f $(OBJECTS) $(EXECUTABLES)
