#include<stdio.h>
#include"ex2_2.h"
//void foo();

extern int nCount;
extern int nCount2;

int main()
{
	nCount=10;
	nCount2=11;
	foo();
	foo();
	
	return 0;
}
