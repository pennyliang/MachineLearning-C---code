#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <utility> 
#include <math.h>
#include <stdint.h>
using namespace std;
double sigmoid(double x)
{
        double ex = pow(2.718281828,x);
        return ex/(1+ex);
}
double beta = -1;  //make sure that the small energe means high probability and huge energe means low probability.
double e(double x)
{
	return pow(2.718281828,beta*x);
}
double* sig_table;
double function_g(double x)
{
        x=x>3.99?4.0:x;
        x=x<-3.99?-4.0:x;
	//return sigmoid(x);
        return sig_table[(uint32_t)((x+4.0)*128*1024)];
};
double init_sig_table()
{
        sig_table = (double*)malloc((8*128*1024+1)*sizeof(double));
        for(int i=0;i<8*128*1024;++i)
        {
                sig_table[i] = sigmoid((i/131072.0-4.0));
        }

}
pair<double,double> corpus[1024];
void sample()
{
	for(int i=0;i<1024;++i)
	{
		double x = ((rand()%4096)/4095.0*2) - 1;
		double y = x*x;
		corpus[i] = make_pair(x,y); 
	}
}

int main(int argc, char ** argv)
{
	init_sig_table();
	double s = atof(argv[1]);
	sample();
	double w1[20];
	double w2[20];
	double h[20];
	double b[20];
	double b2 = 0;

	
	double w1_g1[20];
        double w2_g1[20];
	double b_g1[20];
	double b2_g1 = 0;
	
	double w1_g2[20];
        double w2_g2[20];
        double b_g2[20];
        double b2_g2 = 0;

	double output;
	bool start = false;
	for(int i=0;i<20;++i)
	{
		w1[i] = 0.1*(((rand()%4096)/4095.0*2) );
		w2[i] = 0.1*(((rand()%4096)/4095.0*2) );
		b[i] = 0.1*(((rand()%4096)/4095.0*2) );
	}
	for(int iter = 0;iter<20000;++iter)
	{
		double sum_error = 0.0;
		
		for(int index=0;index<1024;++index)
		{
		
			for(int i = 0;i<20;++i)
			{
				w1_g1[i] = 0;
				w2_g1[i] = 0;
				b_g1[i] = 0;
				b2_g1 = 0;
			}	
			double x = corpus[index].first;

			for(int i=0;i<20;++i)
			{
				h[i] = function_g(w1[i]*x+b[i]);
			}
			double sum_tmp = 0.0;
			for(int i=0;i<20;++i)
			{
				sum_tmp += w2[i]*h[i];
			}
			sum_tmp += b2;
			output = function_g(sum_tmp);
			double error = output - corpus[index].second;
			double sign = error>0?+1:-1;
			for(int i=0;i<20;++i)
			{
				w2_g1[i] =  sign*h[i]*(output*(1-output));
			}
			b2_g1 = sign*(output*(1-output));

			for(int i=0;i<20;++i)
			{
				w1_g1[i] =  sign*w2[i]*x*((output*(1-output))*h[i]*(1-h[i]));
				b_g1[i] =   sign*w2[i]*((output*(1-output))*h[i]*(1-h[i]));
			}
			//sample_50_y
			double sum_p = 0.0;
			{	
				for(int i = 0;i<20;++i)
				{
					w1_g2[i] = 0;
					w2_g2[i] = 0;
					b_g2[i] = 0;
					b2_g2 = 0;
				}
				for(int sample_idx=0;sample_idx<50;++sample_idx)
				{
					double tmp = ((rand()%4096)/4095.0*2) - 1;
                			double y = tmp*tmp;

					for(int i=0;i<20;++i)
					{
						h[i] = function_g(w1[i]*x+b[i]);
					}
					double sum_tmp = 0.0;
					for(int i=0;i<20;++i)
					{
						sum_tmp += w2[i]*h[i];
					}
					sum_tmp += b2;
					output = function_g(sum_tmp);
					double errorx = output - y;
					double sign = errorx>0?+1:-1;
					errorx = errorx>0?errorx:-1*errorx;	
					double t = e(errorx);
					sum_p += t;
					for(int i=0;i<20;++i)
					{
						w2_g2[i] +=  (t)*sign*h[i]*(output*(1-output));
					}
					b2_g2 += (t)*sign*(output*(1-output));
					for(int i=0;i<20;++i)
					{
						w1_g2[i] +=  (t)*sign*w2[i]*x*((output*(1-output))*h[i]*(1-h[i]));
						b_g2[i] +=   (t)*sign*w2[i]*((output*(1-output))*h[i]*(1-h[i]));;
					}					
				}
			}
			
			for(int i=0;i<20;++i)
			{
				w1[i] -=  s*(w1_g1[i] - w1_g2[i]/sum_p);
				w2[i] -=  s*(w2_g1[i] - w2_g2[i]/sum_p);
				b[i]  -=  s*(b_g1[i]  - b_g2[i]/sum_p);
			}
			b2 -= s*(b2_g1 - b2_g2/sum_p);
			sum_error += error>0?error:-1*error;
			if(start)
				cout<<x<<"\t"<<output<<"\t"<<corpus[index].second<<endl;
		}
		cout<<sum_error<<endl;
		//if(sum_error<50) start = true;
	}	
	return 0;
}
