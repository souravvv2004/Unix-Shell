CC = gcc
CFLAGS = -Wall  -Iinclude -D_POSIX_C_SOURCE=200809L
LIBS = -lreadline

SRC = src/main.c src/executor.c src/parser.c \
      src/builtins.c src/redirection.c \
      src/pipe.c src/signals.c

OUT = myshell

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)

run: all
	./$(OUT)
