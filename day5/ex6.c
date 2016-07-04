#include<stdio.h>

int main()
{
	int num[]={3,7,15,6,8,2};
	int sum=0;
	int max=num[0];
	int min=num[0];

	printf("배열의 갯수:%d\r\n",sizeof(num)/sizeof(int));

	for(int i=0;i<sizeof(num)/sizeof(int);i++){
		sum+=num[i];
		if(max<num[i]){
			max=num[i];
		}
		if(min>num[i]){
			min=num[i];
		}
	}
	
	printf("배열 총합:%d\r\n",sum);
	printf("max=%d\r\n",max);
	printf("min=%d\r\n",min);

	return 0;
}
