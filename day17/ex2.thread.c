#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

pthread_t tid;
int bLoop=1;

void *doSomeTing(void *arg)
{
	int nCount=0;

	while(1){
		char ch=getchar();
		if(ch=='q'){
			bLoop=0;
		}
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
	while(bLoop){
		puts("test");
		sleep(1);
	}

	printf("bye~");

	return 0;
}
