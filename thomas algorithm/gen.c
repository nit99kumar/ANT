#include <stdio.h>
#include <math.h>

int main()
{
	int n, i, j;
	float h, y0=0, y1=-1, a, b, c, d=0, x=0;

	
	printf("enter the grid size: ");
	scanf("%f",&h);
	n = (1/h)-1;

	a = 1/(h*h);
	b = -400 - (2/(h*h));
	c = a;

	for(i=0; i<n; i++)
	{
		x += h;
		d = -401 * sin(x);
		printf("%0.1f %0.1f %0.1f %0.1f\n",a,b,c,d);
	}
	return 0;
}