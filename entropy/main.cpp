
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdint.h"

#define arr_len(arr) (sizeof(arr)/sizeof(typeof(arr[0])))

double K[]={3.0/12,4.0/12,5.0/12};
double C[]={2.0/12,4.0/12,6.0/12};
double F[]={1.0/12,10.0/12,1.0/12};

double entropy(double*k,uint32_t k_len)
{
	double ret = 0.0;
	for(uint32_t i=0;i<k_len;++i)
	{
		ret += -1*k[i]*log(k[i]);
	}
	return ret;
}

double cross_entropy(double*k,uint32_t k_len,double*c,uint32_t c_len)
{
	double ret = 0.0;
	for(uint32_t i=0;i<k_len&&i<c_len;++i)
	{
		ret += -1*k[i]*log(c[i]);
	}
	return ret;
} 
double KL_divergence(double*k,uint32_t k_len,double*c,uint32_t c_len)
{
	double ret = 0.0;
	ret = cross_entropy(k,k_len,c,c_len) - cross_entropy(k,k_len,k,k_len); //is equal to cross_entropy(k,k_len,c,c_len) - entropy(k,k_len);
	return ret;
}

int main(void)
{
	double ret = 0.0;
	ret = entropy(K,arr_len(K));
	printf("entropy(K)=%f\n",ret);
	
	ret = entropy(C,arr_len(C));
        printf("entropy(C)=%f\n",ret);

	ret = entropy(F,arr_len(F));
        printf("entropy(F)=%f\n",ret);

	ret = KL_divergence(K,arr_len(K),C,arr_len(C));
        printf("KL_divergence(K,C)=%f\n",ret);

	ret = KL_divergence(K,arr_len(K),F,arr_len(F));
        printf("KL_divergence(K,F)=%f\n",ret);

	printf("F has more uncertainty than the others, measured by entropy(F) is smallest\n");
	printf("K is similar to C more than F, measured by KL(K,C)<KL(K,F)\n");

}
