#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"map.h"

char title_palette[]={'.','#','@'};

int main()
{
	_S_MAP_OBJECT test;
	map_init(&test);
	map_load(&test,"car.dat");
	puts("-------load complete---------");
	map_dump(&test,title_palette);

	return 0;
}
