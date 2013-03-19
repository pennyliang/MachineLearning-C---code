
/*
黑盒A：1白章 3黑章
黑盒B：2方框章 5个圆形章

P(A,B)

P(A=白，B=方)
P(A=白，B=圆)
P(A=黑，B=方)
P(A=黑，B=圆)
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
enum a_type  {WHITE,BLACK};
enum b_type  {SQUARE,CIRCLE};
int boxA_get()
{
	if(0==(random())%4)
	{
		return WHITE;
	}
	else
	{
		return BLACK;
	}	
};
int boxB_get()
{
	if((random())%7<=1)
	{
		return SQUARE;
	}
	else
	{
		return CIRCLE;
	}
};

int boxB_get2(int a)
{
	if(random()%2==0)
	{
		if( a == WHITE )
		{
			return SQUARE;
		}
		else
		{
			return CIRCLE;
		}
	}
	else
	{
		return boxB_get();
	}

}
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("usage: [sampling cunt]\n");
		return -1;
	}
	int sample_cnt = atoi(argv[1]);
	srandom(time(NULL));
	if(sample_cnt>1000000)
	{
		printf("chose a number fewer than 1000000\n");
		return -1;
	}
	int A[sample_cnt][2];
	
	for(int i=0;i<sample_cnt;++i)
	{
		A[i][0] = boxA_get();
		A[i][1] = boxB_get();
	}
	//count P(X=WHITE,Y=SQUARE) ,P(X=WHITE),P(Y=SQUARE)
	int count_white_square = 0;
	int count_white = 0;
	int count_square = 0;

	for(int i=0;i<sample_cnt;++i)
	{
		if(A[i][0] == WHITE) count_white++;
		if(A[i][1] == SQUARE) count_square++;
		if(A[i][0] == WHITE && A[i][1] == SQUARE) count_white_square++;
	}
	printf("white:%d,prob:%f,square:%d,prob:%f,<white,square>%d,prob:%f\n",count_white,count_white*1.0/sample_cnt,count_square,count_square*1.0/sample_cnt,count_white_square,count_white_square*1.0/sample_cnt);

	printf("P(X=white,Y=square):%f,P(X=white)*P(Y=square):%f\n",count_white_square*1.0/sample_cnt,(count_white*1.0/sample_cnt)*(count_square*1.0/sample_cnt));	
	

	for(int i=0;i<sample_cnt;++i)
        {
                A[i][0] = boxA_get();
                A[i][1] = boxB_get2(A[i][0]);
        }
	count_white_square = 0;
        count_white = 0;
        count_square = 0;
	
        for(int i=0;i<sample_cnt;++i)
        {
                if(A[i][0] == WHITE) count_white++;
                if(A[i][1] == SQUARE) count_square++;
                if(A[i][0] == WHITE && A[i][1] == SQUARE) count_white_square++;
        }
	printf("//////////////////////\n");
        printf("white:%d,prob:%f,square:%d,prob:%f,<white,square>%d,prob:%f\n",count_white,count_white*1.0/sample_cnt,count_square,count_square*1.0/sample_cnt,count_white_square,count_white_square*1.0/sample_cnt);

        printf("P(X=white,Y=square):%f,P(X=white)*P(Y=square):%f\n",count_white_square*1.0/sample_cnt,(count_white*1.0/sample_cnt)*(count_square*1.0/sample_cnt));


	
}

