#include<stdio.h>

int main()
{
	char str[80]="dream";
	
	printf("%s\r\n",str);
	
	int nCount=0;
	while(str[++nCount]!=0){	//nCount++ 루프를 빠져나가기전에 더해줌
		
	}
	printf("%d\r\n",nCount);

	return 0;
}
