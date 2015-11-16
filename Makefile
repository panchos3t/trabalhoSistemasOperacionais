SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
OUT = fat_sim
CC = gcc

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(OBJ)

# compila todos os .c para .o
%.o: %.c
	$(CC) -o $@ -c $<

clean:
	rm -rf *.o

clean_all:
	rm -rf *.o
	rm -rf fat.part $(OUT)