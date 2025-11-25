#include <gtest/gtest.h>
#include <Matrix.hpp>

using matrix::Matrix;
using matrix::det;
using matrix::det_bar;

TEST(MatrixTest, DefaultConstructor)
{
    Matrix<int> m;
    EXPECT_EQ(m.rows(), 0u);
    EXPECT_EQ(m.cols(), 0u);
}

TEST(MatrixTest, SizeConstructor)
{
    Matrix<int> m(2, 3);
    EXPECT_EQ(m.rows(), 2u);
    EXPECT_EQ(m.cols(), 3u);
    EXPECT_NO_THROW(m[0][0] = 1);
    EXPECT_NO_THROW(m[1][2] = 5);
}

TEST(MatrixTest, SizeValueConstructor)
{
    Matrix<int> m(2, 2, 7);
    ASSERT_EQ(m.rows(), 2u);
    ASSERT_EQ(m.cols(), 2u);

    for (size_t i = 0; i < m.rows(); ++i)
        for (size_t j = 0; j < m.cols(); ++j)
            EXPECT_EQ(m[i][j], 7);
}

TEST(MatrixTest, SquareConstructor)
{
    Matrix<double> m(3);
    EXPECT_EQ(m.rows(), 3u);
    EXPECT_EQ(m.cols(), 3u);
}

TEST(MatrixTest, IndexOperator)
{
    Matrix<int> m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);

    const Matrix<int> &cm = m;
    EXPECT_EQ(cm[1][1], 4);
}
TEST(MatrixTest, CopyConstructor)
{
    Matrix<int> m1(2, 2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    Matrix<int> m2 = m1;

    EXPECT_EQ(m2.rows(), 2u);
    EXPECT_EQ(m2.cols(), 2u);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);

    m1[0][0] = 100;
    EXPECT_EQ(m2[0][0], 1);
}

TEST(MatrixTest, TemplatedCopyConstructor)
{
    Matrix<int> mi(2, 2);
    mi[0][0] = 1; mi[0][1] = 2;
    mi[1][0] = 3; mi[1][1] = 4;

    Matrix<double> md(mi);

    EXPECT_EQ(md.rows(), 2u);
    EXPECT_EQ(md.cols(), 2u);
    EXPECT_DOUBLE_EQ(md[0][0], 1.0);
    EXPECT_DOUBLE_EQ(md[1][1], 4.0);
}

TEST(MatrixTest, CopyAssignment)
{
    Matrix<int> m1(2, 2, 5);
    Matrix<int> m2(3, 3, 1);

    m2 = m1;

    EXPECT_EQ(m2.rows(), 2u);
    EXPECT_EQ(m2.cols(), 2u);
    EXPECT_EQ(m2[0][0], 5);
    EXPECT_EQ(m2[1][1], 5);

    m1[0][0] = 100;
    EXPECT_EQ(m2[0][0], 5);
}

TEST(MatrixTest, MoveConstructor)
{
    Matrix<int> m1(2, 2, 9);
    Matrix<int> m2 = std::move(m1);

    EXPECT_EQ(m2.rows(), 2u);
    EXPECT_EQ(m2.cols(), 2u);
    EXPECT_EQ(m2[0][0], 9);

    EXPECT_EQ(m1.rows(), 0u);
    EXPECT_EQ(m1.cols(), 0u);
}

TEST(MatrixTest, MoveAssignment)
{
    Matrix<int> m1(2, 2, 3);
    Matrix<int> m2(1, 1, 1);

    m2 = std::move(m1);

    EXPECT_EQ(m2.rows(), 2u);
    EXPECT_EQ(m2.cols(), 2u);
    EXPECT_EQ(m2[0][0], 3);

    EXPECT_EQ(m1.rows(), 0u);
    EXPECT_EQ(m1.cols(), 0u);
}

TEST(MatrixTest, UnaryMinus)
{
    Matrix<int> m(2, 2);
    m[0][0] = 1;  m[0][1] = -2;
    m[1][0] = 3;  m[1][1] = 0;

    Matrix<int> n = -m;
    EXPECT_EQ(n[0][0], -1);
    EXPECT_EQ(n[0][1], 2);
    EXPECT_EQ(n[1][0], -3);
    EXPECT_EQ(n[1][1], 0);
}

