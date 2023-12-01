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

class Vector3DTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    static bool IsZeroVector(const Pulsarion::float3& vec) {
        return vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f;
    }
};

// Test for division by zero
TEST_F(Vector3DTest, HandlesDivisionByZero) {
    Pulsarion::float3 v(1.0f, 2.0f, 3.0f);
    auto result = v / 0.0f;
    EXPECT_TRUE(IsZeroVector(result));
}

// Test for normalization
TEST_F(Vector3DTest, HandlesNormalization) {
    std::vector<Pulsarion::float3> testVectors = {
        {1.0f, 2.0f, 0.0f}, {0.0f, 1.0f, 2.0f}, {3.0f, 4.0f, 5.0f}, {1e-6f, 0.0f, 0.0f}
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

TEST_F(Vector3DTest, HandlesAddition) {
    Pulsarion::float3 v1(1.0f, 2.0f, 3.0f);
    Pulsarion::float3 v2(4.0f, 5.0f, 6.0f);
    auto result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, 7.0f);
    EXPECT_FLOAT_EQ(result.z, 9.0f);
}


TEST_F(Vector3DTest, HandlesSubtraction) {
    Pulsarion::float3 v1(5.0f, 4.0f, 3.0f);
    Pulsarion::float3 v2(2.0f, 1.0f, 0.0f);
    auto result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}


TEST_F(Vector3DTest, HandlesDotProduct) {
    Pulsarion::float3 v1(1.0f, 2.0f, 3.0f);
    Pulsarion::float3 v2(4.0f, 5.0f, 6.0f);
    float result = v1.Dot(v2);
    EXPECT_FLOAT_EQ(result, 32.0f); // 1*4 + 2*5 + 3*6
}

TEST_F(Vector3DTest, HandlesCrossProduct) {
    Pulsarion::float3 v1(1.0f, 2.0f, 3.0f);
    Pulsarion::float3 v2(4.0f, 5.0f, 6.0f);
    Pulsarion::float3 result = v1.Cross(v2);
    EXPECT_FLOAT_EQ(result.x, -3.0f); // 2*6 - 3*5
    EXPECT_FLOAT_EQ(result.y, 6.0f); // 3*4 - 1*6
    EXPECT_FLOAT_EQ(result.z, -3.0f); // 1*5 - 2*4
}

TEST_F(Vector3DTest, HandlesScalarMultiplication) {
    Pulsarion::float3 v(2.0f, 3.0f, 4.0);
    float scalar = 2.0f;
    auto result = v * scalar;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
    EXPECT_FLOAT_EQ(result.z, 8.0f);
}

TEST_F(Vector3DTest, HandlesZeroVector) {
    Pulsarion::float3 v(0.0f, 0.0f, 0.0f);
    EXPECT_TRUE(IsZeroVector(v));
}


class Vector4DTest : public ::testing::Test {
protected:
    void SetUp() override {

    }

    static bool IsZeroVector(const Pulsarion::float4& vec) {
        return vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f && vec.w == 0.0f;
    }
};

// Test for division by zero
TEST_F(Vector4DTest, HandlesDivisionByZero) {
    Pulsarion::float4 v(1.0f, 2.0f, 3.0f, 4.0f);
    auto result = v / 0.0f;
    EXPECT_TRUE(IsZeroVector(result));
}

// Test for normalization
TEST_F(Vector4DTest, HandlesNormalization) {
    std::vector<Pulsarion::float4> testVectors = {
        {1.0f, 2.0f, 0.0f, 4.0f}, {0.0f, 1.0f, 2.0f, 3.0f}, {3.0f, 4.0f, 5.0f, 6.0f}, {1e-6f, 0.0f, 0.0f, 0.0f}
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

TEST_F(Vector4DTest, HandlesAddition) {
    Pulsarion::float4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    Pulsarion::float4 v2(5.0f, 6.0f, 7.0f, 8.0f);
    auto result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 6.0f);
    EXPECT_FLOAT_EQ(result.y, 8.0f);
    EXPECT_FLOAT_EQ(result.z, 10.0f);
    EXPECT_FLOAT_EQ(result.w, 12.0f);
}


TEST_F(Vector4DTest, HandlesSubtraction) {
    Pulsarion::float4 v1(8.0f, 7.0f, 6.0f, 5.0f);
    Pulsarion::float4 v2(4.0f, 3.0f, 2.0f, 1.0f);
    auto result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 4.0f);
    EXPECT_FLOAT_EQ(result.w, 4.0f);
}


TEST_F(Vector4DTest, HandlesDotProduct) {
    Pulsarion::float4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    Pulsarion::float4 v2(5.0f, 6.0f, 7.0f, 8.0f);
    float result = v1.Dot(v2);
    EXPECT_FLOAT_EQ(result, 70.0f); // 1*5 + 2*6 + 3*7 + 4*8
}

TEST_F(Vector4DTest, HandlesCrossProduct) {
    Pulsarion::float4 v1(1.0f, 2.0f, 3.0f);
    Pulsarion::float4 v2(4.0f, 5.0f, 6.0f);
    Pulsarion::float4 result = v1.Cross3D(v2); // Cross product is only defined for 3D vectors
    EXPECT_FLOAT_EQ(result.x, -3.0f); // 2*6 - 3*5
    EXPECT_FLOAT_EQ(result.y, 6.0f); // 3*4 - 1*6
    EXPECT_FLOAT_EQ(result.z, -3.0f); // 1*5 - 2*4
    EXPECT_FLOAT_EQ(result.w, 0.0f);
}

TEST_F(Vector4DTest, HandlesScalarMultiplication) {
    Pulsarion::float4 v(2.0f, 3.0f, 4.0, 5.0f);
    float scalar = 2.0f;
    auto result = v * scalar;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
    EXPECT_FLOAT_EQ(result.z, 8.0f);
    EXPECT_FLOAT_EQ(result.w, 10.0f);
}

TEST_F(Vector4DTest, HandlesZeroVector) {
    Pulsarion::float4 v(0.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_TRUE(IsZeroVector(v));
}

