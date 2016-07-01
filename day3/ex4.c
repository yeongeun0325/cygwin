#include <stdio.h>
#include <stdlib.h>
#include "../hwork.h"

int main()
{
	system("clear");
	
	int i=0;
	int j=1;

	while(i<10){
		gotoxy(5,i);
		printf("+");
		gotoxy(i,5);
		printf("+");
		i++;
	}

	while(j<11){
		gotoxy(j,11+j);
		printf("x");
		gotoxy(11-j,11+j);
		printf("x");
		j++;
}
	gotoxy(0,30);
	printf("====================\r\n");

	return 0;
}
