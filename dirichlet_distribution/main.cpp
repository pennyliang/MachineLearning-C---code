
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<stdint.h>

uint64_t tao(int x)
{
	if(x==1)
	{
		return 1;
	}
	else
	{
		return (x-1)*tao(x-1);
	}
}
//try Dir(4,4,2)
//at 3/7,3/7,1/7 the weight reach maximum and around 3/7,3/7,1/7 the weight is heavy
int main(void)
{
	srand(time(NULL));
	double nomalization = (tao(10))/( tao(4) * tao(4) * tao(2) ) ;
	for(int i=0;i<200;i++)
	{
		int a = random()%100000;
		int b = random()%100000;
		int c = random()%100000;
		double all = a+b+c;
		double p1 = a/all;
		double p2 = b/all;
		double p3 = c/all;
		double weight = nomalization * pow(p1,4-1)*pow(p2,4-1)*pow(p3,2-1);
		printf("%f\t%f\t%f\t%f\n",weight,p1,p2,p3);
	}

	return 0;
}
