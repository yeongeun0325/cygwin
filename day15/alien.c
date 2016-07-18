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
#include "alien.h"

static void Apply(_S_ALIEN_OBJECT *pObj,double deltaTick)
{
	switch(pObj->m_nFSM){
		case 0: //dead
			break;
	}
}

static void Draw(_S_ALIEN_OBJECT *pObj, _S_MAP_OBJECT *pBuff)
{
	switch(pObj->m_nFSM){
		case 0:
			break;
		default:
			map_drawTile_trn(pObj->m_pBody,
					(int)(pObj->m_fXpos+pObj->m_fCenterX),
					(int)(pObj->m_fYpos+pObj->m_fCenterY),
					pBuff);
			break;
	}
}


void Alien_init(_S_ALIEN_OBJECT *pObj,_S_MAP_OBJECT *pBody)
{
	pObj->m_nFSM=0;
	pObj->m_nStep=0;
	
	pObj->m_pBody = pBody;
	pObj->m_fYpos = 0;
	pObj->m_fXpos = 0;
	
	pObj->m_fCenterX=0-(pBody->m_header.m_nWidth/2);
	pObj->m_fCenterY=0-(pBody->m_header.m_nHeight/2);


	pObj->pfApply=Apply;
	pObj->pfDraw=Draw;

}
