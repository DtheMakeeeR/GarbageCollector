#include "TMem.h"
TMem TNode::memory;
void TNode::InitMem(int size)
{
	memory.pFirst = (TNode*) new char[sizeof(TNode) * size];
	memory.pFree = memory.pFirst;
	memory.pLast = memory.pFirst + size - 1;
	TNode* curr = memory.pFirst;
	for (size_t i = 0; i < size-1; i++)
	{
		memory.pFirst[i].pLeft = memory.pFirst + i + 1;
		//curr->pLeft = curr+1;
		//curr++;
		//curr->key = -1;
	}
	memory.pLast->key = -1;
	memory.pLast->pLeft = nullptr;
}

void TNode::PrintFree()
{

}

void* TNode::operator new(size_t s)
{
	TNode* res = memory.pFree;
	if (res == nullptr) return nullptr;
	memory.pFree = memory.pFree->pLeft;
	return res;
}

void TNode::operator delete(void* p)
{
	TNode* tmp = (TNode*)p;
	tmp->pLeft = memory.pFree;
	memory.pFree = tmp;
}
