CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude
SRC = $(wildcard src/*.c)

canteen: $(SRC) include/canteen.h
	mkdir -p data
	$(CC) $(CFLAGS) -o canteen $(SRC)

clean:
	rm -f canteen canteen.exe
