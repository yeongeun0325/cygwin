#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	//char ptr[]=" move position 30,20";
	char *ptr=strdup("move position 30,20");
	char *ptrTemp;

	ptrTemp=strtok(ptr," ");	//공백문자를 만나면 잘라냄
	
	printf("%s\r\n",ptrTemp);
	printf("%s\r\n",strtok(NULL," "));

	ptrTemp=strtok(NULL,",");
	printf("%d\r\n",atoi(ptrTemp)+1);

	ptrTemp=strtok(NULL,",");
	printf("%d\r\n",atoi(ptrTemp)+1);
	//printf("%s\r\n",strtok(NULL," "));

	return 0;
}
