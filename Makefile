CC = gcc
BIN = bin/
SRC = src/
EXEC = k_means
CFLAGS = -O2
THREADS = 2
CP_CLUSTERS = 4

.DEFAULT_GOAL = k_means

k_means:	$(SRC)k_means.c 
	$(CC) $(CFLAGS) $(SRC)k_means.c -o $(BIN)$(EXEC)


clean:
	rm -r bin/*

runseq:
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS)

runpar:
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) $(THREADS)