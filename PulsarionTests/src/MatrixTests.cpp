#include <gtest/gtest.h>
#include <PulsarionMath/Math.hpp>

class Matrix4x4Test : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }
};

TEST_F(Matrix4x4Test, HandlesIdentity)
{
    Pulsarion::Mat4 m1;
    EXPECT_FLOAT_EQ(m1.data[0], 1.0f);
    EXPECT_FLOAT_EQ(m1.data[1], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[2], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[3], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[4], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[5], 1.0f);
    EXPECT_FLOAT_EQ(m1.data[6], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[7], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[8], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[9], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[10], 1.0f);
    EXPECT_FLOAT_EQ(m1.data[11], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[12], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[13], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[14], 0.0f);
    EXPECT_FLOAT_EQ(m1.data[15], 1.0f);

    // Double
    Pulsarion::Mat4d m2;
    EXPECT_FLOAT_EQ(m2.data[0], 1.0);
    EXPECT_FLOAT_EQ(m2.data[1], 0.0);
    EXPECT_FLOAT_EQ(m2.data[2], 0.0);
    EXPECT_FLOAT_EQ(m2.data[3], 0.0);
    EXPECT_FLOAT_EQ(m2.data[4], 0.0);
    EXPECT_FLOAT_EQ(m2.data[5], 1.0);
    EXPECT_FLOAT_EQ(m2.data[6], 0.0);
    EXPECT_FLOAT_EQ(m2.data[7], 0.0);
    EXPECT_FLOAT_EQ(m2.data[8], 0.0);
    EXPECT_FLOAT_EQ(m2.data[9], 0.0);
    EXPECT_FLOAT_EQ(m2.data[10], 1.0);
    EXPECT_FLOAT_EQ(m2.data[11], 0.0);
    EXPECT_FLOAT_EQ(m2.data[12], 0.0);
    EXPECT_FLOAT_EQ(m2.data[13], 0.0);
    EXPECT_FLOAT_EQ(m2.data[14], 0.0);
    EXPECT_FLOAT_EQ(m2.data[15], 1.0);

    Pulsarion::Mat4ld m3;
    EXPECT_FLOAT_EQ(m3.data[0], 1.0);
    EXPECT_FLOAT_EQ(m3.data[1], 0.0);
    EXPECT_FLOAT_EQ(m3.data[2], 0.0);
    EXPECT_FLOAT_EQ(m3.data[3], 0.0);
    EXPECT_FLOAT_EQ(m3.data[4], 0.0);
    EXPECT_FLOAT_EQ(m3.data[5], 1.0);
    EXPECT_FLOAT_EQ(m3.data[6], 0.0);
    EXPECT_FLOAT_EQ(m3.data[7], 0.0);
    EXPECT_FLOAT_EQ(m3.data[8], 0.0);
    EXPECT_FLOAT_EQ(m3.data[9], 0.0);
    EXPECT_FLOAT_EQ(m3.data[10], 1.0);
    EXPECT_FLOAT_EQ(m3.data[11], 0.0);
    EXPECT_FLOAT_EQ(m3.data[12], 0.0);
    EXPECT_FLOAT_EQ(m3.data[13], 0.0);
    EXPECT_FLOAT_EQ(m3.data[14], 0.0);
    EXPECT_FLOAT_EQ(m3.data[15], 1.0);
}

