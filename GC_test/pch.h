//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#include "../GarbageCollector/TMem.cpp"
#include "../GarbageCollector/TMem.h"
TEST(GarbageCollector, ) {
	TNode::Clear();
	TTree tree;
	for (int i = 5; i < 10; i++)
	{
		tree.Insert(i);
	}
	for (int i = 4; i >= 0; i--)
	{
		tree.Insert(i);
	}

	for (int i = 0; i < 10; i++) EXPECT_EQ(tree.Find(i), true);
}