# Makefile
# --------
# Automatisation de la compilation du projet Restaurant.
# - Définit le compilateur (gcc) et les options (-Wall, -pthread, -Iinclude).
# - Compile chaque fichier .c en .o.
# - Lie les objets pour créer l'exécutable "restaurant".
# - Règle "clean" : supprime les fichiers objets et l'exécutable.
# - Règle "run" : compile et exécute directement le programme.
#
# Rôle : simplifier la compilation et l'exécution du projet.


# Compilateur et options
CC = gcc
CFLAGS = -Wall -pthread -Iinclude

# Fichiers sources et objets
SRC = src/main.c src/commande.c src/file.c src/serveur.c src/cuisinier.c src/log.c src/interaction.c src/globals.c
OBJ = $(SRC:.c=.o)

# Nom de l'exécutable
TARGET = restaurant

# Règle principale
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Règle générique pour compiler chaque .c en .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f src/*.o $(TARGET)

# Exécution directe
run: $(TARGET)
	./$(TARGET)
