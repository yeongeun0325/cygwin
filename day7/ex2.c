#include<stdio.h>

void exchange(char **ap,char **bp)
{
	char *tp;

	tp=*ap;
	*ap=*bp;
	*bp=tp;
}

int main()
{
	int val=10;
	int *ip;
	ip=&val;

	char *ap="success";
	char *bp="failure";
	//char *tp;

	printf("ap:%s bp:%s\r\n",ap,bp);

	exchange(&ap,&bp);

/*	tp=ap;
	ap=bp;
	bp=tp;
*/
	printf("ap:%s bp:%s\r\n",ap,bp);
}
