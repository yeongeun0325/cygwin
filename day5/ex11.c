#include<stdio.h>

int main()
{
	char str1[]="hello world";
	char str2[80];

	printf("%s\r\n",str1);
	
	int i;
	for(i=0;str1[i]!=0x00;i++){
		str2[i]=str1[i];
	
	}
	str2[i]=0x00;
	printf("%s\r\n",str2);

	return 0;
}
