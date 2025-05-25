//
// pch.h
//

#pragma once
#include "gtest/gtest.h"
#include "../GarbageCollector/TMem.h"
//#include "../GarbageCollector/TMem.cpp"
class MemorySetUp : public testing::Test
{

protected:
    void SetUp() override
    {
        for (int i = 5; i < 10; i++) tree.Insert(i);
        for (int i = 4; i >= 0; i--) tree.Insert(i);
    }
    void TearDown() override
    {
        TNode::Clear();
    }
    static void TearDownTestSuite()
    {

    }
public:
    static void SetUpTestSuite()
    {
        TNode::InitMem(20);
    }
    TTree tree;
};

