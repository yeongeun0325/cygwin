#include<stdio.h>

int reverse(char *arr,int size)
{
	int i,temp;
	for(i=0;i<size/2;i++){
		temp=arr[i];
		arr[i]=arr[size-1-i];
		arr[size-1-i]=temp;
	}
}

int main()
{
	char arr[]={1,2,3,4,5};
	
	int size=sizeof(arr)/sizeof(char);

	for(int i=0;i<size;i++){
		printf("%d ",arr[i]);
	}
	puts("");

/*	for(int i=5;i>0;i--){
		printf("%d ",arr[i]);
	}
	puts("");

	for(int i=0;i<5/2;i++){
		int temp=arr[i];
		arr[i]=arr[5-1-i];
		arr[5-1-i]=temp;
	}
*/	
	reverse(arr,size);

	for(int i=0;i<5;i++){
		printf("%d ",arr[i]);
	}
	
	
	return 0;
}
