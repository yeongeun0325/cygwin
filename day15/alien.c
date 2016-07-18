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
	double speed=10.0;
	switch(pObj->m_nFSM){
		case 0: //dead
			pObj->m_nFSM=1;
			break;
		case 1:	//ready
			pObj->m_nFSM=2;
			break;
		case 2:	//move right
			pObj->m_fXpos+=(deltaTick*speed);
			if(pObj->m_fXpos>=35){
				pObj->m_fYpos+=3;
				pObj->m_nFSM=3;
				pObj->m_nStep=0;
			}
			break;
		case 3:	//move left
			pObj->m_fXpos-=(deltaTick*speed);
			if(pObj->m_fXpos<=0){
				pObj->m_fYpos-=3;
				pObj->m_nFSM=2;
				pObj->m_nStep=0;
			}
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
