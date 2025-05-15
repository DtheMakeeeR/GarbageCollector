#pragma once
typedef int TKey;

struct TTree;
struct TNode;

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
	TNode(TKey k) : key(k), pLeft(nullptr), pRight(nullptr), isGarbage(false) {}
	void* operator new(size_t s);
	void operator delete(void* p);
};
