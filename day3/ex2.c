#include<stdio.h>

int main()
{
	int a,b;
	a=2;b=1;

	while(b<=9){
		
		printf("%d * %d = %d\r\n",a,b,a*b);
		b+=2;
	}
	
	return 0;
}
