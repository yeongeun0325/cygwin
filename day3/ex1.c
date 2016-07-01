#include<stdio.h>

int main()
{
	char cmd;
	scanf("%s",&cmd);
	
	/*
	if(cmd=='z'){
		printf("질럿을 생산합니다.\r\n");
	}
	else if(cmd=='d'){
		printf("드래곤을 생산합니다.\r\n");
	}
	else {
		printf("잘못된 입력입니다.\r\n");
	}
	*/

	switch(cmd){
		case 'z':
			printf("질럿을 생산합니다.\r\n"); 
			break;
		case 'd':
			printf("드래곤을 생산합니다.\r\n"); 
			break;
		default:
			printf("잘못된 입력입니다.\r\n"); 
			break;
	}

	return 0;
}
