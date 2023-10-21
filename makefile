GCC=gcc
CFLAGS= -I ./include -lpthread ./include/*.c

PROGS = threads process

all: $(PROGS)

threads:
	$(GCC) $(CFLAGS) -o ./bin/threads ./src/hdispersa.c

process:
	$(GCC) $(CFLAGS) -o ./bin/process ./src/pdispersa.c