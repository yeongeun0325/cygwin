#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int bLoop=1;

void apply(char *);

int main()
{
	puts("mydeitor v.1.0");

	while(bLoop)
	{
		char strCmd[128];
		gets(strCmd);

		char *pTemp = strtok(strCmd," ");

		if(!strcmp(pTemp,"exit")) {
			bLoop=0;
		}
		else{
			apply(pTemp);
		}
	}

	return 0;
}
