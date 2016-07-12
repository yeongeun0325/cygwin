#include<stdio.h>
#include<stdlib.h>

#include"../mapEditor/map.h"

int main()
{
	char TilePalette[]={'.','#','@'};
	_S_MAP_OBJECT screenBuffer;
	map_init(&screenBuffer);
	map_new(&screenBuffer,16,16);

	_S_MAP_OBJECT carObj;
	map_init(&carObj);
	map_load(&carObj,"car.dat");

	puts("\r\n==================");
	//map_dump(&carObj,TilePalette);
	
	{
		int ix,iy;
		_S_MAP_OBJECT *pObj=&carObj;
		for(iy=0;iy<pObj->m_header.m_nHeight;iy++){
			for(ix=0;ix<pObj->m_header.m_nWidth;ix++){
				map_PutTile(&screenBuffer,ix+10,iy+10,pObj->m_pBuf[iy*pObj->m_header.m_nWidth+ix]);
			}
		}
		for(iy=0;iy<pObj->m_header.m_nHeight;iy++){
			for(ix=0;ix<pObj->m_header.m_nWidth;ix++){
				map_PutTile(&screenBuffer,iy+3,ix+3,pObj->m_pBuf[iy*pObj->m_header.m_nWidth+ix]);
			}
		}
	}

	map_dump(&screenBuffer,TilePalette);
	

	return 0;
}
