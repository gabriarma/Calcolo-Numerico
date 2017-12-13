void createMatrix_x2(const char* fileName, int row);

void esercizio3(void* source_A,void* source_b)
{
//risolvere sistema lineare Ax~=b+∂b
//∂b=||b||∞ * (-0.01,0.01,-0.01,...,0.01)^t
	
//creo vettore b trasposto
createMatrix_x2(tmpFile, source_b->row);
FILE* f= fopen(tmpFile,"r");
MATRIX *b_=create_matrix(f);
fclose(f);

//calcolo norma vettore b
int s=0;
MATRIX b_norma_t=clone_matrx(source_b);
for(int i=0; i<source->row;i++)
{
	if(((b_norma_t->matrix)[i][0])<0)
		((b_norma_t->matrix)[i][0])=-((b_norma_t->matrix)[i][0]);
	if((b_norma_t->matrix)[i][0]>s)
		s=(b_norma_t->matrix)[i][0];
}
//calcolo vettore delta b
MATRIX delta_b=clone_matrx(source_b);
for(int i=0;i<delta_b->row;i++)
{
	(delta_b->matrix)[i][0]=s* (b_->matrix)[i][0];
}

//creo vettore b+∂b
MATRIX *b=clone_matrx(delta_b);
for(int i=0;i<delta_b->row;i++)
{
	(b->matrix)[i][0]=(b->matrix)[i][0] + (delta_b->matrix)[i][0];
}

//soluzione Ax~=b+∂b
MATRIX *x_=sost_indietro(source_A,b);
//soluzione Ax=b
MATRIX *x=sost_indietrto(source_A,source_b);
}

void createMatrix_x2(const char* fileName, int row)
{
	FILE* matrixFile = fopen(fileName, "w");
	if (!matrixFile)
		fail_errno("Error creating file");
	fprintf(matrixFile, "%d %d\n", row, 1);

	for (int i = 0; i < row; i=i+2)
	{
		fprintf(matrixFile, " -0.01");
		fprintf(matrixFile, " 0.01");
	}
	fclose(matrixFile);
}