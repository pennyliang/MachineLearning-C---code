#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double norm(double theta[100],double oldtheta[100])
{
	double sum = 0.0;
	for(int i=0;i<100;++i)
	{
		sum += fabs(theta[i]-oldtheta[i]);
	}
	return sum;
}

float weight(float x,float xi,float tao)
{
	return expf( -1*(x-xi)*(x-xi)/(2*tao*tao) );	
}
float theta[2]={0.1,0.1};

float x_times_theta(float x[2],float theta[2])
{
	return x[0]*theta[0] + x[1]*theta[1];
}

void Loss(float X,float x[100][2],float* y ,float* ret)
{
	
	for(int i=0;i<99;++i)
	{
		float temp = x_times_theta(theta,x[i])-y[i] ;
		float r = 0.5*(weight(X,x[i][1],0.8)* powf(temp,2.0));
		ret[0] += r*x[i][0];
		ret[1] += r*x[i][1];
	}
}
int progress(const char* x_dat,const char* y_dat)
{
	//	read x_dat into x[100][2] 0->x0 1->x1
	float x[100][2];
	{
		FILE * fp;
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		fp = fopen(x_dat, "r");
		if (fp == NULL)
			exit(EXIT_FAILURE);
		int i=0;
		while ((read = getline(&line, &len, fp)) != -1) {
			x[i][0]= 1;
			x[i++][1] = atof(line);	
		}
		if (line)
			free(line);
	}

	//	read y_dat into y[100]
	float y[100];
	{		
		FILE * fp;
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		fp = fopen(y_dat, "r");
		if (fp == NULL)
			exit(EXIT_FAILURE);
		int k=0;
		while ((read = getline(&line, &len, fp)) != -1) {
			y[k++] = atof(line);
		}
		if (line)
			free(line);
	}
	float predict_x = 4.0;
	float last_v = 0.0;
	for(int i=0;i<40;++i)
	{
		float loss[2]={0.1,0.1};
		Loss(predict_x,x,y,&loss[0]);
		theta[0] = theta[0] + 0.001*loss[0];
		theta[1] = theta[1] + 0.001*loss[1];
		//printf("%f\t%f\n",loss[0],loss[1]);

		float predict_y = theta[0]+predict_x*theta[1];
		printf("after %dth iterate %f\n",i,theta[0]+predict_x*theta[1]);
		if(fabs(last_v-predict_y)<0.05) break;
		last_v = predict_y;
	}
	printf("final:%f\n",theta[0]+predict_x*theta[1]);	 
	
}
