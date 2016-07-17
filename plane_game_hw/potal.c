#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"

#include "potal.h"


void Potal_init(_S_Potal *pObj,_S_MAP_OBJECT *pBody,int x,int y)
{
	pObj->m_pBody = pBody;
	pObj->m_nYpos = y;
	pObj->m_nXpos = x;

	pObj->fpDraw=Potal_Draw;
}

void Potal_Draw(_S_Potal *pObj, _S_MAP_OBJECT *pBuff)
{
	map_drawTile_trn(pObj->m_pBody,pObj->m_nXpos,pObj->m_nYpos,pBuff);
}
