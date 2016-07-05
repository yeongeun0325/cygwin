#include<stdio.h>
#include<string.h>

int exit_sum=0;	//전역변수

void test()
{
	static int sum=0;
	sum++;
	printf("sum:%d\r\n",sum);
	exit_sum++;
}

extern int test_num;

int main()
{
	test();
	test();
	
	printf("%d\r\n",exit_sum);
	printf("%d\r\n",test_num);
	//printf("%d\r\n",sum);

	return 0;
}
