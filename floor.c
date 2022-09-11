#include <stdio.h>
int floorm(int num)
{
	int D = 0;
 	while((num-=10)>=0)
 	{
 		D++;
 
 	}
	return D;

}


int main(void)
{

	double a = 3;
	printf("%d",floorm(a));

	return 0;
}
