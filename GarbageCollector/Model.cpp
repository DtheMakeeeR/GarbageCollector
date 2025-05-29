#include "Model.h"

void Model::Split(string str)
{
	input.clear();
	stringstream ss(str);
	string tmp;
	while (ss >> tmp) input.push_back(tmp);
}

void Model::Error(string msg)
{
	cout << endl << "\033[31m" << msg << "\033[0m";
	getchar();
}

void Model::Update()
{
	system("cls");
	cout << TNode::CreatePrint();
}

void Model::Run()
{
	Update();
	while (true)
	{
		string s;
		cout << ">>";
		//cin.ignore();
		while (s == "")
		{
			getline(cin, s);
		}
		Split(s);
		string command = input[0];
		if (command == "insert")
		{
			try
			{
				int arg = stoi(input.at(1));
				tree.Insert(arg);
			}
			catch(...)
			{
				Error("Argument error");
			}
		}
		else if (command == "delete")
		{
			try
			{
				int arg = stoi(input.at(1));
				tree.Delete(arg);
			}
			catch (...)
			{
				Error("Argument error");
			}
		}
		else if (command == "print")
		{
			if (input.size() == 1) tree.PrintTree(cout);
			else if (input.at(1) == "garbage") TNode::PrintGarbage(cout);
			else if (input.at(1) == "empty") TNode::PrintEmpty(cout);
			else if (input.at(1) == "node") TNode::PrintNode(cout);
			else tree.PrintTree(cout);
			getchar();
		}
		else if (command == "clear")
		{
			TNode::ClearMem(&tree);
		}
		else if (command == "init")
		{
			for (size_t i = 21; i < 50; i+=5)
			{
				try
				{
					tree.Insert(i);
				}
				catch (...)
				{
					Error("insert error");
				}
			}
			for (int i = 17; i > 0; i-=5)
			{
				try
				{
					tree.Insert(i);
				}
				catch (...)
				{
					Error("insert error");
				}
			}
			for (size_t i = 4; i < 60; i += 5)
			{
				try
				{
					tree.Insert(i);
				}
				catch (...)
				{
					Error("insert error");
				}
			}
		}
		else
		{
			Error("Unknown command");
		}
		Update();
	}
}
