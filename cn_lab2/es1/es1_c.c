#include <stdio.h>
#include <stdlib.h>
#include "MyMatrix.h"

int Vassoluto(int n);

int es1_c(const char *const fileName)
{
	FILE* matrixFile = fopen(fileName, "w");
	if (!matrixFile)
		fail_errno("Error creating file");
	int d0 = 2, d1 = 5;
	const int N = (10 * (d1 + 1)) + d0;
	int T[N][N];
	fprintf(matrixFile, "%d %d\n", N, N);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==j)
				T[i][j]=2;
			else if(Vassoluto(i-j)==1)
				T[i][j]=-1;
			else 
				T[i][j]=0;
			printf("%d ",T[i][j]);
			fprintf(matrixFile, "%d ", T[i][j]);
		}
		printf("\n");
		fprintf(matrixFile,"\n");
	}
	int s,n=0; //s-> sommatoria  //n -> norma infinito
	for(int i=0;i<N;i++)
	{
		s=0;
		for(int j=0;j<N;j++)
		{
			if(T[i][j]<0)
				T[i][j]=-T[i][j];
			s+=T[i][j];
		}
		if(s>n)
			n=s;
	}
	printf("la norma infinito di T e':%d\n", n);
	fprintf(matrixFile, "la norma infinito di T e':%d\n", n);
	fclose(matrixFile);
	return 0;
}

int Vassoluto(int n)
{
	if(n<0)
		n=-n;
	return n;
}