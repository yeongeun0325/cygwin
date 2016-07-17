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

void bullet_init(_S_Bullet_Object *pObj,double x,double y,
double speed,_S_MAP_OBJECT *pBody)
{
	pObj->m_nFSM=0;	//0:sleep 1:active
	pObj->m_nStep=0;
	pObj->m_fSpeed=speed;
	pObj->m_fXpos=x;
	pObj->m_fYpos=y;
	pObj->m_pBody=pBody;


}

void bullet_apply(_S_Bullet_Object *pObj,double deltaTick)
{
	switch(pObj->m_nFSM){
		case 0:
			break;
		case 1:
			if(pObj->m_nStep==0){
				pObj->m_nStep++;
				pObj->m_faccLifeTime=0;

			}
			else{
				pObj->m_faccLifeTime+=deltaTick;
				if(pObj->m_faccLifeTime>pObj->m_fLifeLimit){
					pObj->m_nStep=0;
					pObj->m_nFSM=0;
				}
				pObj->m_fYpos-=deltaTick*pObj->m_fSpeed;	//스피드당 총알
			}
			break;
	}
	
}

void bullet_draw(_S_Bullet_Object *pObj,_S_MAP_OBJECT *pMapBuf)
{
	switch(pObj->m_nFSM){
		case 0:
			break;
		case 1:
			map_drawTile_trn(pObj->m_pBody,(int)pObj->m_fXpos,
					(int)pObj->m_fYpos,pMapBuf);
			break;
	}
}

void bullet_fire(_S_Bullet_Object *pObj,int x,int y,double speed,double lifeLimit)
{
	pObj->m_nFSM=1;
	pObj->m_nStep=0;
	pObj->m_fXpos=(double)x;
	pObj->m_fYpos=(double)y;
	pObj->m_fSpeed=speed;
	pObj->m_fLifeLimit=lifeLimit;

}
