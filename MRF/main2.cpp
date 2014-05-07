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
	return pow(2.718281828,(theta * f1));
}
int main(void) // using mini-batch with setting size = 2
{
	float theta1 = 1;
	float f1[5] = {0};
	float p[5] = {0};
	p[0] = p_corpus(0,theta1,f1[0]);
	p[1] = p_corpus(1,theta1,f1[1]);
	p[2] = p_corpus(2,theta1,f1[2]);
	p[3] = p_corpus(3,theta1,f1[3]);
	p[4] = p_corpus(4,theta1,f1[4]);

	for(int iter = 0; iter<100000;++iter)
	{

		p[iter%5] = p_corpus(iter%5,theta1,f1[iter%5]);
		iter++;
		p[iter%5] = p_corpus(iter%5,theta1,f1[iter%5]);
		float sum_p = p[(iter-1)%5]+p[iter%5];
		
		theta1 -= -0.1*((f1[iter%5]+f1[(iter-1)%5])/2- (f1[iter%5]*p[iter%5]/sum_p+f1[(iter-1)%5]*p[(iter-1)%5]/sum_p));
		printf ("%d\t%f\t%f\n",iter,p[(iter-1)%5]/sum_p, p[iter%5]/sum_p);
		//printf ("%f\n",theta1);
	}	
	return 0;
}
