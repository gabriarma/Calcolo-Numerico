#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define elem float

struct  {
    elem **matrix;
  int row;
  int column;
}typedef MATRIX;

/*costruttori di matrici*/
elem **new_matrix(int , int);       /*ritorna an array dinamico delle dimensioni passate*/
MATRIX *new_struct_MATRIX(int ,int );
MATRIX *create_matrix( FILE *stream );
MATRIX *clone_matrx(const void *const);
MATRIX *create_sistem_matrix_vector(void *, void *);
void free_matrix(void* );

/*Operazioni su matrici*/
void swap_row(void* ,int ,int );
MATRIX *matrix_multiplication(const void *const , const void *const );
MATRIX *gauss_elimination(void *);

/*Stampe di matrici*/
void print_matrice(const void *const);
void print_matrix_vertex(const void *const ,const void *const);


#endif //MYMATRIX_H
