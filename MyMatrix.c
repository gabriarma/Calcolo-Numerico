#include "MyMatrix.h"

/*
 *
 *
 */


elem **new_matrix(const int x,const int y)
{
    elem **matrix = (elem**)calloc((size_t)x, sizeof(elem*));

    for (int i = 0; i < x; i++)
    {
        matrix[i] = (elem*)calloc((size_t)y, sizeof(elem));
    }
    return matrix;
}

MATRIX *new_struct_MATRIX(const int r, const int c)
{
    if(r<0 || c<0)
        return NULL;
    MATRIX *m = (MATRIX *)malloc(sizeof(MATRIX));
    m->column = c;
    m->row = r;
    m->matrix = new_matrix(r,c);
    return m;
}

MATRIX *create_matrix( FILE *stream )
{
    int rows, columns;
    char* aux = malloc(sizeof(char)*16);
    fscanf( stream, "%d", &rows );
    fscanf( stream, "%d", &columns );
    MATRIX *m = new_struct_MATRIX(rows, columns);
    elem **matrix = m->matrix;
    for(int i = 0; i < rows; i++ )
    {
        for(int j = 0; j < columns; j++ ) {
            fscanf(stream,"%s",aux);
            matrix[ i ][ j ] = (elem)strtod(aux,NULL);
        }
    }
    free(aux);
    return m;
}

MATRIX *clone_matrx(const void *const m_)
{
    MATRIX *m=(MATRIX*)m_;
    if(m==NULL)
        return NULL;
    MATRIX *m_clone = new_struct_MATRIX(m->row, m->column);
    for (int i = 0; i < m->row; ++i) {
        for (int j = 0; j < m->column; ++j) {
            (m_clone->matrix)[i][j] = (m->matrix)[i][j];
        }
    }
    return m_clone;
}

MATRIX *create_sistem_matrix_vector(void *m_, void *v_)
{

    const MATRIX *m=(MATRIX*)m_;
    const MATRIX *v=(MATRIX*)v_;
    int i, j;
    if(m->row != v->row || v->column != 1)
    {
        fprintf(stderr,"Errore\n Impossibile creare un sistema matrice|vettore con gli argomenti passati\n");
        return NULL;
    }
    MATRIX *res = new_struct_MATRIX(m->row,m->column+1);
    for (i = 0; i < res->row; ++i)
    {
        for (j = 0; j < m->column; ++j)
        {
            (res->matrix)[i][j] = (m->matrix)[i][j];
        }
        (res->matrix)[i][j] = (v->matrix)[i][0];
    }
    return res;
}

void free_matrix(void* m_)
{
    MATRIX*m=(MATRIX*)m_;
    for (int i = 0; i < m->row; ++i) {
        free(*(m->matrix+i));
    }
    free(m->matrix);
    free(m);
}

/*
 *
 *
 *
 */


void swap_row(void* m_,const int r1,const int r2)
{
    MATRIX*m=(MATRIX*)m_;
    if(r1>m->row || r2>m->row)
    {
        fprintf(stderr,"Illegal operation(Swapping row)\n");
        exit(-1);
    }
    elem *tmp;
    if(r1==r2)
        return;
    tmp=*(m->matrix+r1);
    *(m->matrix+r1)=*(m->matrix+r2);
    *(m->matrix+r2)=tmp;
}

MATRIX *matrix_multiplication(const void *const m1_, const void *const m2_)
{
    const MATRIX *m1=(MATRIX*)m1_;
    const MATRIX *m2=(MATRIX*)m2_;
    if(m1->column != m2->row)
    {
        fprintf(stderr,"Illegal operation(Matrix Moltiplication)\n");
        exit(-1);
    }
    MATRIX *result = (MATRIX *)malloc( sizeof( MATRIX ) );
    result->row = m1->row;
    result->column = m2->column;
    result->matrix = new_matrix(result->row,result->column);
    for(int m = 0; m < m1->row; m++ ) {
        for(int i = 0; i < m2->column; i++ ) {
            for(int j = 0; j < m2->row; j++ ) {
                (result->matrix)[ m ][ i ] += ( m1->matrix )[ m ][ j ] *
                                              ( m2->matrix )[ j ][ i ];
            }
        }
    }
    return result;
}

MATRIX *gauss_elimination(void *m_)
{
    MATRIX *m=clone_matrx(m_);
    if(m==NULL)
        return NULL;
    for (int i=0; i<m->row; i++)
    {
        elem** matrix = m->matrix;
        if(matrix[i][i]==0)
        {
            int row_to_swap=-1;
            for (int j = i; j < m->column; ++j)
            {
                if(matrix[i][j]!=0)
                {
                    row_to_swap = j;
                    break;
                }
            }
            if(row_to_swap<0)
            {
                fprintf(stderr,"Fottuto");
                return NULL;
            }
            swap_row(m, i, row_to_swap);
        }
        for (int k=i+1; k<m->row; k++) {
            elem c = -matrix[k][i]/matrix[i][i];
            for (int j=i; j<m->row+1; j++) {
                if (i==j) {
                    matrix[k][j] = 0;
                } else {
                    matrix[k][j] += c * matrix[i][j];
                }
            }
        }
    }
    return m;
}

/*
 *
 *
 *
 */

void print_matrice(const void *const m_)
{
    MATRIX*m=(MATRIX*)m_;
    int i, j;

    printf("\nThe matrix is:\n\n");
    for( i = 0; i < m->row; i++ ) {
        for( j = 0; j < m->column; j++ ) {
            printf( "%.4f ", (m->matrix)[ i ][ j ] );
        }
        printf("\n");
    }

}

void print_matrix_vertex(const void *const m_, const void *const v_)
{
    MATRIX*m=(MATRIX*)m_;
    MATRIX*v=(MATRIX*)v_;
    if(v->column!=1) {
        fprintf(stderr, "ERROR:\nThe 2nd matrix passed by argument is not a vector\n");
        exit(-1);
    }
    if(m->row != v->row) {
        fprintf(stderr, "ERROR:\nThe two matrices are not compatible\n");
        exit(-1);
    }
    printf("\nThe matrix A |b are:\n\n");
    int i, j;
    for( i = 0; i < m->row; i++ ) {
        for( j = 0; j < m->column; j++ ) {
            printf( "%.5f ", (m->matrix)[ i ][ j ] );
        }
        printf("\t| %.5f\n", (v->matrix)[i][0]);
    }
}




