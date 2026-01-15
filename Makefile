CC = gcc

# Options de compilation
# -Wall -Wextra -Werror: Affiche tous les avertissements utiles
# -g3 : Ajoute les informations de débogage
# -IHeaders : Spécifie que les fichiers d'en-tête (.h) se trouvent dans le dossier Headers
CFLAGS = -Wall -Wextra -Werror -g3 -IHeaders

# Détection de l'OS
ifdef ComSpec
    OS_DETECTED = Windows_NT
else
    OS_DETECTED = $(OS)
endif

ifeq ($(OS_DETECTED),Windows_NT)
    LDFLAGS = -Wl,--stack=1677721600
else
    LDFLAGS = -Wl,-z,stack-size=16777216
endif

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
ifeq ($(OS_DETECTED),Windows_NT)
	if not exist $(OBJDIR) mkdir $(OBJDIR)
else
	mkdir -p $(OBJDIR)
endif

clean:
ifeq ($(OS_DETECTED),Windows_NT)
	if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
else
	rm -rf $(OBJDIR)
endif
fclean: clean
ifeq ($(OS_DETECTED),Windows_NT)
	if exist $(EXEC) del $(EXEC)
else
	rm -rf $(EXEC)
endif
re: fclean all