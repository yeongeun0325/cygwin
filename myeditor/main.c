#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern int bLoop;
extern char *pTemp;
extern char strCmd[];

void me_exit();
void me_push();
void me_delete();
void me_dump();

int main()
{
	puts("mydeitor v.1.0");

	while(bLoop)
	{
		gets(strCmd);

		pTemp = strtok(strCmd," ");

		if(!strcmp(pTemp,"exit")) {
			me_exit();
		}
		else if(!strcmp(pTemp,"push")) {
			me_push();
		}
		else if(!strcmp(pTemp,"pop")) {
		}
		else if(!strcmp(pTemp,"del")){	//앞에서부터 제거
			me_delete();
		}
		else if(!strcmp(pTemp,"ins")){
			int nIndex=atoi(strtok(NULL," "));
			pTemp=strtok(NULL,"");
			printf("%d %s 추가 \r\n",nIndex,pTemp);
		}
		else if(!strcmp(pTemp,"rm")){
			int nIndex=atoi(strtok(NULL," "));

		}
		else if(!strcmp(pTemp,"set")){
			//set 1 new string
			int nIndex=atoi(strtok(NULL," "));
		}
		else if(!strcmp(pTemp,"dump")) {
			me_dump();
		}
	}

	return 0;
}
