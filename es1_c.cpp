#include <stdio.h>
#include <stdlib.h>
int Vassoluto(int n);

int main()
{
	const int N=62;
	int T[N][N];
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
			printf("%d\t",T[i][j]);
		}
		printf("\n");
	}
	int s,s1,n=0; //s-> sommatoria  //n -> norma infinito
	for(int i=0;i<N;i++)
	{
		s=0,s1=0;
		for(int j=0;j<N;j++)
		{
			if(T[i][j]<0)
				T[i][j]=-T[i][j];
			s+=T[i][j];
		}
		if(s>n)
			n=s;
	}
	printf("la norma infinito di T e':%d\n",n);
	return 0;
}

int Vassoluto(int n)
{
	if(n<0)
		n=-n;
	return n;
}