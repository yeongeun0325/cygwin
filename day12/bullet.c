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
#include "bullet.h"

void bullet_init(_S_BULLET_OBJECT *pObj,double x,double y,
double speed,_S_MAP_OBJECT *pBody)
{
	pObj->m_nFSM=0;	//0:sleep 1:active
	pObj->m_nStep=0;
	pObj->m_fSpeed=speed;
	pObj->m_fXpos=x;
	pObj->m_fYpos=y;
	pObj->m_pBody=pBody;


}

void bullet_apply(_S_BULLET_OBJECT *pObj,double deltaTick)
{
	//pObj->m_fYpos-=deltaTick*pObj->m_fSpeed;	//스피드당 총알
	pObj->m_fSpeed-=1.0;
}

void bullet_draw(_S_BULLET_OBJECT *pObj,_S_MAP_OBJECT *pMapBuf)
{
	map_drawTile_trn(pObj->m_pBody,(int)(pObj->m_fXpos),
			(int)(pObj->m_fYpos),pMapBuf);
}
