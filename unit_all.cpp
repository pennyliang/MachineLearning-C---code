#include <stdio.h>
#include <gtest/gtest.h>
#include "andrewng-problem-set3/regulation.h"

TEST( HW,andrewng_problem_set3 )
{
	progress("./andrewng-problem-set3/x.dat","andrewng-problem-set3/y.dat");
        EXPECT_TRUE( true );
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
