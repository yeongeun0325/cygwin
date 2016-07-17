#ifndef __BULLET_H__
#define __BULLET_H__

typedef struct {
	int m_nFSM;
	int m_nStep;
	double m_fXpos;
	double m_fYpos;
	double m_fSpeed;
	double m_faccLifeTime; //현재 생존시간 
	double m_fLifeLimit; //수명

	_S_MAP_OBJECT *m_pBody;

} _S_BULLET_OBJECT;

void bullet_init(_S_BULLET_OBJECT *,double ,double ,double ,_S_MAP_OBJECT *);
void  bullet_apply(_S_BULLET_OBJECT *,double );
void bullet_draw(_S_BULLET_OBJECT *,_S_MAP_OBJECT *);

void bullet_fire(_S_BULLET_OBJECT *,int ,int ,double ,double);

#endif
