#include<stdio.h>
#include<stdlib.h>

#include"map.h"

char title_palette[]={'.','@','#'};

int main()
{
	_S_MAP_OBJECT test_map;
	map_init(&test_map);

	_S_MAP_OBJECT test_map2;
	map_init(&test_map2);

	//test_map.new(8,8);
	map_new(&test_map,8,8);
	map_dump(&test_map,title_palette);

	map_new(&test_map2,4,4);
	map_dump(&test_map2,title_palette);

	return 0;
}
