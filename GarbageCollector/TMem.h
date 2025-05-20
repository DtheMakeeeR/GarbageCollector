#pragma once
#include <stack>
using namespace std;
typedef int TKey;

struct TNode;
class TTree {
	TNode* pRoot, * pCurr, * pPrev;
	stack<TNode*> st;
	int level;
	void printRec(TNode* p);
public:
	void printTree();
	bool Find(TKey k);
	void Insert(TKey k);
	void Delete(TKey k);
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
	bool isGarbage;
	static TMem memory;
	static void InitMem(int size = 100);
	static void ClearMem(TTree* t);
	static void PrintFree();
public:
	TNode(TKey k) : key(k), pLeft(nullptr), pRight(nullptr), isGarbage(true) {}
	void* operator new(size_t s);
	void operator delete(void* p);
};
