#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(){
	int i,n;
	float x1,*x,*f,*e,*d,*h,*r,*z,y,df,dx,xs;
	FILE *fp,*fi;
	fp=fopen("out.txt","w");
	fi=fopen("in.txt","r");
	printf("Enter no. of points: ");
	fscanf(fi,"%d",&n);
	x=(float *)malloc(n*sizeof(float));
	f=(float *)malloc(n*sizeof(float));
	e=(float *)malloc(n*sizeof(float));
	d=(float *)malloc(n*sizeof(float));
	h=(float *)malloc(n*sizeof(float));
	r=(float *)malloc(n*sizeof(float));
	z=(float *)malloc(n*sizeof(float));
	for(i=0;i<n;i++){
		printf("x%d y%d : ",i+1,i+1);
		fscanf(fi,"%f %f",&x[i],&f[i]);
	}
	for(i=0;i<n-2;i++) e[i]=2.0*(x[i+2]-x[i]);
	for(i=0;i<n-2;i++) h[i]=x[i+2]-x[i+1];
	for(i=0;i<n-1;i++) d[i]=x[i+1]-x[i];
	for(i=0;i<n-2;i++) r[i]=6*((f[i+2]-f[i+1])/h[i]-(f[i+1]-f[i])/d[i]);
	for(i=0;i<n-3;i++){
		df=d[i]/e[i];
		e[i+1]=e[i+1]-df*h[i];
		r[i+1]=r[i+1]-df*r[i];
	}
	for(i=n-4;i<=0;i--){
		df=h[i]/e[i+1];
		r[i+1]=r[i]-r[i+1]*df;
	}
	for(i=0;i<n-2;i++){
		z[i+1]=r[i]/e[i];
	}
	z[0]=0;
	z[n-1]=0;
	for(i=0;i<n-1;i++){
		dx=(x[i+1]-x[i])/5.0;
		for(x1=x[i];x1<x[i+1];x1+=dx){
			y=-z[i]*pow((x1-x[i+1]),3)/(6.0*d[i])+z[i+1]*pow((x1-x[i]),3)/(6.0*d[i])+(f[i+1]/d[i]-z[i+1]*d[i]/6.0)*(x1-x[i])+(-f[i]/d[i]+z[i]*d[i]/6.0)*(x1-x[i+1]);
			fprintf(fp,"%f,%f\n",x1,y);
		}
		printf("Polynomial %d: %.2f*(X-%.2f)^3 + %.2f*(X-%.2f)^3 + %.2f(X-%.2f) + %.2f(X-%.2f)\n",i+1,z[i]/(6.0*d[i]),x[i+1],z[i+1]/(6.0*d[i]),x[i],(f[i+1]/d[i]-z[i+1]*d[i]/6.0),x[i],(-f[i]/d[i]+z[i]*d[i]/6.0),x[i+1]);
	}
	fclose(fp);
}