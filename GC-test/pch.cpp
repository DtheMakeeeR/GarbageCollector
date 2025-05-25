//
// pch.cpp
//
#include "pch.h"

int main(int argc, char** argv) {
    MemorySetUp::SetUpTestSuite();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



