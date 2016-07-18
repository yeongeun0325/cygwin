#ifndef __ALIEN_H__
#define __ALIEN_H__

typedef struct _S_ALIEN_OBJECT{
	int m_nFSM;
	int m_nStep;
	
	double m_fXpos;
	double m_fYpos;

	double m_fCenterX;
	double m_fCenterY;

	_S_MAP_OBJECT *m_pBody;
	void (*pfApply)(struct _S_ALIEN_OBJECT *,double);
	void (*pfDraw)(struct _S_ALIEN_OBJECT *,_S_MAP_OBJECT *);
} _S_ALIEN_OBJECT;

void Alien_init(_S_ALIEN_OBJECT *pObj,_S_MAP_OBJECT *pBody);
//void Alien_Apply(_S_ALIEN_OBJECT *pObj,double deltaTick,char key_input);
//void Alien_Draw(_S_ALIEN_OBJECT *pObj, _S_MAP_OBJECT *pBuff);


	


#endif
