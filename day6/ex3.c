#include<stdio.h>

int main()
{
	char aStr[]="world";	//상수
	char *pStr="hello"; 	//주소에 대한 변수

	printf("%s %s\r\n",aStr,pStr);
	
	pStr=aStr;
	printf("%s \r\n",pStr);

	return 0;
}
