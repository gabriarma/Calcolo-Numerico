#include<stdlib.h>
#include <stdio.h>

int es1_a()
{
	
	int A[16]={3,1,-1,0,0,7,-3,0,0,-3,9,-2,0,0,4,-10};	//matrice A
	int A1[16]={2,4,-2,0,1,3,0,1,3,-1,1,2,0,-1,2,1};	//matrice A1
	int s,s1,n=0,n1=0; //s,s1 -> sommatorie  //n,n1 -> norme 
	for(int i=0;i<16;i=i+4)
	{
		s=0,s1=0;
		for(int j=i;j<=i+3;j++)
		{
			if(A[j]<0)
				A[j]=-A[j];
			s+=A[j];
			if(A1[j]<0)
				A1[j]=-A1[j];
			s1+=A1[j];
		}
		if(s>n)
			n=s;
		if(s1>n1)
			n1=s1;
		//printf("i=%d\t s=%d\t s1=%d\n",i,s,s1);
	}
	printf("la norma infinito di A e':%d\nla norma infinito di A1 e':%d\n",n,n1);
	return 0;
}