#include<stdio.h>

int main()
{
	int test=0x0000001;
	test=test<<1;	//0001->0010
	printf("%x \r\n",test);

	test=test<<1;	//0010->0100
	printf("%x \r\n",test);

	test=test<<1;	//0100->1000
	printf("%x \r\n",test);

	return 0;
}
