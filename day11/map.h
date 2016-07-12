#ifndef __MAP_H__
#define __MAP_H__

typedef struct{
	int m_nSkima;
	int m_nWidth;
	int m_nHeight;

}_S_MAP_HEADER;

typedef struct{
	_S_MAP_HEADER m_header;
	char *m_pBuf;

}_S_MAP_OBJECT;

void map_dump(_S_MAP_OBJECT *pObj,char *pTile_pal);
void map_new(_S_MAP_OBJECT *pObj,int nWidth,int nHeight);
void map_PutTile(_S_MAP_OBJECT *pObj,int x,int y,int nTileIndex);
int map_save(_S_MAP_OBJECT *pObj,char *filename);
int map_load(_S_MAP_OBJECT *pObj,char *filename);

#endif
