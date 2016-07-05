#include<stdio.h>
#include<string.h>

int main()
{
	char *pStrCmd="move position 123,56";
	char *ptr=strstr(pStrCmd,"position");

	printf("%s\r\n",ptr);

	char pStrTemp[128];

	strncpy(pStrTemp,pStrCmd,4);	//몇번째까지 복사	
	printf("%s\r\n",pStrTemp);

	char *pStrClone;
	
	pStrClone=strdup(pStrCmd);	//메모리할당해줌
	pStrClone[0]='a';

	//pStrClone=pStrCmd;
	//pStrCmd[1]='n';
	printf("%s\r\n",pStrClone);
	printf("%s\r\n",pStrCmd);


	return 0;
}
