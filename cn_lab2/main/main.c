#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raccoltaEsercizi.h"
#include "fileNameLis_lib.h"

const char* strA1="4 4 \n3 1 -1 0 \n0 7 -3 0 \n0 -3 9 -2 \n0 0 4 -10\n";  //Prima matrice dell'esercizio 1
const char* strA2="4 4 \n2 4 -2 0 \n1 3 0 1 \n3 -1 1 2 \n0 -1 2 1\n";     //Seconda matrice dell'esercizio 1

const char* direNameList[] = { "../data/A1","../data/A2","../data/B","../data/C" };

void createFile_fromString(const char *,const char *const );

int main()
{
	//ESERCIZIO 1
	char *s;
	printf("\nEsercizio 1:\n");
	printf("\t-punto a:\n");
	es1_a();
	printf("\n\n\t-punto b:\n");
	s = nomeFile(direNameList[2], fileNameMatrice);
	es1_b(s);
	printf("\n\n\t-punto c:\n");
	s = nomeFile(direNameList[3], fileNameMatrice);
	es1_c(s);
	//ESERCIZIO 2
	s = nomeFile(direNameList[0], fileNameMatrice);
	createFile_fromString(s, strA1);
	free(s);
	s = nomeFile(direNameList[1], fileNameMatrice);
	createFile_fromString(s, strA1);
	free(s);
	for (int i = 0; i < 4; i++)
	{
		printf("\n\nES 2 parte %d:\n",i+1);
		esercizio2(direNameList[i]);
		printf("ES 3 parte %d:\n",i+1);
		esercizio3(direNameList[i]);
		puts("************************************************************");
	}
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

