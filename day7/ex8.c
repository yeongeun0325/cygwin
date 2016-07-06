#include<stdio.h>

int main()
{
	int arr[5]={10,20,30,40,50};
	void *vp=arr;

	printf("%d\r\n",*((int *)vp+2));
	printf("%d\r\n",arr[2]);
	return 0;
}
