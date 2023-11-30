#include <gtest/gtest.h>
#include <PulsarionMath/Math.hpp>

class Vector2DTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    static bool IsZeroVector(const Pulsarion::float2& vec) {
        return vec.x == 0.0f && vec.y == 0.0f;
    }
};

// Test for division by zero
TEST_F(Vector2DTest, HandlesDivisionByZero) {
    Pulsarion::float2 v(1.0f, 2.0f);
    auto result = v / 0.0f;
    EXPECT_TRUE(IsZeroVector(result));
}

// Test for normalization
TEST_F(Vector2DTest, HandlesNormalization) {
    std::vector<Pulsarion::float2> testVectors = {
        {1.0f, 0.0f}, {0.0f, 1.0f}, {3.0f, 4.0f}, {1e-6f, 0.0f}
    };

    for (const auto& vec : testVectors) {
        auto normalizedVec = vec.Normalized();
        if (!IsZeroVector(vec)) {
            float magnitude = normalizedVec.Magnitude();
            EXPECT_NEAR(magnitude, 1.0f, 1e-6f);
        } else {
            EXPECT_TRUE(IsZeroVector(normalizedVec));
        }
    }
}

TEST_F(Vector2DTest, HandlesAddition) {
    Pulsarion::float2 v1(1.0f, 2.0f);
    Pulsarion::float2 v2(3.0f, 4.0f);
    auto result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}


TEST_F(Vector2DTest, HandlesSubtraction) {
    Pulsarion::float2 v1(5.0f, 4.0f);
    Pulsarion::float2 v2(1.0f, 2.0f);
    auto result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
}


TEST_F(Vector2DTest, HandlesDotProduct) {
    Pulsarion::float2 v1(1.0f, 2.0f);
    Pulsarion::float2 v2(3.0f, 4.0f);
    float result = v1.Dot(v2);
    EXPECT_FLOAT_EQ(result, 11.0f); // 1*3 + 2*4
}

TEST_F(Vector2DTest, HandlesCrossProduct) {
    Pulsarion::float2 v1(1.0f, 2.0f);
    Pulsarion::float2 v2(3.0f, 4.0f);
    float result = v1.Cross(v2);
    EXPECT_FLOAT_EQ(result, -2.0f); // 1*4 - 2*3
}

TEST_F(Vector2DTest, HandlesScalarMultiplication) {
    Pulsarion::float2 v(2.0f, 3.0f);
    float scalar = 2.0f;
    auto result = v * scalar;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST_F(Vector2DTest, HandlesZeroVector) {
    Pulsarion::float2 v(0.0f, 0.0f);
    EXPECT_TRUE(IsZeroVector(v));
}

