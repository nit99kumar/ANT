#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

float** allocate(int x,int y)
{ 
int i;
float **c=(float **)malloc(x*sizeof(float*));
for( i=0;i<x;i++)
{ c[i] = (float *)malloc(y*sizeof(float));
}
return c;
}
float* thomas(float **mat,int n)
{
float *X=(float *)malloc(n*sizeof(float));
int i;
//Thomas algorithm
for ( i = 1; i < n; i++)
{
float m = mat[i][0]/mat[i-1][1];
mat[i][1] = mat[i][1] - m * mat[i - 1][2];
mat[i][3] = mat[i][3] - m*mat[i-1][3];
}
//Back substitution
X[n-1] = mat[n-1][3]/mat[n-1][1];
for ( i = n - 2; i >= 0; i--)
X[i] = (mat[i][3] - mat[i][2] * X[i+1]) / mat[i][1];
/* printf("For step size h = %.4f \n",step);
for(i=0;i<n;i++)
{
printf("y(%.2f) = %f \n",(i+1)*step,mat[i][4]);
}
printf("\n");*/
float *Xn=(float *)malloc(n+2*sizeof(float));
Xn[0]=0;
Xn[n+1]=0;
for(i=0;i<n;i++)
{ Xn[i+1]=X[i];
}
return Xn;
}
int main()
{
int i,n;
printf("Enter the number of points \n");
scanf("%d",&n);
printf("Start entering the points in the format x_i : y _i \n");
float **p =allocate(n,2);
for(i=0;i<n;i++)
scanf("%f %f",&p[i][0],&p[i][1]);
float **mat = allocate(n-2,4);
float *h = (float *)malloc(n-1*sizeof(float));
for(i=0;i<n-1;i++)
h[i]=p[i+1][0]-p[i][0];
float *yk = (float *)malloc(n-1*sizeof(float));
for(i=0;i<n-1;i++)
yk[i]=p[i+1][1]-p[i][1];
mat[0][1]=2*(h[0]+h[1]);
mat[0][2]=h[1];
mat[0][3]=6*( yk[1]/h[1] - yk[0]/h[0]);
mat[n-3][0]=h[n-3];
mat[n-3][1]=2*(h[n-2]+h[n-3]);
mat[n-3][3]=6*( yk[n-2]/h[n-2] - yk[n-3]/h[n-3]);
for(i=1;i<n-3;i++)
{
mat[i][0]=h[i];
mat[i][1]=2*(h[i]+h[i+1]);
mat[i][2]=h[i+1];
mat[i][3]=6*( yk[i+1]/h[i+1] - yk[i]/h[i]);
}
float *X = thomas(mat,n-2);
//computing intermediate values
for(i=0;i<n-1;i++)
{
int j;
for(j=0;j<10;j++)
{
float x = p[i][0]+(j+1)*(p[i+1][0]-p[i][0])/10;
float a= p[i+1][0]-x;
float b = x-p[i][0];
float val = X[i]/6*(((a*a*a)/h[i]) - h[i]*a)
+yk[i]*a/h[i]
+X[i+1]/6*((b/h[i])-h[i]*b)
+yk[i+1]/h[i+1]*b;
printf("%f %f\n",x,val);
}
printf("\n");
}
return 0;
}
