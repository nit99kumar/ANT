#include <stdio.h>
#include <stdlib.h>

//displaying a 2-d matrix
void display(float **A, int n)
{
	int i, j;
	printf("\n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
			printf("%0.2f ",A[i][j]);
		printf("\ni=%d\n",i);
	}
	printf("\n");
}

void thomas(float **A, float *D, int n, float h)
{
	int i, j;
	float *X, c_new, d_new;
	X = (float *)malloc(n * sizeof(float));
	for(i=0; i<n; i++)
	{
		if(i==0)
		{
			c_new = A[i][i+1] / A[i][i]; //c1' = c1/b1;
			d_new = D[i] / A[i][i]; //d1' = d1/b1;
			A[i][i] = 1;
			A[i][i+1] = c_new;
			D[i] = d_new;
		}
		if(i>0 && i<n-1)
		{
			c_new = A[i][i+1] / (A[i][i] - (A[i][i-1] * A[i-1][i]));
			d_new = (D[i] - (A[i][i-1] * D[i-1])) / (A[i][i] - (A[i][i-1] * A[i-1][i]));
			A[i][i-1] = 0;
			A[i][i] = 1;
			A[i][i+1] = c_new;
			D[i] = d_new;
		}
		if(i==(n-1))
		{
			d_new = (D[i] - (A[i][i-1] * D[i-1])) / (A[i][i] - (A[i][i-1] * A[i-1][i]));
			A[i][i-1] = 0;
			A[i][i] = 1;
			D[i] = d_new;
		}
	}
	//calculating delta(Y)
	X[n-1] = D[n-1];
	for(i=n-2; i>=0; i--)
		X[i] = D[i] - A[i][i+1] * X[i+1];
	
	for(i=0; i<n; i++)
		printf("%f\n", X[i]);
}

int main()
{
	float h;
	int n, i, j;
	scanf("%d", &n);
	h = (1/(n+1));
	float **A = (float **)calloc(n, sizeof(float *));
	float *D = (float *)malloc(n * sizeof(float));
	for(i=0; i<n; i++)
	{
		A[i] = (float *)calloc(n, sizeof(float));
		for(j=0; j<n; j++)
			scanf("%f",&A[i][j]);
	}
	for(i=0; i<n; i++)
		scanf("%f", &D[i]);
	display(A,n);
	thomas(A, D, n, h);
	return 0;
}