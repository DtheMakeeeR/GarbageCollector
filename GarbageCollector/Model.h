#pragma once
#include "TMem.h"
#include <vector>
class Model
{
	TTree tree;
	vector<string> input;
	void Split(string str);
	void Error(string msg);
	void Update();
public:
	Model(size_t s):tree(), input() { TNode::InitMem(s); }
	void Run();
};
