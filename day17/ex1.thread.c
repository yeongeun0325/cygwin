#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

pthread_t tid;

void *doSomeTing(void *arg)
{
	int nCount=0;

	while(1){
		printf("tick...%dsec\r\n",nCount);
		//puts("test");
		sleep(1);
		nCount++;
	}
	return NULL;
}

int main()
{
	int err;
	err=pthread_create(&tid,NULL,&doSomeTing,NULL);
	
	if(err!=0){
		printf("\r\n cannot create thread : [%s]\r\n",strerror(err));
	}
	else{
		printf("\r\n create successfully :\r\n");
	}
	char ch=getchar();

	//doSomeTing(NULL);

	printf("u press %c key\r\n",ch);

	return 0;
}
