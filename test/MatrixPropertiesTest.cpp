#include "MatrixTests.hpp"

TEST_F(MatrixTest, MatrixTraceTest) {
	Matrix
		identity(100),
		BIG({
			 {13, -15, -7 , 9  , 13, -1, 1, -13},
			 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
			 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
			 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
		}),
		empty(0),
		square(4, 4, 4.);
	ASSERT_ANY_THROW(BIG.Trace());
	ASSERT_TRUE(cmp_double(identity.Trace(), 100.));
	ASSERT_TRUE(cmp_double(empty.Trace(), 0.));
	ASSERT_TRUE(cmp_double(square.Trace(), 16.));
}

TEST_F(MatrixTest, MatrixDeterminantTest) {
	Matrix
		longmatrix({
			 {13, -15, -7 , 9  , 13, -1, 1, -13},
			 {-9, 2  , 4  , -11, 3 , -1, 5, -13},
			 {-5, 9  , -14, -2 , 5 , -2, 7, -3 },
			 {1 , 3  , -7 , 8  , 11, -1, 4, 14 },
		}),
		identity(10),
		empty(0),
		det_0({
				{ 20,  28,  8,  4,  32 },
				{ 25,  35, 10,  5,  40 },
				{ 40,  56, 16,  8,  64 },
				{-10, -14, -4, -2, -16 },
				{  0,   0,  0,  0,   0 },
		}),
		inversible({
				{   7,  -1,  9,  4,   6},
				{  14, -11,  6,  9,  -8},
				{  -8, -10,  2,  9, -14},
				{ -10,   2,-15, -9,  -4},
				{   0,  -2, 10, -7,  14},
		});
	ASSERT_ANY_THROW(longmatrix.Det());
	ASSERT_TRUE(cmp_double(identity.Det(), 1.));
	ASSERT_TRUE(cmp_double(empty.Det(), 1.));
	ASSERT_TRUE(cmp_double(det_0.Det(), 0.));
	ASSERT_TRUE(cmp_double(inversible.Det(), -81860.));
}
