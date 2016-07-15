#ifndef __AREA_H__
#define __AREA_H__

typedef struct _S_AREA{
	char *m_szName;
	struct _S_AREA *node[8];

	void (*pfDraw)(struct _S_AREA *);
	struct _S_AREA* (*pfFind)(struct _S_AREA *,const char *);

}_S_AREA;

void area_init(_S_AREA *pObj);

#endif
