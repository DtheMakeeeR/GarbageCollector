#pragma once
#include <stack>
#include <iostream>
enum Status
{
	garbage,
	node,
	empty
};
using namespace std;
typedef int TKey;

struct TNode;
class TTree {
	TNode* pRoot, * pCurr, * pPrev;
	stack<TNode*> st;
	int level;
	void PrintRec(ostream& os, TNode* p);
public:
	void PrintTree(ostream& os);
	bool Find(TKey key);
	void Insert(TKey key);
	void Delete(TKey key);
	void Reset();
	void GoNext();
	bool IsEnd() { return st.empty(); }
	TNode& GetCurr() { return *pCurr; }
};
struct TMem
{
	TNode* pFirst, * pLast, * pFree;
};
struct TNode
{
	TKey key;
	TNode* pLeft, * pRight;
	Status status;
	static TMem memory;
	static void InitMem(int size = 100);
	static void ClearMem(TTree* t);
	static void PrintFree(ostream& os);
public:
	TNode(TKey k) : key(k), pLeft(nullptr), pRight(nullptr), status(Status::empty) {}
	void* operator new(size_t s);
	void operator delete(void* p);
};