TEST_F(Matrix4x4Test, HandlesAddition)
{
    Pulsarion::Mat4 m1;
    Pulsarion::Mat4 m2;
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

    Pulsarion::Mat4d m3;
    Pulsarion::Mat4d m4;
    auto result2 = m3 + m4;
    EXPECT_FLOAT_EQ(result2.data[0], 2.0);
    EXPECT_FLOAT_EQ(result2.data[1], 0.0);
    EXPECT_FLOAT_EQ(result2.data[2], 0.0);
    EXPECT_FLOAT_EQ(result2.data[3], 0.0);
    EXPECT_FLOAT_EQ(result2.data[4], 0.0);
    EXPECT_FLOAT_EQ(result2.data[5], 2.0);
    EXPECT_FLOAT_EQ(result2.data[6], 0.0);
    EXPECT_FLOAT_EQ(result2.data[7], 0.0);
    EXPECT_FLOAT_EQ(result2.data[8], 0.0);
    EXPECT_FLOAT_EQ(result2.data[9], 0.0);
    EXPECT_FLOAT_EQ(result2.data[10], 2.0);
    EXPECT_FLOAT_EQ(result2.data[11], 0.0);
    EXPECT_FLOAT_EQ(result2.data[12], 0.0);
    EXPECT_FLOAT_EQ(result2.data[13], 0.0);
    EXPECT_FLOAT_EQ(result2.data[14], 0.0);
    EXPECT_FLOAT_EQ(result2.data[15], 2.0);

    Pulsarion::Mat4ld m5;
    Pulsarion::Mat4ld m6;
    auto result3 = m5 + m6;
    EXPECT_FLOAT_EQ(result3.data[0], 2.0);
    EXPECT_FLOAT_EQ(result3.data[1], 0.0);
    EXPECT_FLOAT_EQ(result3.data[2], 0.0);
    EXPECT_FLOAT_EQ(result3.data[3], 0.0);
    EXPECT_FLOAT_EQ(result3.data[4], 0.0);
    EXPECT_FLOAT_EQ(result3.data[5], 2.0);
    EXPECT_FLOAT_EQ(result3.data[6], 0.0);
    EXPECT_FLOAT_EQ(result3.data[7], 0.0);
    EXPECT_FLOAT_EQ(result3.data[8], 0.0);
    EXPECT_FLOAT_EQ(result3.data[9], 0.0);
    EXPECT_FLOAT_EQ(result3.data[10], 2.0);
    EXPECT_FLOAT_EQ(result3.data[11], 0.0);
    EXPECT_FLOAT_EQ(result3.data[12], 0.0);
    EXPECT_FLOAT_EQ(result3.data[13], 0.0);
    EXPECT_FLOAT_EQ(result3.data[14], 0.0);
    EXPECT_FLOAT_EQ(result3.data[15], 2.0);
}

TEST_F(Matrix4x4Test, HandlesSubtraction)
{
    Pulsarion::Mat4 m1;
    Pulsarion::Mat4 m2;
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

    Pulsarion::Mat4d m3;
    Pulsarion::Mat4d m4;
    auto result2 = m3 - m4;
    EXPECT_FLOAT_EQ(result2.data[0], 0.0);
    EXPECT_FLOAT_EQ(result2.data[1], 0.0);
    EXPECT_FLOAT_EQ(result2.data[2], 0.0);
    EXPECT_FLOAT_EQ(result2.data[3], 0.0);
    EXPECT_FLOAT_EQ(result2.data[4], 0.0);
    EXPECT_FLOAT_EQ(result2.data[5], 0.0);
    EXPECT_FLOAT_EQ(result2.data[6], 0.0);
    EXPECT_FLOAT_EQ(result2.data[7], 0.0);
    EXPECT_FLOAT_EQ(result2.data[8], 0.0);
    EXPECT_FLOAT_EQ(result2.data[9], 0.0);
    EXPECT_FLOAT_EQ(result2.data[10], 0.0);
    EXPECT_FLOAT_EQ(result2.data[11], 0.0);
    EXPECT_FLOAT_EQ(result2.data[12], 0.0);
    EXPECT_FLOAT_EQ(result2.data[13], 0.0);
    EXPECT_FLOAT_EQ(result2.data[14], 0.0);
    EXPECT_FLOAT_EQ(result2.data[15], 0.0);

    Pulsarion::Mat4d m5;
    Pulsarion::Mat4d m6;
    auto result3 = m5 - m6;
    EXPECT_FLOAT_EQ(result3.data[0], 0.0);
    EXPECT_FLOAT_EQ(result3.data[1], 0.0);
    EXPECT_FLOAT_EQ(result3.data[2], 0.0);
    EXPECT_FLOAT_EQ(result3.data[3], 0.0);
    EXPECT_FLOAT_EQ(result3.data[4], 0.0);
    EXPECT_FLOAT_EQ(result3.data[5], 0.0);
    EXPECT_FLOAT_EQ(result3.data[6], 0.0);
    EXPECT_FLOAT_EQ(result3.data[7], 0.0);
    EXPECT_FLOAT_EQ(result3.data[8], 0.0);
    EXPECT_FLOAT_EQ(result3.data[9], 0.0);
    EXPECT_FLOAT_EQ(result3.data[10], 0.0);
    EXPECT_FLOAT_EQ(result3.data[11], 0.0);
    EXPECT_FLOAT_EQ(result3.data[12], 0.0);
    EXPECT_FLOAT_EQ(result3.data[13], 0.0);
    EXPECT_FLOAT_EQ(result3.data[14], 0.0);
    EXPECT_FLOAT_EQ(result3.data[15], 0.0);
}

