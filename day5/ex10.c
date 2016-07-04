#include<stdio.h>

int main()
{
	char word[50]="hi~ word";
	/*word[0]='w';
	word[1]='o';
	word[2]='r';
	word[3]='d';
	word[4]=0x00;

	for(int i=0;i<5;i++){
		printf("%c",word[i]);
	}*/
	
	printf("%s\r\n",word);

	/*int i=0;
	while(word[i]!=0x00){
		printf("%c",word[i]);
		i++;
	
	}*/

	for(int i=0;i<50;i++){
		printf("%d",word[i]);
	}
	scanf("%s",(word+9));
	
//	*(word+2)=0x00;

	printf("your input is :%s",word);


	return 0;
}
