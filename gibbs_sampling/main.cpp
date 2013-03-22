#include <stdio.h>
#include <math.h>
#include <stdlib.h>
const int doc_cnt = 16;
const int term_per_doc = 16;
const int term_cnt = 5;
const int topic_cnt = 2;

int doc[doc_cnt][term_per_doc][topic_cnt]={
	{{2,0},{2,0},{2,0},{2,0},{3,1},{3,0},{3,0},{3,0},{3,1},{3,0},{4,1},{4,1},{4,0},{4,1},{4,0},{4,0}},
	{{2,0},{2,0},{2,1},{2,0},{2,0},{3,1},{3,1},{3,1},{3,1},{3,1},{3,1},{3,0},{4,1},{4,0},{4,0},{4,1}},
	{{2,0},{2,0},{2,0},{2,1},{2,0},{2,0},{2,0},{3,0},{3,1},{3,0},{3,1},{3,0},{4,1},{4,0},{4,0},{4,0}},
	{{2,1},{2,1},{2,1},{2,0},{2,1},{2,0},{2,0},{3,0},{3,1},{3,1},{3,0},{3,0},{3,0},{4,0},{4,0},{4,0}},
	{{2,1},{2,1},{2,0},{2,1},{2,0},{2,1},{2,0},{3,1},{3,0},{4,0},{4,1},{4,0},{4,0},{4,0},{4,0},{4,0}},
	{{2,0},{2,1},{2,1},{2,0},{2,1},{2,1},{2,1},{2,1},{2,1},{3,0},{3,1},{3,0},{4,0},{4,0},{4,1},{4,1}},
	{{0,0},{2,0},{2,1},{2,1},{2,1},{3,1},{3,1},{3,0},{3,0},{3,1},{3,0},{4,0},{4,1},{4,1},{4,1},{4,0}},
	{{0,1},{1,0},{1,1},{2,0},{2,0},{2,1},{2,1},{2,1},{2,1},{3,0},{3,1},{3,1},{3,0},{4,1},{4,1},{4,0}},
	{{0,1},{1,0},{1,0},{1,1},{2,0},{2,0},{2,0},{2,0},{2,0},{2,1},{3,1},{3,0},{3,1},{3,1},{4,0},{4,1}},
	{{0,1},{0,0},{1,1},{1,1},{1,0},{2,1},{2,0},{2,0},{2,0},{2,0},{2,0},{3,1},{4,1},{4,0},{4,0},{4,1}},
	{{0,0},{0,1},{1,0},{1,1},{1,1},{2,0},{2,0},{2,0},{2,1},{2,1},{2,0},{2,0},{3,1},{3,1},{3,1},{4,1}},
	{{0,0},{0,0},{0,0},{1,0},{1,0},{1,0},{1,0},{1,1},{1,0},{2,1},{2,0},{2,1},{2,1},{2,0},{2,1},{3,0}},
	{{0,0},{0,0},{0,0},{0,1},{0,1},{0,1},{1,0},{1,1},{1,0},{2,1},{2,0},{2,0},{2,0},{2,1},{2,1},{4,0}},
	{{0,0},{0,0},{1,1},{1,1},{1,0},{1,0},{1,0},{1,1},{1,1},{1,1},{2,1},{2,1},{2,0},{2,1},{2,0},{2,0}},
	{{0,0},{0,1},{0,1},{0,1},{1,1},{1,1},{1,1},{1,0},{1,0},{1,1},{1,0},{2,1},{2,0},{2,1},{2,0},{2,1}},
	{{0,1},{0,0},{0,1},{0,1},{0,0},{1,1},{1,1},{1,0},{1,0},{1,0},{1,0},{1,1},{2,1},{2,1},{2,1},{2,0}},

};

double C[term_cnt][topic_cnt];
double F[doc_cnt][topic_cnt];

void update_C_F()
{
	for(int i=0;i<term_cnt;++i)
        {
                for(int j=0;j<topic_cnt;++j)
                {
                        C[i][j] = 0;
                }
        }
        for(int i=0;i<doc_cnt;++i)
        {
                for(int j=0;j<topic_cnt;++j)
                {
                        F[i][j] = 0;;
                }
        }
	for(int i=0;i<doc_cnt;++i)
        {
                for(int j=0;j<term_cnt;++j)
                {
                        C[doc[i][j][0] ][doc[i][j][1]]++;
                }
        }
        for(int i=0;i<doc_cnt;++i)
        {
                for(int j=0;j<term_cnt;++j)
                {
                        F[i][doc[i][j][1]]++;
                }
        }
}
void show_C()
{
	for( int i =0 ;i<term_cnt;++i)
	{
		for(int j=0;j<topic_cnt;++j)
		{
			printf("%f\t",C[i][j]);
		}
		printf("\n");
	}	
}
void show_doc()
{
	for(int i=0;i<doc_cnt;i++)
	{
		for(int j=0;j<term_cnt;++j)
		{
			printf("{%d,%d}\t",doc[i][j][0],doc[i][j][1]);
		}
		printf("\n");
	}	
}
void show_F()
{
	for( int i =0 ;i<doc_cnt;++i)
	{
		for(int j=0;j<topic_cnt;++j)
		{
			printf("%f\t",F[i][j]);
		}

	}
}

double beta = 0.01;
double alpha = 15;
int max_iter = 64;

int main(void)
{
	update_C_F();
	show_C();

	for(int iter = 0; iter<max_iter;++iter)
	{
		for(int d=0;d<doc_cnt;++d) //doc by doc
		{
			for(int i=0;i<term_cnt;++i) // term by term
			{
				double sum_c1[topic_cnt]={0,0};
				double sum_c2[topic_cnt]={0,0};
				double result_c[topic_cnt]={0.0,0.0};		

				for(int t=0;t<topic_cnt;++t)
				{
					for(int k=0;k<term_cnt;++k)
					{
						sum_c1[t] += C[k][t] ;
					}
					for(int tt=0;tt<topic_cnt;++tt)
					{
						sum_c2[t] += F[d][tt];
					}
					result_c[t] += log( (C[doc[d][i][0]][t]+beta) /(sum_c1[t]+term_cnt*beta) ) * (-1) + (-1) * log( (F[d][t]+alpha)/(sum_c2[t]+topic_cnt*alpha)) ;
				}

				if(result_c[0] > result_c[1]) // to label <doc d,word i> with 1 ,we know ther are only two topics show write this code for the reason of simple. 
				{
					//printf("{class,0}:{word:%d},{doc:%d},%f,%f\n",doc[d][i][0],d,result_c[0],result_c[1]);
					doc[d][i][1] = 1;
				}
				else
				{
					//printf("{class,1}:{word:%d},{doc:%d},%f,%f\n",doc[d][i][0],d,result_c[0],result_c[1]);
					doc[d][i][1] = 0;
				}
			}
			//update_C_F(); here to make every change to make effect to next training.
			show_doc();
			printf("\n");
			show_C();
			show_F();
		}
		update_C_F(); //update_C_F() here to make docs trained indenpend with order of training
	}
	return 0;
}
