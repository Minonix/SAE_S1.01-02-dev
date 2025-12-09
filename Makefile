# Nom du compilateur
CC = gcc

# Options de compilation
# -Wall -Wextra -Werror: Affiche tous les avertissements utiles
# -g3 : Ajoute les informations de débogage
# -IHeaders : Spécifie que les fichiers d'en-tête (.h) se trouvent dans le dossier Headers
CFLAGS = -Wall -Wextra -Werror -g3 -IHeaders -Wl,--stack=17000000

# Nom de l'exécutable final
EXEC = main.exe

# Dossier pour les fichiers objets
OBJDIR = obj

# Trouver automatiquement tous les fichiers sources .c dans le dossier Sources
SRCS = $(wildcard Sources/*.c)

# Générer les noms des fichiers objets en remplaçant Sources/*.c par obj/*.o
OBJS = $(patsubst Sources/%.c, $(OBJDIR)/%.o, $(SRCS))

# Règle par défaut (celle qui est exécutée si on tape juste "make")
all: $(EXEC)

# Règle pour créer l'exécutable à partir des fichiers objets
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Règle pour compiler les fichiers sources (.c) en fichiers objets (.o)
# $@ est le nom de la cible (ex: obj/main.o)
# $< est le nom de la première dépendance (ex: Sources/main.c)
$(OBJDIR)/%.o: Sources/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< 

# Règle pour créer le dossier des objets s'il n'existe pas
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJS) $(OBJDIR)
fclean: clean
	rm -rf $(EXEC)
re: fclean all