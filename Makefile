# Variables
CC = gcc
CFLAGS = -Wall -Wextra
EXEC = ProjetInfo
SRC = main.c qcm.c

# Regle par defaut
all: $(EXEC)

# Compilation de l'executable
$(EXEC): $(SRC) qcm.h
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

# Nettoyage des fichiers generes
clean:
	rm -f $(EXEC)
