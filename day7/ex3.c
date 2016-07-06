#include<stdio.h>

int str_prn(char **ary,int cnt)
{
	for(int i=0;i<cnt;i++){
		//puts(ary[i]);
		printf("%s\r\n",ary[i]);
	}
}

int main()
{
	char *ptr_ary[]={"eggle","tiger","lion","squirrel"};
	int count;

	count=sizeof(ptr_ary)/sizeof(ptr_ary[0]);

	str_prn(ptr_ary,count);

	/*for(int i=0;i<count;i++){
		printf("%s\r\n",ptr_arr[i]);
	}*/
	return 0;
}
