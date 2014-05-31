#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
#include "plays.h"

using namespace std;

struct Node
{
	Plays data;
	Node *Nxt,*Prv;
	Node(Plays y)
	{
		data = y;
		Nxt = Prv = NULL;
	}
};

class doublylinkedlist
{
public:
	void print(int n)
	{
		iterator = front;
		for (int l = 0; l != n; ++l)
		{
			if (iterator->data.returndesc() == "Null")
				iteratorInc();
			cout << iterator->data.returndesc() << " " << iterator->data.returnMin() << " " << iterator->data.returnOff() << " " <<
				iterator->data.returnDeff() << " " << iterator->data.returnTogo() << " " << iterator->data.returnydline() << " " <<
				endl;
			iteratorInc();
		}
	}

	void iteratorInc()
	{
		if (iterator == back)
			iterator = NULL;
		else iterator = iterator->Nxt;
	}
	void iteratorDec()
	{
		if (iterator == front)
			iterator = NULL;

		else iterator = iterator->Prv;
	}
	void iteratorDEL()
	{
		iterator->Prv->Nxt = iterator->Nxt;
		iterator->Nxt->Prv = iterator->Prv;
	}
	void iteratorM2F()
	{
		iteratorDEL();
		front->Nxt->Prv = iterator;
		iterator->Prv = front;
		iterator->Nxt = front->Prv;
		front->Nxt = iterator;
	}
	Node *front,* back, *iterator;
	doublylinkedlist()
	{
		front = NULL;
		back = NULL;
	}
	void storeback(Plays entered)
	{
		Node *n = new Node(entered);
		n->data = entered;
			if( back == NULL)
			{
				front = n;
				back = n;
			}
			else
			{
				back->Nxt = n;
				n->Prv = back;
				back = n;
			}
	}
};
#endif