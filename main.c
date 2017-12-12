#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "MyMatrix.h"

const char* const A1="4 4\n 3 1 -1 0\n 0 7 -3 0\n 0 -3 9 -2\n 0 0 4 -10";  //Prima matrice dell'esercizio 1
const char* const A2="4 4\n 2 4 -2 0\n 1 3 0 1\n 3 -1 1 2\n 0 -1 2 1";     //Seconda matrice dell'esercizio 1
const char* fileNameA1 = "matrixA1.txt";
const char* fileNameA2 = "matrixA2.txt";





void fail_errno(const char* );
void test();
void createFile_fromString(char *,const char *const );

int main( int argc, char **argv )
{
    test();
    return (EXIT_SUCCESS);
}


































void test() /*test delle funzioni delle matrici*/
{
    char **fileNames;       //array di stringhe contenente i nomi dei file dove sono salvate le matrici/vatori
    int numFile = 4;
    fileNames = (char**)calloc(sizeof(char*),(size_t)numFile);
    for (int i = 0; i < numFile; ++i) {
        *(fileNames+i)=(char*)calloc(sizeof(char),(size_t)32);
    }
    //assegnazione dei nomi dei file e creazione dei file
    fileNames[0]="A_matrix.txt";    createFile_fromString(fileNames[0],myMatrix);
    fileNames[1]="b_vector.txt";    createFile_fromString(fileNames[1],myVector);
    fileNames[2]="matrix1.txt";     createFile_fromString(fileNames[2],A1);
    fileNames[3]="matrix2.txt";     createFile_fromString(fileNames[3],A2);

    FILE* A_matrixFile = fopen(fileNames[0],"r");
    FILE* b_vectorFile = fopen(fileNames[1],"r");
    FILE* matrx1File = fopen(fileNames[2],"r");
    FILE* matrx2File = fopen(fileNames[3],"r");
    /*for (int j = 0; j < numFile; ++j) {
        printf("%s\n", *(fileNames+j));
        free(*(fileNames+j));
    }*/
    free(fileNames);
    //creazione dele matrci a partire dai file
    MATRIX *A = create_matrix( A_matrixFile ),
            *b = create_matrix( b_vectorFile ),
            *m1 = create_matrix(matrx1File),
            *m2 = create_matrix(matrx2File);
    //chiusura dei file
    fclose(A_matrixFile);
    fclose(b_vectorFile);
    fclose(matrx1File);
    fclose(matrx2File);
    //test sulle varie unzione sulle matrici
    printf("\n\nStampa matrice A|b\n\n");
    print_matrix_vertex(A,b);
    //swap_row(A,0,1);
    printf("\n\nStampa matrice A con la riga 1 scambiata con la riga 2\n\n");
    print_matrice(A);
    printf("\n\nStampa matrice m1");
    print_matrice(m1);
    printf("\n\nStampa matrice m2");
    print_matrice(m2);
    MATRIX *res = matrix_multiplication(m1,m2);
    printf("\n\nstampa matrice m1*m2");
    print_matrice(res);
    MATRIX *res2 = create_sistem_matrix_vector(A,b);
    print_matrice(res2);
    MATRIX *res2_gauss = gauss_elimination(res2);
    print_matrice(res2_gauss);

    //free all memory used
    free_matrix(A);
    free_matrix(b);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(res);
    free_matrix(res2);
    //free_2d_Arrey((void **)fileNames, numFile);
}

void createFile(char **argv)
{
    char* const name_matrixFile = "matrixFile.txt";
    char* const name_vectorFile = "vectorFile.txt";
    FILE* matrixFile = fopen(name_matrixFile,"w");
    FILE* vectorFile = fopen(name_vectorFile,"w");
    if(!matrixFile || !vectorFile)
        fail_errno("Error creating file");
    fprintf(matrixFile,"%s",myMatrix);
    fprintf(vectorFile,"%s",myVector);
    fclose(matrixFile);
    fclose(vectorFile);
    argv[1]=name_matrixFile;
    argv[2]=name_vectorFile;
}

void createFile_fromString(char *fileName,const char *const strMatrix)
{
    char* const name_matrixFile = fileName;
    FILE* matrixFile = fopen(name_matrixFile,"w");
    if(!matrixFile)
        fail_errno("Error creating file");
    fprintf(matrixFile,"%s", strMatrix);
    fclose(matrixFile);
}

void fail_errno(const char* c)
{
    perror(c);
    exit(EXIT_FAILURE);
}
