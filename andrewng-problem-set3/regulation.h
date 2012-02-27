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

int progress(const char* x_dat,const char* y_dat)
{
	//	read y.dat into y[20]
	double y[20];
	{
		FILE * fp;
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		fp = fopen(y_dat, "r");
		if (fp == NULL)
			exit(EXIT_FAILURE);
		int i=0;
		while ((read = getline(&line, &len, fp)) != -1) {
			y[i++] = atof(line);	
		}
		if (line)
			free(line);
	}

	//	read x.dat into x[20][100] 20 sample, 100 item in every sample
	double x[20][100];
	double xT[100][20];
	{		
		FILE * fp;
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		fp = fopen(x_dat, "r");
		if (fp == NULL)
			exit(EXIT_FAILURE);
		int k=0;
		while ((read = getline(&line, &len, fp)) != -1) {
			for(int i=0;i<100;++i)
			{
				char* item = line+16*i;
				line[16*(i+1)]='\0';
				x[k][i] = atof(item);
				xT[i][k] = x[k][i];
				line[16*(i+1)]=' ';
			}
			k++;
		}
		if (line)
			free(line);
	}
	double lamda = 0.1;
	double theta[100];
	double oldtheta[100];
	for(int i=0;i<100;++i)
	{
		theta[i]=0;
	}	
	for(int i=0;i<100;++i)
	{
		oldtheta[i]=1;
	}
	while ( norm(theta,oldtheta) > 0.00001)
	{
		for(int i=0;i<100;++i) oldtheta[i] = theta[i];

		for(int ti=0;ti<100;++ti)
		{
			theta[ti]=0;
			double theta_i1 = 0.0; 
			double theta_i2 = 0.0;
			double r[20]; 
			for(int i=0;i<20;++i)
			{
				double sum=0.0;
				for(int j=0;j<100;++j)
				{
					sum+=x[i][j]*theta[j];
				}
				r[i] = sum-y[i];
			}
			double sum = 0.0;
			for(int i=0;i<20;++i)
			{
				sum += x[i][ti]*r[i];
			}
				
			double xx = 0.0;
			for(int i=0;i<20;++i)
			{
				xx += x[i][ti]*x[i][ti];
			}
			
			theta_i1 = (sum*(-1)-lamda)/xx;
			if(theta_i1<0) theta_i1 = 0;

			theta_i2 = (sum*(-1)+lamda)/xx;
			if(theta_i2>0) theta_i2 = 0;
			// try theta_i1
			theta[ti] = theta_i1;
			double obj_theta_1 = 0.0;
			for(int i=0;i<20;++i)
                        {
                                double sum=0.0;
                                for(int j=0;j<100;++j)
                                {
                                        sum+=x[i][j]*theta[j];
                                }
                                obj_theta_1 += fabs(sum-y[i]);
                        }
			obj_theta_1 = obj_theta_1*obj_theta_1*(0.5);
			for(int i=0;i<100;++i)
			obj_theta_1 += lamda*fabs(theta[i]);
			
			// try theta_i2	
			theta[ti] = theta_i2;
			double obj_theta_2 = 0.0;
                        for(int i=0;i<20;++i)
                        {
                                double sum=0.0;
                                for(int j=0;j<100;++j)
                                {
                                        sum+=x[i][j]*theta[j];
                                } 
                                obj_theta_2 += fabs(sum-y[i]);
                        }
                        obj_theta_2 = obj_theta_2*obj_theta_2*(0.5);
                        for(int i=0;i<100;++i)
                        obj_theta_2 += lamda*fabs(theta[i]);
	
			// chose theta from obj_theta
			if(obj_theta_1<obj_theta_2)
			{
				theta[ti] = theta_i1;
			}
			else
			{
				theta[ti] = theta_i2;
			}
			for(int i=0;i<100;++i)
			{
				fprintf(stderr,"%f\t",theta[i]);
			}
			fprintf(stderr,"%f,%f\n",obj_theta_1,obj_theta_2);	
		}
	}
	/* the answer which teach ng gives us, show in theta.dat*/
	theta[0] = 0.68372018;
	theta[1] = 8.4110202*0.1;
	theta[2] = -8.3028605*0.1;
	theta[3] = -8.5031124*0.1;
	theta[4] = -9.3904984*0.1;
	/* i check the answer of mine, is there big difference between the answer of tearch ng gives*/
	double obj_theta_1 = 0.0;
	for(int i=0;i<20;++i)
	{
		double sum=0.0;
		for(int j=0;j<100;++j)
		{
			sum+=x[i][j]*theta[j];
		}
		obj_theta_1 += fabs(sum-y[i]);
	}
	obj_theta_1 = obj_theta_1*obj_theta_1*(0.5);
	for(int i=0;i<100;++i)
		obj_theta_1 += lamda*fabs(theta[i]);
	fprintf(stderr,"the difference between with the right answer:\n%f\n",obj_theta_1);
	return EXIT_SUCCESS;
}
