#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	printf("count %d\r\n",argc);

	for(int i=0;i<argc;i++){
		puts(argv[i]);
	}
	
	return 0;
}
