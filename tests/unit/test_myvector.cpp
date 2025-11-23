#include <gtest/gtest.h>
#include <MyVector.hpp>

using My_vector::vector;

TEST(MyVectorTest, DefaultConstructor)
{
    vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
}

TEST(MyVectorTest, SizeConstructor)
{
    vector<int> v(5);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v.capacity(), 5u);
}

TEST(MyVectorTest, SizeValueConstructor)
{
    vector<int> v(4, 42);
    ASSERT_EQ(v.size(), 4u);
    ASSERT_EQ(v.capacity(), 4u);

    for (size_t i = 0; i < v.size(); ++i)
        EXPECT_EQ(v[i], 42);
}


TEST(MyVectorTest, IndexOperatorReadWrite)
{
    vector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(MyVectorTest, AtThrowsOnOutOfRange)
{
    vector<int> v(2, 10);

    EXPECT_NO_THROW(v.at(0));
    EXPECT_NO_THROW(v.at(1));
    EXPECT_THROW(v.at(2), std::out_of_range);
    EXPECT_THROW(v.at(100), std::out_of_range);

    const vector<int> cv = v;
    EXPECT_NO_THROW(cv.at(0));
    EXPECT_THROW(cv.at(2), std::out_of_range);
}

TEST(MyVectorTest, BackOnNonEmpty)
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(v.back(), 3);

    const vector<int> &cv = v;
    EXPECT_EQ(cv.back(), 3);
}

TEST(MyVectorTest, BackThrowsOnEmpty)
{
    vector<int> v;
    EXPECT_THROW(v.back(), std::out_of_range);

    const vector<int> cv;
    EXPECT_THROW(cv.back(), std::out_of_range);
}
TEST(MyVectorTest, PushBackIncreasesSize)
{
    vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);

    v.push_back(10);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_GE(v.capacity(), 1u);

    v.push_back(20);
    v.push_back(30);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST(MyVectorTest, CapacityGrowthOnPushBack)
{
    vector<int> v;
    v.push_back(0);
    size_t first_cap = v.capacity();
    EXPECT_EQ(first_cap, 64u);
    for (int i = 1; i < 64; ++i)
        v.push_back(i);

    EXPECT_EQ(v.size(), 64u);
    EXPECT_EQ(v.capacity(), first_cap);

    v.push_back(64);
    EXPECT_EQ(v.size(), 65u);
    EXPECT_EQ(v.capacity(), first_cap * 2);
}

TEST(MyVectorTest, PopBackDecreasesSize)
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.back(), 2);

    v.pop_back();
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v.back(), 1);

    v.pop_back();
    EXPECT_EQ(v.size(), 0u);
    EXPECT_THROW(v.back(), std::out_of_range);
}

TEST(MyVectorTest, PopBackThrowsOnEmpty)
{
    vector<int> v;
    EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(MyVectorTest, CopyConstructorDeepCopy)
{
    vector<int> v1(3, 5);
    v1[1] = 10;

    vector<int> v2 = v1;

    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2.capacity(), v1.capacity());
    EXPECT_EQ(v2[0], 5);
    EXPECT_EQ(v2[1], 10);
    EXPECT_EQ(v2[2], 5);
    v1[1] = 42;
    EXPECT_EQ(v2[1], 10);
}

TEST(MyVectorTest, CopyAssignmentDeepCopy)
{
    vector<int> v1(2, 7);
    vector<int> v2(3, 1);

    v2 = v1;

    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2[0], 7);
    EXPECT_EQ(v2[1], 7);

    v1[0] = 100;
    EXPECT_EQ(v2[0], 7);
}

TEST(MyVectorTest, MoveConstructorStealsResources)
{
    vector<int> v1(3, 9);
    size_t old_cap = v1.capacity();

    vector<int> v2 = std::move(v1);

    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2.capacity(), old_cap);
    EXPECT_EQ(v2[0], 9);
    EXPECT_EQ(v1.size(), 0u);
    EXPECT_EQ(v1.capacity(), 0u);
}

TEST(MyVectorTest, MoveAssignmentStealsResources)
{
    vector<int> v1(3, 4);
    vector<int> v2(1, 1);

    size_t old_cap = v1.capacity();

    v2 = std::move(v1);

    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2.capacity(), old_cap);
    EXPECT_EQ(v2[0], 4);

    EXPECT_EQ(v1.size(), 0u);
    EXPECT_EQ(v1.capacity(), 0u);
}

