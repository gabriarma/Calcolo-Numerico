#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyMatrix.h"

int factorial(int n);

int es1_b(const char *const fileName)
{
	FILE* matrixFile = fopen(fileName, "w");
	if (!matrixFile)
		fail_errno("Error creating file");
	long N=0,D1=0,D2=0,P=0,n=10;
	long norma=0,s=0; //s->sommatoria
	fprintf(matrixFile, "%d %d\n",(int) n, (int)n);
	for(int i=1;i<=n;i++)
	{
		s=0;
		for(int j=1;j<=n;j++)
		{
			N=factorial(i+j-2);
			D1=factorial(i-1);
			D2=factorial(j-1);
			P=N/(D1*D2);
			s+=P;
			printf("%ld ",P);
			fprintf(matrixFile, "%ld ", P);
		}
		fprintf(matrixFile, "\n");
		printf("\n");
		if(s>norma)
			norma=s;
	}
	printf("La norma infinito della matrice P e' %ld\n",norma);
	fprintf(matrixFile, "\nLa norma infinito della matrice P e' %ld\n", norma);
	fclose(matrixFile);
	return 0;
}

int factorial(int n)
{
	if(n>1)
		return n* factorial(n-1);
	else
		return 1;
}

