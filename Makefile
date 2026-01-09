CC = gcc

# Options de compilation
# -Wall -Wextra -Werror: Affiche tous les avertissements utiles
# -g3 : Ajoute les informations de débogage
# -IHeaders : Spécifie que les fichiers d'en-tête (.h) se trouvent dans le dossier Headers
CFLAGS = -Wall -Wextra -Werror -g3 -IHeaders

#pour windows :
LDFLAGS = -Wl,--stack=1677721600
#pour Linux
# LDFLAGS = -Wl,-z,stack-size=16777216


# Nom de l'exécutable final
EXEC = main.exe
OBJDIR = obj
SRCS = $(wildcard Sources/*.c)
OBJS = $(patsubst Sources/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(EXEC)

# Ici on utilise LDFLAGS pour l'édition de liens
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Ici on utilise UNIQUEMENT CFLAGS pour compiler
$(OBJDIR)/%.o: Sources/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
fclean: clean
	rm -rf $(EXEC)
re: fclean all