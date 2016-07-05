#include<stdio.h>

int main()
{
	int ary[5]={1,2,3,4,5};
	int ary2[5];
	int *pAry;

	pAry=ary;	//o

	printf("%d %d\r\n",pAry[1],*(ary+1));
	//ary2=ary;	//x read only



	return 0;
}
