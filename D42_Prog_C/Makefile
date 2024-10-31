CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRC = src/main.c
EXEC = D42_Prog_C

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(EXEC)