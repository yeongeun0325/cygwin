#ifndef __PLANE_BULLET_H__
#define __PLANE_BULLET_H__

typedef struct _S_PLANE_BULLET_OBJECT {
	int m_nFSM;
	int m_nStep;
	double m_fXpos;
	double m_fYpos;

	double m_fCenterX;
	double m_fCenterY;

	double m_fvx;
	double m_fvy;
	double m_fSpeed;

	double m_faccLifeTime; //현재 생존시간 
	double m_fLifeLimit; //수명

	_S_MAP_OBJECT *m_pBody;

	void (*pfDraw)(struct _S_PLANE_BULLET_OBJECT *pObj,_S_MAP_OBJECT *pMapBuf);
	void (*pfApply)(struct _S_PLANE_BULLET_OBJECT *pObj,double deltaTick);
	void (*pfFire)(struct _S_PLANE_BULLET_OBJECT *,double,double,double,double);
} _S_PLANE_BULLET_OBJECT;

void plane_bullet_init(_S_PLANE_BULLET_OBJECT *pObj,double x,double y,double speed,_S_MAP_OBJECT *pBody);
//void bullet_fire_1(_S_PLANE_BULLET_OBJECT *pObj,int x,int y,double speed,double lifeLimit)
#endif
