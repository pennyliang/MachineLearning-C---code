#include "stdio.h"
#include "stdint.h"
#define _USE_MATH_DEFINES
#include <math.h>

//Beta(x|a,b) = 1/B(a,b) * x^(a-1) * (1-x)^(b-1)
//B(a,b) =T(a)T(b)/T(a+b)
//T(a)=(a-1)!

int T(uint32_t a)
{
	
	if(a==1|| a==0)
		return 1;
	else
		return (a-1)*T(a-1);
}
double T2(double a)
{
	double e = 2.718281828;
	
	return sqrt(2*M_PI)*pow(e,-a)*pow(a,a-0.5);

}
double B(int a,int b)
{
	return T2(a)*T2(b)*1.0/T2(a+b);
}
double Beta(double x,int a,int b)
{
	return 1.0/B(a,b) * pow(x,a-1) * pow((1-x),b-1);
}
int main(void)
{
	/*{
		int a = 1 ,b = 1;
		for(int i=0;i<20;++i)
		{
			double plot = 0+(i/20.0);
			printf("%f\t",Beta(plot,a,b));
		}
	}*/
	{
		int a = 0.1 , b =0.1;
		for(int i=0;i<20;++i)
		{
			double plot = 0+(i/20.0);
			printf("%f,%f\t",plot,Beta(plot,a,b));
		}
	}
}
