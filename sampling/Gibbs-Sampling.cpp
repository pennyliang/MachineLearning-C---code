#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

//typedef int event_vector[4];
struct event_vector
{
	int m_v[4];
	event_vector()
	{
		m_v[0] = 0; m_v[1] = 0; m_v[2] = 0; m_v[3] = 0;
	}
	event_vector(const event_vector& e)
	{
		m_v[0] = e.m_v[0];
		m_v[1] = e.m_v[1];
		m_v[2] = e.m_v[2];
		m_v[3] = e.m_v[3];
	}
	int &operator [] (int idx)
	{
		return m_v[idx];	
	}
	
};
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

event_vector ret;
void Gibbs_Sampling()
{
	ret[1] = 1;
	ret[3] = 1;
	
	if(ret[2] == 1 && ret[1] == 1 && rdm((P_S_O_C[0]*P_R_O_C[0])))
        {
                ret[0] = 1;
        }
        else if( ret[2] == 0 && ret[1] == 1 && rdm((P_S_O_C[0]*(1-P_R_O_C[0]))))
        {
                ret[0] = 1;
        }
	/*else if( ret[2] == 1 && rdm((P_S_O_C[1]*P_R_O_C[1])))
	{
		ret[0] = 0;
	}
	else if(  ret[2] == 0 && rdm((P_S_O_C[1]*(1-P_R_O_C[1]))))
	{
		ret[0] = 0;
	}*/
	else{ ret[0] = 0;}
	
	if (ret[0] == 1 && ret[1] == 1 && ret[3] == 1 && rdm(P_R_O_C[0]*P_W_O_S_R[0]))
        {
                ret[2] = 1;
        }
	else if(ret[0] == 0 && ret[1] == 1 && ret[3] == 1 && rdm((1-P_R_O_C[0])*P_W_O_S_R[0]))
	{
		ret[2] = 1;
	}
	/*else if(ret[0] == 1 && ret[1] == 1 && ret[3] == 1 && rdm(P_R_O_C[1]*P_W_O_S_R[1]))
	{
		ret[2] = 0;
	}
	else if(ret[0] == 0 && ret[1] == 1 && ret[3] == 1 && rdm((1-P_R_O_C[1])*P_W_O_S_R[1]))
        {
                ret[2] = 0;
        }*/
        else
        {
                ret[2] = 0;
        }
}

struct weight_counter
{
	vector< pair<event_vector,double> > m_v;
	double sum;
	void print_all(void)
	{
		for(int i=0;i<m_v.size();++i)
                {
			cout<<m_v[i].first[0]<<"\t"<<m_v[i].first[1]<<"\t"<<m_v[i].first[2]<<"\t"<<m_v[i].first[3]<<"\t"<<m_v[i].second/sum<<endl;
		}
	}
	void Normalize(void)
	{
		sum = 0;
		for(int i=0;i<m_v.size();++i)
                {
                        sum+=m_v[i].second;
                }
	}
	double & operator[] (event_vector& c)
	{
		for(int i=0;i<m_v.size();++i)
		{
			if(m_v[i].first[0] == c[0] && m_v[i].first[1] == c[1]&&m_v[i].first[2] == c[2]&&m_v[i].first[3] == c[3])
			{
				return m_v[i].second;
			}
		}
		m_v.push_back(make_pair(c,0));
		return m_v[m_v.size()-1].second;
	}
};
int main(void)
{
	int sum = 0;
	srand(time(NULL));
	int N[2] = {0};
	weight_counter W;	
	for(int i=0;i<100;++i)
	{
		Gibbs_Sampling(); // return weight and ret, ret is global variable.
		W[ret] += 1;
	}
	W.Normalize();
	W.print_all();
	return 0;
}

