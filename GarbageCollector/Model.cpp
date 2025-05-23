#include "TMem.h"
class Model
{
	TTree tree;
public:
	Model(size_t s) { TNode::InitMem(s); }
};