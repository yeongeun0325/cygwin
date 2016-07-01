#include<stdio.h>

int testAr[5]={100,101,102,103,104};
char testAr2[5]={100,101,102,103,104};
int main()
{
	printf("testAr[1]=%d\r\n",testAr[1]);

	//배열의 처음 시작번지를 가져옴
	int *pTemp=testAr;
	printf("pTemp[1]=%d\r\n",pTemp[1]);
	printf("pTemp[2]=%d\r\n",pTemp[2]);
	printf("ptemp=%d pTemp+1=%d pTemp+2=%d\r\n",pTemp,pTemp+1,pTemp+2);	//물리메모리주소
	printf("*ptemp=%d *(pTemp+1)=%d *(pTemp+2)=%d\r\n",*pTemp,*(pTemp+1),*(pTemp+2));

	char *pTemp2=testAr2;
	printf("ptemp2=%d pTemp2+1=%d pTemp2+2=%d\r\n",pTemp2,pTemp2+1,pTemp2+2);	//물리메모리주소
	printf("*ptemp2=%d *(pTemp2+1)=%d *(pTemp2+2)=%d\r\n",*pTemp2,*(pTemp2+1),*(pTemp2+2));


	return 0;
}
