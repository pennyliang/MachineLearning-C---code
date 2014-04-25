#include <stdio.h>
#include <math.h>
using namespace std;
char corpus[5][60]={  "zcngotcnx, igcump, zjcjs, lqpWiqu, cefmfhc, o, lb, fdc",
		        "m, r, xevo, ijjiir, b, to, jz, gsr, wq, vf, x, ga,",
		        "pcp, d, oziVlal, hzagh, yzop, io, advzmxnv,",
		        "emx, kayerf, mlj, rawzyb, jp, ag, ctdnnnbg, wgdw, t,",
		        "cy, spxcq, uzflbbf, dxtkkn, cxwx, jpd, ztzh, lv, zhpkv"
	   	   };
float p_corpus(int c,float theta,float& f1)
{
	float sum = 0;
	for(int i=0;i<sizeof(corpus[c])/sizeof(char);++i)
	{
		sum += corpus[c][i]>='a' && corpus[c][i]<='z'	? 1  : 0;	
	}
	f1 = sum/sizeof(corpus[c]);
	return pow(2.718281828,-1*(theta * f1));
}
int main(void)
{
	float theta1 = 1;
	float f1[5] = {0};
	float p[5] = {0};
	for(int iter = 0; iter<100000;++iter)
	{
		float sum_p = 0.0;
		for(int i=0;i<5;++i)
		{
			p[i] = p_corpus(i,theta1,f1[i]);
			sum_p += p[i];
		}
		theta1 -= 0.1*((f1[0]+f1[1]+f1[2]+f1[3]+f1[4])/5 - (f1[0]*p[0]/sum_p+f1[1]*p[1]/sum_p+f1[2]*p[2]/sum_p+f1[3]*p[3]/sum_p+f1[4]*p[4]/sum_p));
		//printf ("%f\t%f\t%f\t%f\t%f\n",p[0]/sum_p, p[1]/sum_p,p[2]/sum_p,p[3]/sum_p,p[4]/sum_p,p[5]/sum_p);
		printf ("%f\n",theta1);
	}	
	return 0;
}
