#ifndef __POTAL_BULLET_H__
#define __POTAL_BULLET_H__

typedef struct {
	int m_nFSM;
	int m_nStep;
	double m_fXpos;
	double m_fYpos;
	
	double m_fSpeed;
	double m_fvx;	//x축 벡터
	double m_fvy;	//y축 벡터

	double m_faccLifeTime; //현재 생존시간 
	double m_fLifeLimit; //수명

	_S_MAP_OBJECT *m_pBody;

} _S_Potal_Bullet_Object;

void Potal_Bullet_init(_S_Potal_Bullet_Object *,double,double,double,_S_MAP_OBJECT *);
void Potal_Bullet_Apply(_S_Potal_Bullet_Object *,double);
void Potal_Bullet_Draw(_S_Potal_Bullet_Object *,_S_MAP_OBJECT *);

void Potal_Bullet_Fire(_S_Potal_Bullet_Object *,int,int,double,double,double,double);

#endif
