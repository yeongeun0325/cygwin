#ifndef __PLANE_H__
#define __PLANE_H__

typedef struct _S_Plane{
	int m_nXpos;
	int m_nYpos;
	_S_MAP_OBJECT *m_pBody;
	void (*fpApply)(struct _S_Plane *,double ,char);
	void (*fpDraw)(struct _S_Plane *,_S_MAP_OBJECT *);
} _S_Plane;

void Plane_init(_S_Plane *pObj,_S_MAP_OBJECT *pBody,int x,int y);
void Plane_Apply(_S_Plane *pObj,double deltaTick,char key_input);
void Plane_Draw(_S_Plane *pObj, _S_MAP_OBJECT *pBuff);


#endif
