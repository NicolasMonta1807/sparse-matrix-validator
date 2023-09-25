CC=gcc
CFLAGS= -I ./include -lpthread ./include/*.c

makeAll: ./src/pdispersa.c ./src/hdispersa.c
	$(CC) -o ./bin/process ./src/pdispersa.c $(CFLAGS)
	$(CC) -o ./bin/threads ./src/hdispersa.c $(CFLAGS)
