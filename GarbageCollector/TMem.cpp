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
		memory.pFirst[i].key = -1;
		memory.pFirst[i].pLeft = memory.pFirst + i + 1;
	}
	memory.pLast->key = -1;
	memory.pLast->pLeft = nullptr;
}

void TNode::ClearMem(TTree* t)
{
	TNode* tmp = memory.pFirst;
	while (tmp <= memory.pLast)
	{
		tmp->status = Status::garbage;
		tmp++;
	}
	tmp = memory.pFree;
	while (tmp)
	{
		tmp->status = Status::empty;
		tmp = tmp->pLeft;
	}
	for(t->Reset();!t->IsEnd();t->GoNext())
	{
		t->GetCurr().status = Status::node;
	}
	tmp = memory.pFirst;
	while (tmp <= memory.pLast)
	{
		if (tmp->status == garbage) delete tmp;
		tmp++;
	}
}

void TNode::PrintFree(ostream& os)
{
	TNode* tmp = memory.pFirst;
	os << endl;
	while (tmp <= memory.pLast)
	{
		if (tmp->key>0 && tmp->status) os << tmp->key << " ";
		tmp++;
	}
	os << endl;
}

void* TNode::operator new(size_t s)
{
	TNode* res = memory.pFree;
	if (res == nullptr) return nullptr;
	memory.pFree = memory.pFree->pLeft;
	//res->status = Status::node;
	return res;
}

void TNode::operator delete(void* p)
{
	TNode* tmp = (TNode*)p;
	tmp->pLeft = memory.pFree;
	memory.pFree = tmp;
	//tmp->status = Status::garbage;
}

void TTree::PrintRec(ostream& os, TNode* p)
{
	if (p == nullptr) {
		return;
	}
	for (int i = 0; i < level; i++) {
		os << " ";
	}
	os << level << " level: " << p->key << endl;
	level++;
	PrintRec(os, p->pRight);
	PrintRec(os, p->pLeft);
	level--;
}

void TTree::PrintTree(ostream& os)
{
	level = 0;
	PrintRec(os, pRoot);
}

bool TTree::Find(TKey key)
{
	pCurr = pRoot;
	while (pCurr != nullptr) {
		if (key > pCurr->key) {
			pPrev = pCurr;
			pCurr = pCurr->pRight;
		}
		else if (key < pCurr->key) {
			pPrev = pCurr;
			pCurr = pCurr->pLeft;
		}
		else if (key == pCurr->key) {
			return true;
		}
	}
	pCurr = pPrev;
	return false;
}

void TTree::Insert(TKey key)
{
	if (Find(key)) throw - 1;
	TNode* tmp = new TNode(key);
	if (pCurr == nullptr) {
		pRoot = tmp;
	}
	else if (key > pCurr->key) {
		pCurr->pRight = tmp;
	}
	else if (key < pCurr->key) {
		pCurr->pLeft = tmp;
	}
}

void TTree::Delete(TKey key)
{
	if (!Find(key)) throw - 1;
	pCurr->status = Status::empty;
	if (pPrev == nullptr) delete pCurr;
	else if (pPrev->pLeft == pCurr)
	{
		pPrev->pLeft = nullptr;
		delete pCurr;
	}
	else
	{
		pPrev->pRight = nullptr;
		delete pCurr;
	}
}

void TTree::Reset()
{
	while (!st.empty()) st.pop();
	pCurr = pRoot;
	while (pCurr->pLeft != nullptr)
	{
		st.push(pCurr);
		pCurr = pCurr->pLeft;
	}
	st.push(pCurr);
}

void TTree::GoNext()
{
	st.pop();
	pCurr = pCurr->pRight;
	if (pCurr)
	{
		st.push(pCurr);
		while (pCurr->pLeft)
		{
			st.push(pCurr);
			pCurr = pCurr->pLeft;
		}
	}
	else if (!st.empty()) st.top();
}
