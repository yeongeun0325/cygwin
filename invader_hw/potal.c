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


void Potal_Draw(_S_Potal *pObj, _S_MAP_OBJECT *pBuff)
{
	switch(pObj->m_nFSM) {
	case 0:
		break;
	case 1:
		map_drawTile_trn(pObj->m_pBody,
			(int)(pObj->m_fXpos + pObj->m_fCenterX) ,
			(int)(pObj->m_fYpos + pObj->m_fCenterY),
			pBuff);

		break;
	}
	//map_drawTile_trn(pObj->m_pBody,pObj->m_nXpos,pObj->m_nYpos,pBuff);
}

void Potal_Apply(_S_Potal *pObj,double deltaTick)
{
	switch(pObj->m_nFSM) {
		case 0:
			break;
		case 1:
			break;
	}
}


void Potal_init(_S_Potal *pObj,_S_MAP_OBJECT *pBody,int x,int y)
{
	pObj->m_pBody = pBody;
	pObj->m_fYpos = y;
	pObj->m_fXpos = x;

	pObj->pfDraw=Potal_Draw;
}
