#ifndef __BULLET_H__
#define __BULLET_H__

typedef struct _S_BULLET_OBJECT{
	int m_nFSM;
	int m_nStep;
	double m_fXpos;
	double m_fYpos;

	double m_fCenterX;
	double m_fCenterY;
	
	double m_fSpeed;
	double m_fvx;	//x축 벡터
	double m_fvy;	//y축 벡터

	double m_faccLifeTime; //현재 생존시간 
	double m_fLifeLimit; //수명

	_S_MAP_OBJECT *m_pBody;
	
	void (*pfDraw)(struct _S_BULLET_OBJECT *,_S_MAP_OBJECT *);
	void (*pfApply)(struct _S_BULLET_OBJECT *pObj,double deltaTick);
	void (*pfFire)(struct _S_BULLET_OBJECT *,int ,int ,double ,double ,double ,double);


} _S_BULLET_OBJECT;

void bullet_init(_S_BULLET_OBJECT *pObj,double x,double y,double speed,_S_MAP_OBJECT *pBody);

#endif
