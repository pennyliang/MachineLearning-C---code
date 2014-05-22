#include "stdio.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef int event_vector[4];

double P_C[2] = {0.5,0.5};
double P_S_O_C[2]={0.1,0.5};
double P_R_O_C[2] ={0.8,0.2};
double P_W_O_S_R[4]={0.99,0.9,0.9,0};

bool rdm(double true_probability)
{
	if( ((random()%4096)/4095.0) < true_probability )
	{
		return true;
	}
}

event_vector ret = {0};
bool Prior_Sample()
{
	if(rdm(P_C[0]))
	{
		ret[0] = 1;
	}
	else
	{
		ret[0] = 0;
	}
	
	if (ret[0] == 1 && rdm(P_S_O_C[0]))
	{
		ret[1] = 1;
	}
	else if (ret[0] == 0 && rdm(P_S_O_C[1]))
	{
		ret[1] = 1;
	}
	else
	{
		ret[1] = 0;
	}
	if (ret[0] == 1 && rdm(P_R_O_C[0]))
        {
                ret[2] = 1;
        }
        else if (ret[0] == 0 && rdm(P_R_O_C[1]))
        {
                ret[2] = 1;
        }
	else
	{
		ret[2] = 0;
	}

	if (ret[1] == 1 && ret[2] == 1 && rdm(P_W_O_S_R[0]))
        {
                ret[3] = 1;
        }
	else if (ret[1] == 1 && ret[2] == 0 && rdm(P_W_O_S_R[1]))
        {
                ret[3] = 1;
        }
	else if (ret[1] == 0 && ret[2] == 1 && rdm(P_W_O_S_R[2]))
        {
                ret[3] = 1;
        }
	else if (ret[1] == 0 && ret[2] == 0 && rdm(P_W_O_S_R[3]))
        {
                ret[3] = 1;
        }
        else
        {
                ret[3] = 0;
        }
	return true; 
};
int main(void)
{
	int sum = 0;
	srand(time(NULL));
	for(int i=0;i<10000;++i)
	{
		Prior_Sample();
		cout<<ret[0]<<"\t"<<ret[1]<<"\t"<<ret[2]<<"\t"<<ret[3]<<endl;
	}
	return 0;
}

