#include<stdio.h>

int exchange(int *x,int *y)
{
	int *temp;

	temp=*x;
	*x=*y;
	*y=temp;
}

int main()
{
	int cheoli=10,metel=20;

	printf("바꾸기전 %d %d\r\n",cheoli,metel);
	exchange(&cheoli,&metel);
	printf("바꾼후 %d %d\r\n",cheoli,metel);

	return 0;
}
