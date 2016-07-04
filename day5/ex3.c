#include<stdio.h>

int main()
{
	int a;
	int *ap=&a;
	//int *ap; ap=&a;
	
	printf("ap에 저장된 값:%u\r\n",ap);	
	printf("ap자체의 주소값:%u\r\n",&ap);

	a=100;
	printf("%d %d\r\n",*ap,*(int *)4294953996);

	//(int *)4294953996=주소값
	*((int *)4294953996)=200;
	printf("%d\r\n",a);

	return 0;
}
