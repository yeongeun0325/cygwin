#include<stdio.h>

int main()
{
	int num[]={3,6,4,5,7};
	int *pNum=num;
	int max=num[2];
	int min=num[2];
	
	printf("%d %d\r\n",*(pNum+1),num[1]);

	for(int i=0;i<sizeof(num)/sizeof(int);i++){
		printf("%d\r\n",*(pNum+i));
		if(max<*(pNum+i)){
			max=*(pNum+i);	
		}
		else if(min>*(pNum+i)){
			min=*(pNum+i);
			}
	}
	printf("max=%d\r\n",max);
	printf("min=%d\r\n",min);

}
