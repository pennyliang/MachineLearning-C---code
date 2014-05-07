#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
/*
 *  @ - @ - @
 *  |   |   |
 *  @ - @ - @
 
*/
using namespace std;
char corpus[5][60]={  "zcngotcnx, igcump, zjcjs, lqpWiqu, cefmfhc, o, lb, fdc",
		        "m, r, xevo, ijjiir, b, to, jz, gsr, wq, vf, x, ga,",
		        "pcp, d, oziVlal, hzagh, yzop, io, advzmxnv,",
		        "emx, kayerf, mlj, rawzyb, jp, ag, ctdnnnbg, wgdw, t,",
		        "cy, spxcq, uzflbbf, dxtkkn, cxwx, jpd, ztzh, lv, zhpkv"
	   	   };
float p_corpus(int c,float theta1,float& f1)
{
	float sum = 0;	// 小写字母的数量
	for(int i=0;i<sizeof(corpus[c])/sizeof(char);++i)
	{
		sum += corpus[c][i]>='a' && corpus[c][i]<='z'	? 1  : 0;	
	}
	f1 = sum/sizeof(corpus[c]);
	return pow(2.718281828,-1*(theta1 * f1));
}
float p_corpus(char* corpus,float theta1,float& f1)
{
        float sum = 0;  // 小写字母的数量
        for(int i=0;i<sizeof(corpus)/sizeof(char);++i)
        {
                sum += corpus[i]>='a' && corpus[i]<='z'   ? 1  : 0;
        }
        f1 = sum/sizeof(corpus);

        return pow(2.718281828,-1*(theta1 * f1));
}
typedef char t[100];
void sample(t & xx )
{
	for(int i=0;i<100;++i)
	{
		xx[i] = 'a'+ rand()%('z'-'a');
	}
	for(int i=0;i<100;++i)
	{
		if(rand()%1000>500&&rand()%1000<300&&rand()%1000>400)
		{
			xx[i] = ',';
		}
	}
}

int main(void) // using Monte-Carlo sampling, however here we have a new way we donnot want to explain in detail, just in code!
{
	float theta1 = 1;
	float f1[5] = {0};
	float p[5] = {0};
	int i = 0;
	float mc_iteration = 2000;
	for(int iter = 0; iter<100000;++iter)
	{
		i = i%5;
		for( int minibatch=i;true;) // mini batch have only one corpus
		{
			p_corpus(i,theta1,f1[i]);
			p_corpus(i,theta1,f1[(++i)%5]);
			break;
		}
		float mc = 0.0;
		float sum_p = 0.0;
		for(int i=0;i<mc_iteration;++i)
		{
			char sample_string[100]={0};
			sample(sample_string);
			float f;
			float p = p_corpus(sample_string,theta1,f);
			sum_p+=p;
			mc += f*p;
		}
		mc /= sum_p;
		float g = (f1[i]+f1[(++i)%5])/2 - mc;
		cout<<(theta1*mc*8)/sizeof(corpus[0])<<"\t"<<sum_p<<"\t"<<g<<endl;
		theta1 -= 0.1*g;
		i++;
		//printf ("%d\t%f\t%f\t%f\t%f\t%f\n",iter,p[0]/sum_p, p[1]/sum_p,p[2]/sum_p,p[3]/sum_p,p[4]/sum_p,p[5]/sum_p);
		//printf ("%f\n",theta1);
			
	}	
	return 0;
}
