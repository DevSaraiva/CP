CC = gcc
BIN = bin/
SRC = src/
EXEC = k_means
EXEC_SEQ = k_means_seq
CFLAGS = -O2 -fopenmp
CFLAGS_SEQ = -O2

all: k_means k_means_seq

k_means:	$(SRC)k_means.c 
	$(CC) $(CFLAGS) $(SRC)k_means.c -o $(BIN)$(EXEC)

k_means_seq:	$(SRC)k_means.c 
	$(CC) $(CFLAGS_SEQ) $(SRC)k_means.c -o $(BIN)$(EXEC_SEQ)

clean:
	rm -r bin/*

runseq:
	./$(BIN)$(EXEC_SEQ) 10000000 $(CP_CLUSTERS)

runpar:
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) $(THREADS)