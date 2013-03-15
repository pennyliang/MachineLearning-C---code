#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double weight(double x,double xi,double tao)
{
	double ret =  exp( -1*(x-xi)*(x-xi)/(2*tao*tao) );	
	return ret;
}
double theta[2]={0.1,0.1};

double x_times_theta(double x[2],double theta[2])
{
	return x[0]*theta[0] + x[1]*theta[1];
}

float Loss(double X,double tao, double x[100][2],double* y ,double* ret)
{
	
	double r_t[2] = {0.0,0.0};
	double l= 0.0;
	for(int i=0;i<99;++i)
	{
		double temp = y[i] - x_times_theta(theta,x[i]) ;
		double r = (weight(X,x[i][1],tao)* temp);
		r_t[0] += r*x[i][0];
		r_t[1] += r*x[i][1];
		l += r*temp;
	}
	ret[0] += r_t[0];
	ret[1] += r_t[1];
	return l;
}
int lwlr(const char* x_dat,const char* y_dat)
{
	//	read x_dat into x[100][2] 0->x0 1->x1
	double x[100][2];
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
	double y[100];
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
	double predict_x = 10;
	double last_l = 10000000.0; //make a max loss
	for(int i=0;i<400;++i)
	{
		double loss[2]={0.01,0.01};
		double tao = 0.8;   //use 0.1  0.3  0.8 2 and 10 try in this homework
		double l = Loss(predict_x,tao,x,y,&loss[0]);
		theta[0] = theta[0] + 0.0005*loss[0];
		theta[1] = theta[1] + 0.0005*loss[1];
		if( l >= last_l) break;  //no loss decline at all , just quit
		double predict_y = theta[0]+predict_x*theta[1];
		printf("loss:%f,predict_x:%f,tao:%f,after %dth iterate %f\n",l,predict_x,tao,i,theta[0]+predict_x*theta[1]);
		last_l = l;
	}
	
}
