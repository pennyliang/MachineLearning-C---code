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
double e(double x)
{
	return pow(2.718281828,x);
}
double* sig_table;
double function_g(double x)
{
        x=x>3.99?4.0:x;
        x=x<-3.99?-4.0:x;
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
pair<float,float> corpus[1024];
void sample()
{
	for(int i=0;i<1024;++i)
	{
		float x = ((rand()%4096)/4095.0*2) - 1;
		float y = x*x;
		corpus[i] = make_pair(x,y); 
	}
}

int main(void)
{
	init_sig_table();
	float s = 0.01;
	sample();
	float w1[20];
	float w2[20];
	float h[20];
	float b[20];
	float b2;

	float output;
	bool start = false;
	for(int i=0;i<20;++i)
	{
		w1[i] = 0.1*(((rand()%4096)/4095.0*2) );
		w2[i] = 0.1*(((rand()%4096)/4095.0*2) );
		b[i] = 0.1*(((rand()%4096)/4095.0*2) );
	}
	for(int iter = 0;iter<20000;++iter)
	{
		float sum_error = 0.0;
		
		for(int index=0;index<1024;++index)
		{
			float x = corpus[index].first;

			for(int i=0;i<20;++i)
			{
				h[i] = function_g(w1[i]*x+b[i]);
			}
			float sum_tmp = 0.0;
			for(int i=0;i<20;++i)
			{
				sum_tmp += w2[i]*h[i];
			}
			sum_tmp += b2;
			output = function_g(sum_tmp);
			float error = output - corpus[index].second;
			float sign;
			if(error>0)
				sign = +1;
			else
				sign = -1;
			for(int i=0;i<20;++i)
			{
				w2[i] -=  sign*s*h[i]*(output*(1-output));
			}
			b2 -= sign*s*(output*(1-output));

			for(int i=0;i<20;++i)
			{
				w1[i] -=  sign*s*w2[i]*x*((output*(1-output))*h[i]*(1-h[i]));
				b[i] -=   sign*s*w2[i]*((output*(1-output))*h[i]*(1-h[i]));
			}
			sum_error += error>0?error:-1*error;
			if(start)
				cout<<x<<"\t"<<output<<"\t"<<corpus[index].second<<endl;
		}
		cout<<sum_error<<endl;
		if(sum_error<50) start = true;
	}	
	return 0;
}
