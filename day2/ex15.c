#include<stdio.h>

int main()
{
	char ch='A';
	char name[80]="황금박쥐";
	int in=10;
	double db=16.8;

	printf("정수형 상수의 출력 : %d\r\n",-10);
	printf("정수형 상수의 출력 : %d\r\n",in);
 	printf("정수형 상수의 출력 : %d\r\n",in/3);
	
	printf("실수형 상수의 출력 : %1f\r\n",2.5);
	printf("실수형 상수의 출력 : %1e\r\n",db);
	printf("실수형 상수의 출력 : %1f\r\n",db/4);

	printf("문자상수의 출력 : %c\r\n",'F');
	printf("문자변수의 출력 : %c\r\n",ch);

	printf("문자배열의 출력 : %s\r\n",name);
	printf("문자열상수의 출력 : %s\r\n","날아라 태극호");

	return 0;
}
