#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char cmd[]="add 100,30";
	char *cmdTemp;
	int a,b;

	
	cmdTemp=strtok(cmd," ");

	a=atoi(strtok(NULL,","));
	b=atoi(strtok(NULL,","));

	printf("질문에 대한 결과는 %d\r\n",a+b);
	
	return 0;
}
