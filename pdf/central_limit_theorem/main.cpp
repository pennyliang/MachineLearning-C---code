
#include "stdio.h"
#include "stdlib.h"
#include <time.h>
#include "math.h"

int main(int argc, char** argv)
{
	if(argc!=2)
	{
		printf("Central limit theorem Test \nusage: [sampling cnt] \n ");
		return -1;
	}
	int sample_count = atoi(argv[1]);
	int sample_x_sum = 0;
	double sample_v_sum = 0;
	for(int i=0;i<sample_count;++i)
	{
		sample_x_sum += random ()%10;
	}
	double sample_e = sample_x_sum*1.0/sample_count;

	for(int i=0;i<atoi(argv[1]);++i)
	{
		
		sample_v_sum += pow(random()%10 - sample_e,2)*1.0/sample_count;
	}
	double v_sum = 0;
	for(int i=0;i<10;++i)
	{
		v_sum += (i-4.5)*(i-4.5)*1/10;
	}
	printf("E(x):%f \t sample E(x):%f\n",(0+9.0)/2,sample_e);
	printf("V(x):%f \t sample variant:%f\n", v_sum, sample_v_sum); 
	
	return 0;
}
