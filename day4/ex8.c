#include<stdio.h>

int main()
{
	int num1=2016;
	int num2=num1;
	int *ptrTemp=&num1;

	printf("num1=%d *ptrTemp=%d\r\n",num1,*ptrTemp);

	*ptrTemp=2015;
	
	printf("num1=%d *ptrTemp=%d num2=%d\r\n",num1,*ptrTemp,num2);

return 0;
}
