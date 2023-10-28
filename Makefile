CC=gcc
LFLAGS=-lSDL2 -lSDL2_ttf
CFLAGS=-w -I.
DEPS= dataStructures.h
OBJS=main.o dataStructures.o

all: main

clean:
	rm main *.o

main: $(OBJS)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@

debug: $(OBJS)
	$(CC) -g $^ $(CFLAGS) $(LFLAGS) -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@


