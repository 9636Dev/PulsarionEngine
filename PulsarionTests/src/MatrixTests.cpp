#include <gtest/gtest.h>
#include <PulsarionMath/Math.hpp>

#include <iostream>

class Matrix4x4Test : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }
};

TEST_F(Matrix4x4Test, HandlesIdentity)
{
    Pulsarion::Math::Mat4 m;
    EXPECT_FLOAT_EQ(m.data[0], 1.0f);
    EXPECT_FLOAT_EQ(m.data[1], 0.0f);
    EXPECT_FLOAT_EQ(m.data[2], 0.0f);
    EXPECT_FLOAT_EQ(m.data[3], 0.0f);
    EXPECT_FLOAT_EQ(m.data[4], 0.0f);
    EXPECT_FLOAT_EQ(m.data[5], 1.0f);
    EXPECT_FLOAT_EQ(m.data[6], 0.0f);
    EXPECT_FLOAT_EQ(m.data[7], 0.0f);
    EXPECT_FLOAT_EQ(m.data[8], 0.0f);
    EXPECT_FLOAT_EQ(m.data[9], 0.0f);
    EXPECT_FLOAT_EQ(m.data[10], 1.0f);
    EXPECT_FLOAT_EQ(m.data[11], 0.0f);
    EXPECT_FLOAT_EQ(m.data[12], 0.0f);
    EXPECT_FLOAT_EQ(m.data[13], 0.0f);
    EXPECT_FLOAT_EQ(m.data[14], 0.0f);
    EXPECT_FLOAT_EQ(m.data[15], 1.0f);
}

TEST_F(Matrix4x4Test, HandlesAddition)
{
    Pulsarion::Math::Mat4 m1;
    Pulsarion::Math::Mat4 m2;
    auto result = m1 + m2;
    EXPECT_FLOAT_EQ(result.data[0], 2.0f);
    EXPECT_FLOAT_EQ(result.data[1], 0.0f);
    EXPECT_FLOAT_EQ(result.data[2], 0.0f);
    EXPECT_FLOAT_EQ(result.data[3], 0.0f);
    EXPECT_FLOAT_EQ(result.data[4], 0.0f);
    EXPECT_FLOAT_EQ(result.data[5], 2.0f);
    EXPECT_FLOAT_EQ(result.data[6], 0.0f);
    EXPECT_FLOAT_EQ(result.data[7], 0.0f);
    EXPECT_FLOAT_EQ(result.data[8], 0.0f);
    EXPECT_FLOAT_EQ(result.data[9], 0.0f);
    EXPECT_FLOAT_EQ(result.data[10], 2.0f);
    EXPECT_FLOAT_EQ(result.data[11], 0.0f);
    EXPECT_FLOAT_EQ(result.data[12], 0.0f);
    EXPECT_FLOAT_EQ(result.data[13], 0.0f);
    EXPECT_FLOAT_EQ(result.data[14], 0.0f);
    EXPECT_FLOAT_EQ(result.data[15], 2.0f);
}

TEST_F(Matrix4x4Test, HandlesSubtraction)
{
    Pulsarion::Math::Mat4 m1;
    Pulsarion::Math::Mat4 m2;
    auto result = m1 - m2;
    EXPECT_FLOAT_EQ(result.data[0], 0.0f);
    EXPECT_FLOAT_EQ(result.data[1], 0.0f);
    EXPECT_FLOAT_EQ(result.data[2], 0.0f);
    EXPECT_FLOAT_EQ(result.data[3], 0.0f);
    EXPECT_FLOAT_EQ(result.data[4], 0.0f);
    EXPECT_FLOAT_EQ(result.data[5], 0.0f);
    EXPECT_FLOAT_EQ(result.data[6], 0.0f);
    EXPECT_FLOAT_EQ(result.data[7], 0.0f);
    EXPECT_FLOAT_EQ(result.data[8], 0.0f);
    EXPECT_FLOAT_EQ(result.data[9], 0.0f);
    EXPECT_FLOAT_EQ(result.data[10], 0.0f);
    EXPECT_FLOAT_EQ(result.data[11], 0.0f);
    EXPECT_FLOAT_EQ(result.data[12], 0.0f);
    EXPECT_FLOAT_EQ(result.data[13], 0.0f);
    EXPECT_FLOAT_EQ(result.data[14], 0.0f);
    EXPECT_FLOAT_EQ(result.data[15], 0.0f);
}

