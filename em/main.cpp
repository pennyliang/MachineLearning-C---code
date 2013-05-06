#include "math.h"
#include "stdio.h"
enum {
	NUMBER,
	LABLE,
	P,
	ALL
};
double x[][ALL] = {{1.5,0,0},{1.8,0,0},{1.9,1,0},{2.0,1,0},{2.1,1,0},{2.2,1,0},{2.2,1,0},{2.4,0,0},{2.5,1,0},{2.7,0,0},{2.9,1,0},{3.0,1,0},{3.3,0,1},{3.9,0,0},{3.9,1,0},{3.9,1,0},{4.0,0,0},{4.1,1,0},{4.1,0,0},{4.2,0,0},{5.0,1,0}};
double mean[2] = {0,0};
double var[2]={0,0};
int count[2] = {0,0};
int sample_count = sizeof(x) / (sizeof(double)*ALL);
void intialize()
{
	for(int i=0;i<sample_count;++i)
	{
		count[ int(x[i][LABLE]) ]++;;
	}
	for(int i=0;i<sample_count;++i)
        {
                x[i][P] = (count[int(x[i][LABLE])]*1.0)/sample_count;
        }
}

void update_mean_var()
{
	mean[0] = 0; mean[1] = 0;
	
	for(int i=0;i<sample_count;++i)
	{
		mean[int(x[i][LABLE])] += x[i][NUMBER]; 
	}
	mean[0] /= count[0];
	mean[1] /= count[1];

	var[0] = 0; var[1] = 0;
	for(int i=0;i<sample_count;++i)
	{
		var[int(x[i][LABLE])] += ( x[i][NUMBER] - mean[int(x[i][LABLE])] ) * ( x[i][NUMBER] - mean[int(x[i][LABLE])] );
	}	
	
	var[0] /= count[0];
	var[1] /= count[1];

}
double pi = 3.1415926;
double e = 2.718281828;
double Gos(double x, double mean, double var)
{
	return (1/sqrt(var*pi*2)) * pow(e, -1*(x-mean)*(x-mean)/(2*var));
}
void update_p()
{
	for(int i=0;i<sample_count;++i)
	{
		x[i][P] = 0.0;
		double p1 =  Gos(x[i][NUMBER],mean[int(x[i][LABLE])],var[int(x[i][LABLE])]);
		double p2 =  Gos(x[i][NUMBER],mean[(int(x[i][LABLE])+1)%2],var[(int(x[i][LABLE])+1)%2]);
		x[i][P] = p1 / (p1 + p2) ;
	}	
}

int main(void)
{
	intialize();
	int iter_max = 10;
	printf("before:");
	for(int k=0;k<sample_count;++k)
        {
		printf("\t#%d#,%f",int(x[k][LABLE]),x[k][NUMBER]);
	}
	printf("\n");	
	for(int i = 0,j=1;i<iter_max&&j>0;++i)
	{
		j=0;
		update_mean_var();;
		update_p();
		printf("iter:%d",i);	
		for(int k=0;k<sample_count;++k)
		{
			x[k][LABLE] = x[k][P]<0.5 ? (int(x[k][LABLE])+1)%2:x[k][LABLE] ;
			j = x[k][P]<0.5 ? j+1:j;
			printf("\t#%d#,%f",int(x[k][LABLE]),x[k][NUMBER]);
		}
		printf("\n");
	}
	return 0;
}
