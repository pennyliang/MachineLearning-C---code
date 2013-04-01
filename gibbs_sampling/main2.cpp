#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

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
                for(int j=0;j<term_per_doc;++j)
                {
                        C[doc[i][j][0] ][doc[i][j][1]]++;
                }
        }
        for(int i=0;i<doc_cnt;++i)
        {
                for(int j=0;j<term_per_doc;++j)
                {
                        F[i][doc[i][j][1]]++;
                }
        }
}
void show_C()
{
	printf("\n");
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
	printf("\n");
	for(int i=0;i<doc_cnt;i++)
	{
		for(int j=0;j<term_per_doc;++j)
		{
			printf("{%d,%d}\t",doc[i][j][0],doc[i][j][1]);
		}
		printf("\n");
	}	
}
void show_F()
{
	printf("\n");
	for( int i =0 ;i<doc_cnt;++i)
	{
		for(int j=0;j<topic_cnt;++j)
		{
			printf("%f\t",F[i][j]);
		}

	}
}
double beta = 0.01;
double alpha = 1;
int max_iter = 64;

int counter_dt_n[doc_cnt][2];
int counter_dt_sum_n[doc_cnt];
int counter_tt_n[2][5];
int counter_tt_sum_n[2];

int main(void)
{
	//update_C_F();
	//show_C();
	for(int m = 0;m<doc_cnt;++m)
	{
		for(int k=0;k<term_per_doc;++k)
		{
			int topic_idx = doc[m][k][1];
			int term_idx = doc[m][k][0];

			counter_dt_n[m][topic_idx]++;
			counter_dt_sum_n[m]++;
			counter_tt_n[topic_idx][term_idx]++;
			counter_tt_sum_n[topic_idx]++;
		}
		srand(time(NULL));
	}
	srand(time(NULL));
	for(int iter = 0; iter<max_iter;++iter)
	{
		for(int m=0;m<doc_cnt;++m) //doc by doc
		{
			for(int k=0;k<term_per_doc;++k) // term by term
			{

				int topic_idx = doc[m][k][1];
				int new_topic_idx;
				int term_idx = doc[m][k][0];
					

				if(counter_dt_n[m][topic_idx]>0)          // avoid to -1....
					counter_dt_n[m][topic_idx]--;
				
				counter_dt_sum_n[m]--;
				
				if(counter_tt_n[topic_idx][term_idx]>0)    //avoid to -1....
					counter_tt_n[topic_idx][term_idx]--;
				
				counter_tt_sum_n[topic_idx]--;

				//sample topic_idx
				double a = (counter_dt_n[m][0]+beta)/(counter_dt_sum_n[m]+term_cnt*beta);

				a *= (counter_tt_n[0][term_idx]+alpha)/(counter_tt_sum_n[0]+topic_cnt*alpha);
				
				double b = (counter_dt_n[m][1]+beta)/(counter_dt_sum_n[m]+term_cnt*beta);
				b *= (counter_tt_n[1][term_idx]+alpha)/(counter_tt_sum_n[1]+topic_cnt*alpha);
				
				double all = a+b;
				double topic_0_share = a/all;
				if( random()%100000 < topic_0_share*100000)
				{
					topic_idx = 0;
					doc[m][k][1] = 0;
				}	
				else
				{
					topic_idx = 1;
					doc[m][k][1] = 1;
				}
				//end sample topic_idx
				if(counter_dt_n[m][topic_idx]<=counter_dt_sum_n[m])   // here must be <= ,pls use your head to think...
					counter_dt_n[m][topic_idx]++;
				counter_dt_sum_n[m]++;
				
				if(counter_tt_n[topic_idx][term_idx]<=counter_tt_sum_n[topic_idx])
					counter_tt_n[topic_idx][term_idx]++;
				
				counter_tt_sum_n[topic_idx]++;
			}
		}
		show_doc();
		update_C_F();
		show_C();
		show_F();
	}
	show_doc();
	update_C_F();
	show_C();
	show_F();
	return 0;
}
