## project name (generate executable with this name)
#TARGETS  = main
#
#CC       = gcc
## compiling flags here
#CFLAGS   = -std=c99 -Wall -I -Llib.
#
#LINKER   = gcc
## linking flags here
#LFLAGS   = -Wall -I. -lm
#
#SDLFALGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
#
## change these to proper directories where each file should be
#SRCDIR   = src
#OBJDIR   = obj
#BINDIR   = bin
#TRGS     := $(TARGETS:%=$(BINDIR)/%)
#
#DIRS     = $(OBJDIR) $(BINDIR) 
#
#.PHONY: DIRS
#all: $(DIRS) $(SDLFALGS) $(TRGS)
#
#$(OBJDIR):
#	mkdir -p $(OBJDIR)
#$(BINDIR):
#	mkdir -p $(BINDIR)
#
#SOURCES  := $(wildcard $(SRCDIR)/*.c)
#INCLUDES := $(wildcard $(SRCDIR)/*.h)
#OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
#MAINS    := $(TARGETS:%=$(OBJDIR)/%.o)
## Liste des fichiers .o sans ceux contenant un main
#OBJS     := $(filter-out $(MAINS),$(OBJECTS))
#rm       = rm -f
#
#
##$(BINDIR)/$(TARGET): $(OBJECTS)
#$(TRGS): $(OBJECTS)
#	@$(LINKER) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(LFLAGS) -o $@
#	@echo "Linking complete!"
#
#$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
#	@$(CC) $(CFLAGS) -c $< -o $@
#	@echo "Compiled "$<" successfully!"
#
#.PHONY: clean
#clean:
#	@$(rm) $(OBJECTS)
#	@echo "Cleanup complete!"
#
#.PHONY: remove
#remove: clean
#	@$(rm) $(BINDIR)/$(TARGETS)
#	@echo "Executable removed!"




# project name (generate executable with this name)
TARGETS  = main
TEST_TARGETS = test_profils

CC       = gcc
rm = rm -f
# compiling flags here
CFLAGS   = -std=c99 -Wall -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lm -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TESTDIR  = test
TRGS     := $(TARGETS:%=$(BINDIR)/%) $(TEST_TARGETS:%=$(TESTDIR)/%)

DIRS     = $(OBJDIR) $(BINDIR) $(TESTDIR)

.PHONY: DIRS all test_profils
all: $(DIRS) $(TARGETS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
$(TESTDIR):
	mkdir -p $(TESTDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS    := $(TARGETS:%=$(OBJDIR)/%.o)
# Liste des fichiers .o sans ceux contenant un main
OBJS     := $(filter-out $(MAINS),$(OBJECTS))

# Compilation des fichiers sources
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(TESTDIR)/test_compils.o: $(TESTDIR)/test_profils.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

# Compilation du main
$(TARGETS): $(OBJS) $(MAINS)
	@$(LINKER) $(OBJS) $(OBJDIR)/$@.o $(LFLAGS) -o $(BINDIR)/$@
	@echo "Linking complete!"

# Création de l'exécutable des tests
test_profils: $(OBJS) $(TESTDIR)/test_profils.o
	@$(LINKER) $(OBJS) $(TESTDIR)/test_profils.o $(LFLAGS) -o $(TESTDIR)/$@
	@echo "Linking complete!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS) $(MAINS)
	@$(rm) $(TESTDIR)/test_profils.o
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGETS)
	@echo "Executable removed!"
