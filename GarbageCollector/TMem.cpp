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
		memory.pFirst[i].status = Status::empty;
		memory.pFirst[i].pLeft = memory.pFirst + i + 1;
	}
	memory.pLast->key = -1;
	memory.pLast->status = Status::empty;
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

void TNode::PrintGarbage(ostream& os)
{
	TNode* tmp = memory.pFirst;
	os << endl;
	while (tmp <= memory.pLast)
	{
		if (tmp->status == Status::garbage) os << tmp->key << " ";
		tmp++;
	}
	os << endl;
}

void TNode::PrintEmpty(ostream& os)
{
	TNode* tmp = memory.pFirst;
	os << endl;
	while (tmp <= memory.pLast)
	{
		if (tmp->status == Status::empty) os << tmp->key << " ";
		tmp++;
	}
	os << endl;
}

void TNode::PrintNode(ostream& os)
{
	TNode* tmp = memory.pFirst;
	os << endl;
	while (tmp <= memory.pLast)
	{
		if (tmp->status == Status::node) os << tmp->key << " ";
		tmp++;
	}
	os << endl;
}

string TNode::CreatePrint()
{
	TNode* tmp = memory.pFirst;
	stringstream ss;
	while (tmp <= memory.pLast)
	{
		string add;
		switch (tmp->status)
		{
			case Status::node:
				ss << "\033[34m " << tmp->key << " ";
				break;
			case Status::garbage:
				ss << "\033[33m " << tmp->key << " ";
				break;
			case Status::empty:
				ss << "\033[0m " << tmp->key << " ";
				break;
		}
		tmp++;
	}
	ss << "\033[0m " << endl;
	return ss.str();
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
	//tmp->status = Status::empty;
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
	tmp->status = Status::node;
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
