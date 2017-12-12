#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raccoltaEsercizi.h"

const char* const strA1="4 4 \n3 1 -1 0 \n0 7 -3 0 \n0 -3 9 -2 \n0 0 4 -10\n";  //Prima matrice dell'esercizio 1
const char* const strA2="4 4 \n2 4 -2 0 \n1 3 0 1 \n3 -1 1 2 \n0 -1 2 1\n";     //Seconda matrice dell'esercizio 1
const char* const fileNameA1 = "matrixA1.txt";
const char* const fileNameA2 = "matrixA2.txt";
const char* const fileNameB = "matrixB.txt";
const char* const fileNameC = "matrixC.txt";
const char* fileNameList[] = { "matrixA1.txt",
								"matrixA2.txt",
								"matrixB.txt",
								"matrixC.txt" };

void createFile_fromString(const char *,const char *const );

int main()
{
	//	ESERCIZIO 1
	//printf("\nEsercizio 1:\n");
	//printf("\t-punto a:\n");
	//es1_a();
	//printf("\n\n\t*ì-punto b:\n");
	//(fileNameList[2]);
	//printf("\n\n\t-punto c:\n");
	//es1_c(fileNameList[3]);
	//ESERCIZIO 2
	createFile_fromString(fileNameList[0], strA1);
	createFile_fromString(fileNameList[1], strA2);
	esercizio2(fileNameA1);
    return (EXIT_SUCCESS);
}


void createFile_fromString(const char *fileName, const char *const strMatrix)
{
	FILE* matrixFile = fopen(fileName, "w");
	if (!matrixFile)
		fail_errno("Error creating file");
	fprintf(matrixFile, "%s", strMatrix);
	fclose(matrixFile);
}