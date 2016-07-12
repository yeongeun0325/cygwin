#include<stdio.h>
#include<stdlib.h>


#include "map.h"

void map_dump(_S_MAP_OBJECT *pObj,char *pTile_pal)
{
	/*putTitle(0,pObj->m_header.m_nHeight,
			0,pObj->m_header.m_nWidth,
			pObj->m_header.m_nWidth,pObj->m_pBuf,pTile_pal);
	*/
	for(int iy=0;iy<pObj->m_header.m_nHeight;iy++){
		for(int ix=0;ix<pObj->m_header.m_nWidth;ix++){
			putchar(pTile_pal[pObj->m_pBuf[iy*pObj->m_header.m_nHeight+ix]]);
		}
		printf("\r\n");
	}
}

void map_new(_S_MAP_OBJECT *pObj,int nWidth,int nHeight)
{
	int nSize=nWidth*nHeight;
	if(pObj->m_pBuf!=NULL){
		free(pObj->m_pBuf);
	}
	pObj->m_header.m_nWidth=nWidth;//atoi(strtok(NULL," "));
	pObj->m_header.m_nHeight=nHeight;//atoi(strtok(NULL," "));
	pObj->m_pBuf=malloc(nSize);
	
	for(int i=0;i<nSize;i++){
		pObj->m_pBuf[i]=0;
	}
}

void map_PutTile(_S_MAP_OBJECT *pObj,int x,int y,int nTileIndex)
{
	pObj->m_pBuf[pObj->m_header.m_nWidth*y+x]=nTileIndex;
}

//0:성공 1:실패
int map_save(_S_MAP_OBJECT *pObj,char *filename)
{
	FILE *pFile=fopen(filename,"wb");
	fwrite(&(pObj->m_header),sizeof(pObj->m_header),1,pFile);

	int nSize=pObj->m_header.m_nWidth*pObj->m_header.m_nHeight;
	fwrite(pObj->m_pBuf,nSize,1,pFile);

	fclose(pFile);
	
	return 0;
}

int map_load(_S_MAP_OBJECT *pObj,char *filename)
{
	FILE *pFile=fopen(filename,"rb");

	fread(&(pObj->m_header),sizeof(pObj->m_header),1,pFile);

	if(pObj->m_pBuf){
		free(pObj->m_pBuf);
	}

	int nSize=pObj->m_header.m_nWidth*pObj->m_header.m_nHeight;	
	pObj->m_pBuf=malloc(nSize);
	fread(pObj->m_pBuf,nSize,1,pFile);

	fclose(pFile);
	
	return 0;
}

