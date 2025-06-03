// GarbageCollector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Model.h"
#include "TMem.h"
int main()
{
	cout << "Input memory size(>=40)" << endl;
	string input;
	cin >> input;
	int size = 0;
	try { size = stoi(input); }
	catch (...) {}
	if (size < 40) size = 40;
	Model m(size);
	m.Run();
    /*TNode::InitMem(15);
    TTree tree;
	cout << "\033[31m red \033[33m yellow  \033[34m blue \033[0m white" << endl;
	for (size_t i = 0; i < 10; i++)
	{
		tree.Insert(i);
	}
	tree.PrintTree(cout);
	tree.Delete(5);
	tree.PrintTree(cout);
	TNode::ClearMem(&tree);
	TNode::PrintFree(cout);*/
}