TEST(MatrixTest, PlusSameSize)
{
    Matrix<int> a(2, 2);
    Matrix<int> b(2, 2);

    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 10; b[0][1] = 20;
    b[1][0] = 30; b[1][1] = 40;

    Matrix<int> c = a + b;
    EXPECT_EQ(c[0][0], 11);
    EXPECT_EQ(c[0][1], 22);
    EXPECT_EQ(c[1][0], 33);
    EXPECT_EQ(c[1][1], 44);
}

TEST(MatrixTest, PlusThrowsOnSizeMismatch)
{
    Matrix<int> a(2, 2);
    Matrix<int> b(3, 3);

    EXPECT_THROW(a + b, std::runtime_error);
}

TEST(MatrixTest, MinusSameSize)
{
    Matrix<int> a(2, 2);
    Matrix<int> b(2, 2);

    a[0][0] = 5; a[0][1] = 6;
    a[1][0] = 7; a[1][1] = 8;

    b[0][0] = 1; b[0][1] = 2;
    b[1][0] = 3; b[1][1] = 4;

    Matrix<int> c = a - b;

    EXPECT_EQ(c[0][0], 4);
    EXPECT_EQ(c[0][1], 4);
    EXPECT_EQ(c[1][0], 4);
    EXPECT_EQ(c[1][1], 4);
}

TEST(MatrixTest, PlusEqualsAndMinusEquals)
{
    Matrix<int> a(2, 2, 1);
    Matrix<int> b(2, 2, 2);

    a += b;
    EXPECT_EQ(a[0][0], 3);
    EXPECT_EQ(a[1][1], 3);

    a -= b;
    EXPECT_EQ(a[0][0], 1);
    EXPECT_EQ(a[1][1], 1);
}

TEST(MatrixTest, PlusEqualsThrowsOnSizeMismatch)
{
    Matrix<int> a(2, 2);
    Matrix<int> b(1, 3);
    EXPECT_THROW(a += b, std::runtime_error);
}

TEST(MatrixTest, ScalarMultiplicationRight)
{
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = -3; m[1][1] = 4;

    Matrix<int> r = m * 2;

    EXPECT_EQ(r[0][0], 2);
    EXPECT_EQ(r[0][1], 4);
    EXPECT_EQ(r[1][0], -6);
    EXPECT_EQ(r[1][1], 8);
}

TEST(MatrixTest, ScalarMultiplicationLeft)
{
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = -3; m[1][1] = 4;

    Matrix<int> r = 3 * m;
    EXPECT_EQ(r[0][0], 3);
    EXPECT_EQ(r[0][1], 6);
    EXPECT_EQ(r[1][0], -9);
    EXPECT_EQ(r[1][1], 12);
}

TEST(MatrixTest, DetSingleElement)
{
    Matrix<double> m(1, 1);
    m[0][0] = 5.0;
    EXPECT_DOUBLE_EQ(det(m), 5.0);
}

TEST(MatrixTest, Det2x2Double)
{
    Matrix<double> m(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;
    EXPECT_NEAR(det(m), -2.0, 1e-9);
}

TEST(MatrixTest, DetThrowsOnNonSquare)
{
    Matrix<double> m(2, 3);
    EXPECT_THROW(det(m), std::runtime_error);
}

TEST(MatrixTest, DetBar2x2Int)
{
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    EXPECT_EQ(det_bar(m), -2);
}

TEST(MatrixTest, DetBarThrowsOnNonSquare)
{
    Matrix<int> m(2, 3);
    EXPECT_THROW(det_bar(m), std::runtime_error);
}

TEST(MatrixTest, DetBarOverflowThrows)
{
    Matrix<long long> m(2, 2);
    m[0][0] = 500000000000000; m[0][1] = 0;
    m[1][0] = 0;               m[1][1] = 50000000000000;

    EXPECT_THROW(det_bar(m), std::overflow_error);
}
