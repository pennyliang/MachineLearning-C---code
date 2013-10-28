#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <float.h>

using namespace std;

typedef pair<double, double> direct_t;

ostream& operator<<(ostream &os , direct_t& p)
{
	cout<<p.first<<"\t"<<p.second<<endl;
}
direct_t  operator + ( direct_t& left, direct_t& right)
{
	return direct_t(left.first + right.first, left.second + right.second);
}
direct_t  operator - ( direct_t& left, direct_t& right)
{
        return direct_t(left.first - right.first, left.second - right.second);
}
double  operator * ( direct_t& left, direct_t& right)
{
        return (left.first * right.first + left.second * right.second);
}
double norm(direct_t& vect)
{
	return sqrt( vect.first*vect.first + vect.second*vect.second );
}
int main(void)
{
	const int postive_number = 3;
	const int negative_number = 3;
	direct_t positive_samples[postive_number] = {direct_t(1,1+0.5),direct_t(2-0.5,2),direct_t(3,3+0.8)};	
	direct_t negative_samples[negative_number] = {direct_t(4,4-0.5),direct_t(5+0.5,5),direct_t(6,6-1)};	

	direct_t theta(0,2); // initialized theta with (1,2)
	
	int correct_number = 0;
	do{
		correct_number = 0;
		for(int i=0;i<postive_number;++i)
		{
			if( positive_samples[i]*theta > 0)
			{
				correct_number++;
			}
			else
			{
				theta = theta + positive_samples[i];
			}
		}
		for(int i=0;i<negative_number;++i)	
		{
			if( negative_samples[i]*theta < 0)
			{
				correct_number++;
			}
			else
			{
				theta = theta - negative_samples[i];
			}
		}
		cout<<"theta now:"<<theta<<endl;
	}while(correct_number<postive_number+negative_number);
		
	double r = DBL_MAX;
	for(int i=0;i<3;++i)
	{
		double t = +1*(positive_samples[i]*theta);
		if(t<r) r = t;
		cout<< t << endl;
	}
	for(int i=0;i<3;++i)
        {
		double t = -1*(negative_samples[i]*theta) ;
		if(t<r) r = t;
                cout<<t << endl;
        }

	cout<<"margin:"<<r/norm(theta)<<endl;
	cout<<"theta final:"<<theta<<endl;	

}
