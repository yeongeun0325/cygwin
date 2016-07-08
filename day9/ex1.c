#include<stdio.h>

//#define pi 3.14
const double pi=3.14;	//변수

int main()
{
	
	double pi=1.14;

	int a=10,b=20;
	const int *ap;
	
	ap=&a;
	ap=&b;

	//*ap=21;
	b=21;

	
	//pi=2.14;
	//_pi=2.14;

	printf("%f %d\r\n",pi,*ap);

	return 0;
}
