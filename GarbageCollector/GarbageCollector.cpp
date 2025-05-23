// GarbageCollector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TMem.h"
int main()
{
    TNode::InitMem(15);
    TTree tree;
	for (size_t i = 0; i < 10; i++)
	{
		tree.Insert(i);
	}
	tree.PrintTree(cout);
	tree.Delete(5);
	tree.PrintTree(cout);
	TNode::ClearMem(&tree);
	TNode::PrintFree(cout);
}


