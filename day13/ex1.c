#include<stdio.h>
#include<math.h>

int main()
{
	printf("%f\r\n",sqrt(2.0));

	double vx,vy;
	vx=1.0;
	vy=1.0;

	double vlenght=sqrt((vx*vy+vx*vy));
	
	vx/=vlenght;
	vy/=vlenght;

	printf("%f\r\n",vlenght);

	printf("단위벡터:%f %f \r\n",vx,vy);
	
	vlenght=sqrt(vx*vx+vy*vy);
	printf("벡터의길이:%f\r\n",vlenght);

	return 0;
}
