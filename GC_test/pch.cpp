//
// pch.cpp
//

#include "pch.h"
//#include "../GarbageCollector/TMem.h"
int main(int argc, char** argv) {
    TNode::InitMem(20);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}