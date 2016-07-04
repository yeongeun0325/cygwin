#include<stdio.h>

int main()
{
	char cmd;
	int bLoop;
	char buffer[64];
	int nTailIndex=0;
	char *bPoint=buffer;


	for(int i=0;i<64;i++){
		*(bPoint+i)=0;
	}

	bLoop=1;
	
	while(bLoop){
		scanf("%c",&cmd);
		getchar();

		switch(cmd){
			case 'a':	//add
				printf("what :");
				scanf("%c",&cmd);
				getchar();
				bPoint[nTailIndex]=cmd;
				nTailIndex++;
				break;
			case 'd':	//delete
				nTailIndex--;
				bPoint[nTailIndex]=0x00;	
				break;
			case 'f':	//앞에서부터지우기
				for(int i=0;i<nTailIndex-1;i++){
					*(bPoint+i)=*(bPoint+i+1);
				}
				nTailIndex--;
				bPoint[nTailIndex]=0x00;
				break;
			case 's':
				printf("%s\r\n",bPoint);
				break;
			case 'q':
				printf("quit\r\n");
				bLoop=0;
				break;
		}
	}

	return 0;

	
	return 0;
}
