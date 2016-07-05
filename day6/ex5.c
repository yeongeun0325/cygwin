#include<stdio.h>
#include<string.h>

int main()
{
	char *pStr="hello world";
	char strTemp[128];

	strcpy(strTemp,pStr);
	
	strTemp[0]='R';

	printf("원본 %s\r\n",pStr);	
	printf("%s을 복사했습니다.\r\n",strTemp);

	printf("문자열의 길이는 %d\r\n",strlen(strTemp));

	int cmp=strcmp("hello world","aello world");
	printf("%d\r\n",cmp);

	char *pStr2=",hi world";

	strcat(strTemp,pStr2);
	printf("%s\r\n",strTemp);

	return 0;
}
