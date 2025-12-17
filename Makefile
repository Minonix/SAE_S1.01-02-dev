CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -IHeaders
LDFLAGS = -Wl,-z,stack-size=16777210
EXEC = main.exe
OBJDIR = obj
SRCS = $(wildcard Sources/*.c)
OBJS = $(patsubst Sources/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(EXEC)

# Ici on utilise LDFLAGS pour l'édition de liens
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

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