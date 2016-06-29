#include<stdio.h>

int main()
{
	printf("hello\r\n");
	printf("\x1b[31m");
	printf("hello\r\n");

	printf("\x1b[1;31m");
	printf("hello\r\n");

	printf("\x1b[33m");
	printf("hello\r\n");

	printf("\x1b[4;32m");
	printf("hello\r\n");
	
	printf("\x1b[0;36m");
	printf("hello\r\n");

	printf("\x1b[2;36m");
	printf("hello\r\n");

	printf("\x1b[0m");
	printf("\x1b[1;34m");
	printf("hello\r\n");	
	
	printf("\x1b[0;34m");
	printf("hello\r\n");	
		
	printf("\x1b[0;35m");
	printf("hello\r\n");	
	return 0;
}
