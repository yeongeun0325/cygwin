#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char strCmd[128];
	//scanf("%s",strCmd);
	gets(strCmd);

	puts(strCmd);
	//printf("%s\r\n",strCmd);

	char ch=getchar();
	putchar(ch);
	
	return 0;
}
