#include <stdio.h>

int main()
{
	int arr1[4]={1,2,3,4};
	int arr2[4]={11,12,13,14};
	int arr3[4]={21,22,23,24};

	int *ptr_ary[3]={arr1,arr2,arr3};

	printf("%d %d %d\r\n",ptr_ary[0][1],*(ptr_ary[0]+1),*(arr1+1));

	printf("%d %d %d\r\n",ptr_ary[2][2],*(ptr_ary[2]+2),*(arr3+2));

	return 0;
}