TEST_F(Matrix4x4Test, HandlesMultiplication)
{
    Pulsarion::Math::Mat4 m1;
    Pulsarion::Math::Mat4 m2;

    auto result = m1 * m2;
    std::cout << m1.ToString() << std::endl;
    std::cout << m2.ToString() << std::endl;
    std::cout << result.ToString() << std::endl;
    EXPECT_FLOAT_EQ(result.data[0], 1.0f);
    EXPECT_FLOAT_EQ(result.data[1], 0.0f);
    EXPECT_FLOAT_EQ(result.data[2], 0.0f);
    EXPECT_FLOAT_EQ(result.data[3], 0.0f);
    EXPECT_FLOAT_EQ(result.data[4], 0.0f);
    EXPECT_FLOAT_EQ(result.data[5], 1.0f);
    EXPECT_FLOAT_EQ(result.data[6], 0.0f);
    EXPECT_FLOAT_EQ(result.data[7], 0.0f);
    EXPECT_FLOAT_EQ(result.data[8], 0.0f);
    EXPECT_FLOAT_EQ(result.data[9], 0.0f);
    EXPECT_FLOAT_EQ(result.data[10], 1.0f);
    EXPECT_FLOAT_EQ(result.data[11], 0.0f);
    EXPECT_FLOAT_EQ(result.data[12], 0.0f);
    EXPECT_FLOAT_EQ(result.data[13], 0.0f);
    EXPECT_FLOAT_EQ(result.data[14], 0.0f);
    EXPECT_FLOAT_EQ(result.data[15], 1.0f);

    m1 = Pulsarion::Math::Mat4({ 1.0f, 2.0f, 3.0f, 4.0f,
                                 5.0f, 6.0f, 7.0f, 8.0f,
                                 9.0f, 10.0f, 11.0f, 12.0f,
                                 13.0f, 14.0f, 15.0f, 16.0f });

    m2 = Pulsarion::Math::Mat4({ 1.0f, 2.0f, 3.0f, 4.0f,
                                 5.0f, 6.0f, 7.0f, 8.0f,
                                 9.0f, 10.0f, 11.0f, 12.0f,
                                 13.0f, 14.0f, 15.0f, 16.0f });

    result = m1 * m2;
    std::cout << m1.ToString() << std::endl;
    std::cout << m2.ToString() << std::endl;
    std::cout << result.ToString() << std::endl;
    EXPECT_FLOAT_EQ(result.data[0], 90.0f);
    EXPECT_FLOAT_EQ(result.data[1], 100.0f);
    EXPECT_FLOAT_EQ(result.data[2], 110.0f);
    EXPECT_FLOAT_EQ(result.data[3], 120.0f);
    EXPECT_FLOAT_EQ(result.data[4], 202.0f);
    EXPECT_FLOAT_EQ(result.data[5], 228.0f);
    EXPECT_FLOAT_EQ(result.data[6], 254.0f);
    EXPECT_FLOAT_EQ(result.data[7], 280.0f);
    EXPECT_FLOAT_EQ(result.data[8], 314.0f);
    EXPECT_FLOAT_EQ(result.data[9], 356.0f);
    EXPECT_FLOAT_EQ(result.data[10], 398.0f);
    EXPECT_FLOAT_EQ(result.data[11], 440.0f);
    EXPECT_FLOAT_EQ(result.data[12], 426.0f);
    EXPECT_FLOAT_EQ(result.data[13], 484.0f);
    EXPECT_FLOAT_EQ(result.data[14], 542.0f);
    EXPECT_FLOAT_EQ(result.data[15], 600.0f);
}