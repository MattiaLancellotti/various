CC = gcc
CFLAGS = -O2

SRC = main.c
BIN = tty_menu

# If the binary gets compiled with these flags a bunch of debugging messages
# will be displayed if errors occur.
ifdef DEBUG
   CFLAGS += -ggdb -fsanitize=address,undefined -fno-omit-frame-pointer
endif

# Compiling the binary
$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)