TEST_F(Matrix4x4Test, HandlesMultiplication)
{
    Pulsarion::Mat4 m1;
    Pulsarion::Mat4 m2;

    m2 = Pulsarion::Mat4({ 1.0f, 2.0f, 3.0f, 4.0f,
                                 5.0f, 6.0f, 7.0f, 8.0f,
                                 9.0f, 10.0f, 11.0f, 12.0f,
                                 13.0f, 14.0f, 15.0f, 16.0f });
    auto result = m1 * m2;
    EXPECT_FLOAT_EQ(result.data[0], 1.0f);
    EXPECT_FLOAT_EQ(result.data[1], 2.0f);
    EXPECT_FLOAT_EQ(result.data[2], 3.0f);
    EXPECT_FLOAT_EQ(result.data[3], 4.0f);
    EXPECT_FLOAT_EQ(result.data[4], 5.0f);
    EXPECT_FLOAT_EQ(result.data[5], 6.0f);
    EXPECT_FLOAT_EQ(result.data[6], 7.0f);
    EXPECT_FLOAT_EQ(result.data[7], 8.0f);
    EXPECT_FLOAT_EQ(result.data[8], 9.0f);
    EXPECT_FLOAT_EQ(result.data[9], 10.0f);
    EXPECT_FLOAT_EQ(result.data[10], 11.0f);
    EXPECT_FLOAT_EQ(result.data[11], 12.0f);
    EXPECT_FLOAT_EQ(result.data[12], 13.0f);
    EXPECT_FLOAT_EQ(result.data[13], 14.0f);
    EXPECT_FLOAT_EQ(result.data[14], 15.0f);
    EXPECT_FLOAT_EQ(result.data[15], 16.0f);

    m1 = Pulsarion::Mat4({ 1.0f, 2.0f, 3.0f, 4.0f,
                                 5.0f, 6.0f, 7.0f, 8.0f,
                                 9.0f, 10.0f, 11.0f, 12.0f,
                                 13.0f, 14.0f, 15.0f, 16.0f });

    result = m1 * m2;
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

    Pulsarion::Mat4d m3;
    Pulsarion::Mat4d m4;

    m4 = Pulsarion::Mat4d({ 1.0, 2.0, 3.0, 4.0,
                                 5.0, 6.0, 7.0, 8.0,
                                 9.0, 10.0, 11.0, 12.0,
                                 13.0, 14.0, 15.0, 16.0 });
    auto result2 = m3 * m4;
    EXPECT_FLOAT_EQ(result2.data[0], 1.0);
    EXPECT_FLOAT_EQ(result2.data[1], 2.0);
    EXPECT_FLOAT_EQ(result2.data[2], 3.0);
    EXPECT_FLOAT_EQ(result2.data[3], 4.0);
    EXPECT_FLOAT_EQ(result2.data[4], 5.0);
    EXPECT_FLOAT_EQ(result2.data[5], 6.0);
    EXPECT_FLOAT_EQ(result2.data[6], 7.0);
    EXPECT_FLOAT_EQ(result2.data[7], 8.0);
    EXPECT_FLOAT_EQ(result2.data[8], 9.0);
    EXPECT_FLOAT_EQ(result2.data[9], 10.0);
    EXPECT_FLOAT_EQ(result2.data[10], 11.0);
    EXPECT_FLOAT_EQ(result2.data[11], 12.0);
    EXPECT_FLOAT_EQ(result2.data[12], 13.0);
    EXPECT_FLOAT_EQ(result2.data[13], 14.0);
    EXPECT_FLOAT_EQ(result2.data[14], 15.0);
    EXPECT_FLOAT_EQ(result2.data[15], 16.0);

    m3 = Pulsarion::Mat4d({ 1.0, 2.0, 3.0, 4.0,
                                 5.0, 6.0, 7.0, 8.0,
                                 9.0, 10.0, 11.0, 12.0,
                                 13.0, 14.0, 15.0, 16.0 });

    result2 = m3 * m4;
    EXPECT_FLOAT_EQ(result2.data[0], 90.0);
    EXPECT_FLOAT_EQ(result2.data[1], 100.0);
    EXPECT_FLOAT_EQ(result2.data[2], 110.0);
    EXPECT_FLOAT_EQ(result2.data[3], 120.0);
    EXPECT_FLOAT_EQ(result2.data[4], 202.0);
    EXPECT_FLOAT_EQ(result2.data[5], 228.0);
    EXPECT_FLOAT_EQ(result2.data[6], 254.0);
    EXPECT_FLOAT_EQ(result2.data[7], 280.0);
    EXPECT_FLOAT_EQ(result2.data[8], 314.0);
    EXPECT_FLOAT_EQ(result2.data[9], 356.0);
    EXPECT_FLOAT_EQ(result2.data[10], 398.0);
    EXPECT_FLOAT_EQ(result2.data[11], 440.0);
    EXPECT_FLOAT_EQ(result2.data[12], 426.0);
    EXPECT_FLOAT_EQ(result2.data[13], 484.0);
    EXPECT_FLOAT_EQ(result2.data[14], 542.0);
    EXPECT_FLOAT_EQ(result2.data[15], 600.0);

    Pulsarion::Mat4ld m5;
    Pulsarion::Mat4ld m6;

    m6 = Pulsarion::Mat4ld({ 1.0, 2.0, 3.0, 4.0,
                                 5.0, 6.0, 7.0, 8.0,
                                 9.0, 10.0, 11.0, 12.0,
                                 13.0, 14.0, 15.0, 16.0 });
    auto result3 = m5 * m6;
    EXPECT_FLOAT_EQ(result3.data[0], 1.0);
    EXPECT_FLOAT_EQ(result3.data[1], 2.0);
    EXPECT_FLOAT_EQ(result3.data[2], 3.0);
    EXPECT_FLOAT_EQ(result3.data[3], 4.0);
    EXPECT_FLOAT_EQ(result3.data[4], 5.0);
    EXPECT_FLOAT_EQ(result3.data[5], 6.0);
    EXPECT_FLOAT_EQ(result3.data[6], 7.0);
    EXPECT_FLOAT_EQ(result3.data[7], 8.0);
    EXPECT_FLOAT_EQ(result3.data[8], 9.0);
    EXPECT_FLOAT_EQ(result3.data[9], 10.0);
    EXPECT_FLOAT_EQ(result3.data[10], 11.0);
    EXPECT_FLOAT_EQ(result3.data[11], 12.0);
    EXPECT_FLOAT_EQ(result3.data[12], 13.0);
    EXPECT_FLOAT_EQ(result3.data[13], 14.0);
    EXPECT_FLOAT_EQ(result3.data[14], 15.0);
    EXPECT_FLOAT_EQ(result3.data[15], 16.0);

    m5 = Pulsarion::Mat4ld({ 1.0, 2.0, 3.0, 4.0,
                                 5.0, 6.0, 7.0, 8.0,
                                 9.0, 10.0, 11.0, 12.0,
                                 13.0, 14.0, 15.0, 16.0 });

    result3 = m5 * m6;
    EXPECT_FLOAT_EQ(result3.data[0], 90.0);
    EXPECT_FLOAT_EQ(result3.data[1], 100.0);
    EXPECT_FLOAT_EQ(result3.data[2], 110.0);
    EXPECT_FLOAT_EQ(result3.data[3], 120.0);
    EXPECT_FLOAT_EQ(result3.data[4], 202.0);
    EXPECT_FLOAT_EQ(result3.data[5], 228.0);
    EXPECT_FLOAT_EQ(result3.data[6], 254.0);
    EXPECT_FLOAT_EQ(result3.data[7], 280.0);
    EXPECT_FLOAT_EQ(result3.data[8], 314.0);
    EXPECT_FLOAT_EQ(result3.data[9], 356.0);
    EXPECT_FLOAT_EQ(result3.data[10], 398.0);
    EXPECT_FLOAT_EQ(result3.data[11], 440.0);
    EXPECT_FLOAT_EQ(result3.data[12], 426.0);
    EXPECT_FLOAT_EQ(result3.data[13], 484.0);
    EXPECT_FLOAT_EQ(result3.data[14], 542.0);
    EXPECT_FLOAT_EQ(result3.data[15], 600.0);
}

TEST_F(Matrix4x4Test, HandlesVectorMul)
{
    Pulsarion::float4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    auto m1 = Pulsarion::Mat4({ 1.0f, 2.0f, 3.0f, 4.0f,
                                 5.0f, 6.0f, 7.0f, 8.0f,
                                 9.0f, 10.0f, 11.0f, 12.0f,
                                 13.0f, 14.0f, 15.0f, 16.0f });

    Pulsarion::float4 result = m1 * v1;
    EXPECT_FLOAT_EQ(result.x, 30.0f);
    EXPECT_FLOAT_EQ(result.y, 70.0f);
    EXPECT_FLOAT_EQ(result.z, 110.0f);
}