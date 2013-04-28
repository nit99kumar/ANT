#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define epsilon 0.0001

float *thomas(float **, float *, float *, int, float);
void iterate(float **, float *, float *, int, float);
void input(float **, float *, float *, int, float);
void display(float **, int);

//displaying a 2-d matrix
void display(float **A, int n)
{
	int i, j;
	printf("\n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
			printf("%0.2f ",A[i][j]);
	}
	printf("\n");
}

//forming the input
void input(float **A, float *D, float *Y, int n, float h)
{
	int i;
	float x, temp;
	for(i=0; i<n; i++)
	{
		A[i] = (float *)calloc(n, sizeof(float));
		x = h*(i+1);
		temp = (1+x+Y[i+1]);
		A[i][i] = -(2/(h*h)) -(1.5*temp*temp) -0.5;//bi
		if(i==0)
			A[i][i+1] = 1/(h*h);//ci
		else if(i==(n-1))
			A[i][i-1] = 1/(h*h);//ai
		else
		{
			A[i][i-1] = 1/(h*h);//ai
			A[i][i+1] = 1/(h*h);//ci
		}
	}
	for(i=0; i<n; i++)
	{
		x = h*(i+1);
		temp = (1+x+Y[i+1]);
		D[i] = -(1/(h*h))*(Y[i]-2*Y[i+1]+Y[i+2])+(0.5*temp*temp*temp);
		if(i==0)
			D[i] = D[i] - (1/(h*h))*Y[0];
		if(i==(n-1))
			D[i] = D[i] - (1/(h*h))*Y[n+1];
	}
}

float *thomas(float **A, float *D, float *Y, int n, float h)
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
	
	//updating the values of the matrix Y
	for(i=0; i<n; i++)
		Y[i+1] += X[i];

	//updating the input matrix
	input(A, D, Y, n, h);
	return X;
}

void iterate(float **A, float *D, float *Y, int n, float h)
{
	int i, count=0, flag=0;
	float *X;
	do
	{
		X = thomas(A, D, Y, n, h);
		for(i=0; i<n; i++)
		{
			if(fabs(X[i]) < epsilon)
				count++;
		}
		if(count==n)
		{
			flag=1;
			printf("final values Y\n\n");
			for(i=0; i<n+2; i++)
				printf("%5.2f %7f\n", h*i, Y[i]);
			printf("\n");
			//printf("final values delta-Y\n\n");
			//for(i=0; i<n; i++)
			//	printf("%10f\n", X[i]);
			//printf("\n");
		}
	}while(flag==0);
}

int main()
{
	int i,n;
	float **A, *D, *Y, h;//AX = D
	//printf("enter the step size: ");
	//scanf("%f", &h);
	h=0.025;
	n = (1/h)-1;
	A = (float **)calloc(n, sizeof(float *));
	D = (float *)malloc(n * sizeof(float));
	Y = (float *)calloc((n+2), sizeof(float));
	for(i=0; i<n+2; i++)
		Y[i] = h*i*(1-h*i);
	
	input(A, D, Y, n, h);
	iterate(A, D, Y, n, h);
	printf("h = %0.3f\nepsilon = %0.4f", h, epsilon);
	return 0;
}