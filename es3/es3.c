#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raccoltaEsercizi.h"
#include "fileNameLis_lib.h"


void esercizio3(const char *const dir)
{
	//risolvere sistema lineare Ax~=b+∂b
	//∂b=||b||∞ * (-0.01,0.01,-0.01,...,0.01)^t

	//CREAZIOE MATRICE A
	char *s;
	s = nomeFile(dir, fileNameMatrice);
	FILE *matrixFile = fopen(s, "r");
	free(s);
	if (!matrixFile)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	MATRIX *A = create_matrix(matrixFile);
	fclose(matrixFile);
	puts("matrice A creata");

	//CREAZIOE MATRICE B
	s = nomeFile(dir, file_b);
	FILE *vectorFile = fopen(s, "r");
	free(s);
	if (!vectorFile)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	MATRIX *b = create_matrix(vectorFile);
	fclose(vectorFile);
	puts("matrice b creata");

	//calcolo norma vettore b
	elem n = 0;
	MATRIX *b_norma_t = clone_matrx(b);
	for (int i = 0; i<b->row; i++)
	{
		if (((b_norma_t->matrix)[0][i])<0)
			((b_norma_t->matrix)[0][i]) = -((b_norma_t->matrix)[0][i]);
		if ((b_norma_t->matrix)[0][i]>n)
			n = (b_norma_t->matrix)[0][i];
	}
	/*
	*/
	printf("norma infinito di b %f\n", n);
	/*
	*/
	//calcolo vettore ∂b
	MATRIX *delta_b = clone_matrx(b);
	for (int i = 0; i<delta_b->row; i++)
	{
		(delta_b->matrix)[i][0] = n*(-0.01); i++;
		(delta_b->matrix)[i][0] = n*(+0.01);
	}

	//creo vettore b+∂b
	MATRIX *b_modificato = clone_matrx(delta_b);
	for (int i = 0; i<delta_b->row; i++)
	{
		(b_modificato->matrix)[i][0] = (b->matrix)[i][0] + (delta_b->matrix)[i][0];
	}

	//APPLICAZIONE RIDUZIONE DI GAUSS SUL SISTEMA A|(b+∂b)
	MATRIX *A_b_modf = create_sistem_matrix_vector(A, b_modificato);
	MATRIX *A_b_modf_ridotto = gauss_elimination(A_b_modf);
	//SEPARO LA MATRICE A, b dal sisitema
	MATRIX *A_ridotto, *b_ridotto;
	divide_sistem_matrix_vector(A_b_modf_ridotto, (void **)&A_ridotto, (void **)&b_ridotto);
	//soluzione Ax~=b+∂b
	MATRIX *x_ = sost_indietro(A_ridotto, b_ridotto);
	//stampa x nuovo
	printf("Stanpo il vettore x perturbato\n");
	s = nomeFile(dir, fileX_p);
	FILE* f_p = fopen(s, "w");
	if (!f_p)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	print_matrice(x_, f_p);
	print_matrice(x_, stdout);
	fclose(f_p);
}