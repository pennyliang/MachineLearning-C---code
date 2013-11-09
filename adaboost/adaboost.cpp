#include <iostream>
#include <math.h>
using namespace std;
int sample[10][4] = {
                  {1,0,1,1},
                  {1,0,1,1},
                  {0,1,1,-1},
                  {0,1,0,-1},
                  {1,1,1,1},
                  {0,1,0,1},
                  {0,1,1,1},
                  {1,0,0,-1},
                  {0,1,1,1},
                  {1,0,0,-1}
                  };
int f(int a[4])
{
	if(a[0] == 1) return 1;
	else return -1;
}
int g(int a[4])
{
	if(a[1] == 1) return 1;
        else return -1;
}
int h(int a[4])
{
	if(a[2] == 1) return 1;
        else return -1;
}
typedef int (*func) (int a[4]);
int c_iter_number = 5;
int main(int argc, char** argv)
{
	func func_arr[3] = {f,g,h};
	int m = 10;
	double D[m];
	for(int i=0;i<m;++i)
	{
		D[i] = 1.0/m ; 
	}
	c_iter_number = atoi(argv[1]);
	double error[3];
	double alpha[c_iter_number];
	int h[c_iter_number];
	for(int t =0 ;t<c_iter_number; ++t )
	{	
		for(int i=0;i<3;++i)
		{
			error[i] = 0.0;
			for(int j=0;j<10;++j)
			{
				error[i] += D[j] * ((func_arr[i](sample[j])*sample[j][3]) == 1 ? 0:1);
			}	
		}
		double max = (error[0]-0.5>0?1:-1)*(error[0]-0.5);
		int max_idx = 0 ;
		for(int i = 1; i<3;++i)
		{
			if((error[i]-0.5>0?1:-1)*(error[i]-0.5)>max)
			{
				max = error[i];
				max_idx = i;
			}
		}
		
		alpha[t] = 0.5*log((1-error[max_idx])/error[max_idx]);	
		h[t] = max_idx;
		double sum = 0;
		double alpha_t = alpha[t];
		for(int i=0;i<10;++i)
		{
			int f = h[t];
			double t =  D[i] * exp(-1*alpha_t* (func_arr[f](sample[i])*sample[i][3]) );
			sum += t;
			D[i] = t;
		}
		for( int i=0;i<10;++i)
		{
			D[i] /= sum;
		}
		
	}
	int correct_number = 0;
	for(int s=0;s<10;++s)
	{
		double result = 0;
		for(int i = 0;i<c_iter_number;++i)
		{
			result += alpha[i]*func_arr[h[i]](sample[s]);
		}
		if( (result>0?1:-1) == sample[s][3] ) correct_number++ ;
		cout<<result<<"\t"<<sample[s][3]<<"\t"<<((result>0?1:-1) == sample[s][3])<<endl;
	}
	for(int i=0;i<c_iter_number;++i)
	{
		cout<<h[i]<<endl;
	}
	cout<<correct_number/10.0<<endl;	
}
