#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyMatrix.h"

const char *tmpFile = "vettoreTuttiUni.txt";
const char *fileX = "matriceX.txt";
const char *fileX_ = "matriceX_.txt";
const char *file_b = "matrice_b.txt";
const char *fileA_b = "matrice_A|b.txt";

void createMatrix_x(const char* fileName, int row);

int esercizio2(const char *const fileName)
{
	//CREAZIOE MATRICE A E VETORE x
	FILE *matrixFile = fopen(fileName, "r");
	if (!matrixFile)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	MATRIX *A = create_matrix(matrixFile);
	fclose(matrixFile);
	//CALCOLO VETTORE b
	createMatrix_x(tmpFile, A->row);
	FILE* f = fopen(tmpFile, "r");
	MATRIX *x = create_matrix(f);
	fclose(f);
	MATRIX *b = matrix_multiplication(A, x);
	printf("\nIl vettore b e':\n");
	FILE *f1 = fopen(file_b, "w");
	if (!f1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	print_matrice(b, f1);
	print_matrice(b, stdout);
	fclose(f1);
	//APPLICAZIONE RIDUZIONE DI GAUSS SUL SISTEMA A|b
	MATRIX *A_b = create_sistem_matrix_vector(A, b);
	MATRIX *A_b_ridotto = gauss_elimination(A_b);
	printf("\nIl sistema A|b ridotto e':\n");
	FILE *f2 = fopen(file_b, "w");
	if (!f2)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	print_matrice(A_b_ridotto, f2);
	print_matrice(A_b_ridotto, stdout);
	fclose(f2);
	//CALCOLO DEL VETTORE x_
	MATRIX *A_ridotto = NULL, *b_ridotto = NULL;
	divide_sistem_matrix_vector(A_b_ridotto,(void **)&A_ridotto,(void **)&b_ridotto);
	if (A_ridotto == NULL || b_ridotto == NULL)
	{
		printf("problema\n");
		exit(-1);
	}
	printf("\nIl vettore x calcolato con la matrice A e il vettore b è:\n");
	MATRIX* x_ = sost_indietro(A_ridotto, b_ridotto);
	FILE *f3 = fopen(fileX_, "w");
	if (!f3)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	print_matrice(x_, f3);
	print_matrice(x_, stdout);
	fclose(f3);	
	free_matrix(A);
	free_matrix(x);
	free_matrix(x_);
	free_matrix(b);
	free_matrix(A_b);
	free_matrix(A_b_ridotto);
	return(0);
}

void createMatrix_x(const char* fileName, int row)
{
	FILE* matrixFile = fopen(fileName, "w");
	if (!matrixFile)
		fail_errno("Error creating file");
	fprintf(matrixFile, "%d %d\n", row, 1);
	for (int i = 0; i < row; i++)
	{
		fprintf(matrixFile, " 1");
	}
	fclose(matrixFile);
}