#pragma once
#include <stack>
#include <sstream>
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
	TTree() : pRoot(nullptr), pCurr(nullptr), pPrev(nullptr), st() {}
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
	int size;
};
struct TNode
{
	TKey key;
	TNode* pLeft, * pRight;
	Status status;
	static TMem memory;
	static void InitMem(int sz = 100);
	static void ClearMem(TTree* t);
	static void PrintGarbage(ostream& os);
	static void PrintEmpty(ostream& os);
	static void PrintNode(ostream& os);
	static TNode* Find(TKey key);
	static void Clear();
	static string CreatePrint();
public:
	TNode(TKey k) : key(k), pLeft(nullptr), pRight(nullptr), status(Status::empty) {}
	void* operator new(size_t s);
	void operator delete(void* p);
};
