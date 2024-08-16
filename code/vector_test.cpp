#include <gtest/gtest.h>
#include "vector.h"

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, SizeConstructor) {
    // Test for different sizes
    for (int i = 0; i <= 100; i += 10) {
        Vector<int> v(i, 10);

        // Check that the size is correct
        EXPECT_EQ(v.size(), i);

        // If the vector is not empty, check that all elements are initialized to the correct value
        if (i > 0) {
            for (int j = 0; j < i; ++j) {
                EXPECT_EQ(v[j], 10);
            }
        }
    }

    // Test with size 0 (empty vector)
    Vector<int> v_empty(0, 10);
    EXPECT_EQ(v_empty.size(), 0);
    EXPECT_EQ(v_empty.capacity(), 0);

    // Test with a larger size
    Vector<int> v_large(1000, 5);
    EXPECT_EQ(v_large.size(), 1000);

    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(v_large[i], 5);
    }
}

TEST(VectorTest, InitializerListConstructor) {
    Vector<int> v;
    
    // Empty initializer list
    v = {};
    EXPECT_EQ(v.size(), 0);

    // One element
    for (int i = 0; i < 5; i++) {
        v = {i};
        EXPECT_EQ(v.size(), 1);
        EXPECT_EQ(v[0], i);
    }

    // Five elements
    v = {1, 2, 3, 4, 5};
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, PushBack) {
    Vector<int> v;

    // Add elements and check size and contents
    for (int i = 1; i <= 100; i++) {
        v.push_back(i);
        EXPECT_EQ(v.size(), i);
        EXPECT_EQ(v[i - 1], i);  // Check that the last element added is correct
    }

    EXPECT_EQ(v.size(), 100);  // Final size check
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}