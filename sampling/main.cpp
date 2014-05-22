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
bool M() // can this model generate a event (t,f,t,t)
{
	//t,f,t,t
	if(rdm(P_C[0]))
	{
		ret[0] = 1;
	}
	else
	{
		return false;
	}
	
	if (ret[0] == 1 && rdm(1-P_S_O_C[0]))
	{
		ret[1] = 0;
	}
	else
	{
		return false;
	}

	if (ret[0] == 1 && rdm(P_R_O_C[0]))
        {
                ret[2] = 1;
        }
        else 
        {
                return false;
        }

	if (ret[0] == 1 && ret[1] == 0 && ret[2] == 1 && rdm(P_W_O_S_R[2]))
        {
                ret[3] = 1;
        }
        else
        {
                return false;
        }
	return true; 
};
int main(void)
{
	int sum = 0;
	srand(time(NULL));
	for(int i=0;i<10000000;++i)
	{
		if( M())
		{
			sum++;
		}
	}
	cout<<sum/10000000.0<<endl;
	return 0;
}

