#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include "array.hpp"
#include <vector>
#include <string>
just for a test of github
using namespace std;
double corpus[8][9] = {
                       {1,0,0,0,0,0,0,0,1},
		       {0,1,0,0,0,0,0,0,1},
		       {0,0,1,0,0,0,0,0,1},
		       {0,0,0,1,0,0,0,0,1},
		       {0,0,0,0,1,0,0,0,1},
		       {0,0,0,0,0,1,0,0,1},
		       {0,0,0,0,0,0,1,0,1},
	               {0,0,0,0,0,0,0,1,1}
   		};
		       	

double corpus2[8][9]={
                       {1,0,0,0,0,0,0,0,1},
                       {0,1,0,0,0,0,0,0,1},
                       {0,0,1,0,0,0,0,0,1},
                       {0,0,0,1,0,0,0,0,1},
                       {0,0,0,0,1,0,0,0,1},
                       {0,0,0,0,0,1,0,0,1},
                       {0,0,0,0,0,0,1,0,1},
                       {0,0,0,0,0,0,0,1,1}

                        };
                 



double sigmoid(double x)
{
        double ex = pow(2.718281828,x);
        return ex/(1+ex);
}
double* sig_table;
double function_g(double x)
{
        x=x>3.99?4.0:x;
        x=x<-3.99?-4.0:x;
        //return sigmoid(x);
	return sig_table[(uint32_t)((x+4.0)*8*128*1024)];
};
double init_sig_table()
{
        sig_table = (double*)malloc((64*128*1024+1)*sizeof(double));
        for(int i=0;i<64*128*1024;++i)
        {
                sig_table[i] = sigmoid((i/(1048576.0)-4.0));
        }
        sig_table[64*128*1024] = 1;
}

void init_matrix(t_array& w)
{
	for(int i=0;i<w.m_X;++i)
                for(int j=0;j<w.m_Y;++j)
                        w[i][j] = 0.01+ (random()%100+0.1)/100;
}
int main(int argc,char** argv)
{
	init_sig_table();
	srandom(0);
	t_array matrix_w(9,4,NULL);

	init_matrix(matrix_w);
	
	s_array hidden_layer(4,NULL);
	s_array hidden_layer2(4,NULL);
	hidden_layer[3]=1; 	
	hidden_layer2[3]=1;
	double update = 0.01;
	for(int iter = 0;iter<250000;++iter)
	{
		for(int i=0;i<3;++i)
		{
			hidden_layer[i] = 0;
			for(int j=0;j<9;++j)
			{
				hidden_layer[i] += corpus[iter%8][j]*matrix_w[j][i];
			}
			hidden_layer[i] = function_g(hidden_layer[i]);
		}
		for(int i=0;i<8;++i)
		{
			corpus2[iter%8][i] = 0;
			for(int j=0;j<4;++j)
			{
				corpus2[iter%8][i] += hidden_layer[j]*matrix_w[i][j];
			}
			corpus2[iter%8][i] = function_g(corpus2[iter%8][i]);
		}
		for(int i=0;i<3;++i)
                {
                        hidden_layer2[i] = 0;
                        for(int j=0;j<9;++j)
                        {
                                hidden_layer2[i] += corpus2[iter%8][j]*matrix_w[j][i];
                        }
                        hidden_layer2[i] = function_g(hidden_layer2[i]);
                }
		for(int i = 0 ;i<9;++i)
		{
			for(int j=0;j<4;++j)
			{
				matrix_w[i][j] += update * (corpus[iter%8][i]*hidden_layer[j] - corpus2[iter%8][i]*hidden_layer2[j]);
			}
		}
		{
			printf("%f\t%f\t%f\n",hidden_layer2[0],hidden_layer2[1],hidden_layer2[2]);
		}			
	}
}
