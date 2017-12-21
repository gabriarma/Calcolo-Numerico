#CC = gcc
#CFLAGS= -Imatrix_lib
CFLAGS= -Wall -pedantic -Imatrix_lib
BIN_DIR = bin
DATA_DIR = data
LIB_DIR = matrix_lib

LDFLAGS = -L$(BIN_DIR) -lmatrix -lrt
MATRIX_LIB=$(BIN_DIR)/libmatrix.a
MAIN=$(BIN_DIR)/main
MAIN_OBJS=$(BIN_DIR)/main.o $(BIN_DIR)/es1_a.o  $(BIN_DIR)/es1_b.o $(BIN_DIR)/es1_c.o $(BIN_DIR)/es2.o  $(BIN_DIR)/es3.o

EXECS = $(MAIN)

all: $(EXECS)

$(EXECS): | $(DATA_DIR)

#common library
$(MATRIX_LIB): $(BIN_DIR)/matrix.o | $(BIN_DIR)
	ar rcs $@ $(BIN_DIR)/*.o
$(BIN_DIR)/matrix.o: matrix_lib/fileNameLis_lib.h matrix_lib/MyMatrix.h matrix_lib/raccoltaEsercizi.h matrix_lib/MyMatrix.c
	$(CC) $(CFLAGS) -c -o $@ matrix_lib/MyMatrix.c

#MAIN
$(MAIN): $(MAIN_OBJS) $(MATRIX_LIB) | $(BIN_DIR)
	$(CC) -o $@ $(MAIN_OBJS) $(LDFLAGS)
$(BIN_DIR)/main.o: main/main.c matrix_lib/raccoltaEsercizi.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ main/main.c
$(BIN_DIR)/es1_a.o: es1/es1_a.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ es1/es1_a.c
$(BIN_DIR)/es1_b.o: es1/es1_b.c matrix_lib/MyMatrix.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ es1/es1_b.c
$(BIN_DIR)/es1_c.o: es1/es1_c.c matrix_lib/MyMatrix.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ es1/es1_c.c
$(BIN_DIR)/es2.o: es2/es2.c matrix_lib/MyMatrix.h matrix_lib/fileNameLis_lib.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ es2/es2.c
$(BIN_DIR)/es3.o: es3/es3.c matrix_lib/MyMatrix.h matrix_lib/fileNameLis_lib.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ es3/es3.c

# Directories
$(BIN_DIR):
	mkdir $(BIN_DIR)
$(DATA_DIR):
	mkdir $(DATA_DIR)
	mkdir $(DATA_DIR)/A1 $(DATA_DIR)/A2 $(DATA_DIR)/B $(DATA_DIR)/C

clean:
	rm -rf $(BIN_DIR) $(DATA_DIR)