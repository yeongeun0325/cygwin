#include<stdio.h>

int main()
{
	double a=1.3;
	double b=1.7;
	double temp;
	double *pa,*pb;

	printf("바꾸기전 a:%f b:%f\r\n",a,b);

	pa=&a;
	pb=&b;

	temp=*pa;
	*pa=*pb;
	*pb=temp;

	//temp=a;
	//a=b;
	//b=temp;

	printf("바꾼 후 a:%f b:%f\r\n",a,b);
}
