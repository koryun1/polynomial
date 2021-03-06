#pragma once
#include "monom.h"

class cyclelist : public monom

{
private: 
	monom * first; 
public:
#pragma region constructors
	cyclelist()
	{
		first = new monom();
		first->setNext(first);
	};
	cyclelist(const cyclelist & tmp)
	{
		first = new monom();
		first->setNext(first);

		monom *cur1 = tmp.first->getNext(), *cur2 = first;

		while (cur1 != tmp.first)
		{
			monom *m = new monom(*cur1);
			cur2->setNext(m);
			cur1 = cur1->getNext();
			cur2 = m;
		}
		cur2->setNext(first);

	};
#pragma endregion
#pragma region add
	void addMonom(monom * tmp)
	{
		monom * prev = first;
		monom * cur = first->getNext();
		while (cur->getSv() > tmp->getSv())
		{
			prev = cur;
			cur = cur->getNext();
		}
		if (cur->getSv() < tmp->getSv())
		{
			prev->setNext(tmp);
			tmp->setNext(cur);
		}
		else
		{
			cur->setA(cur->getA() + tmp->getA());
			if (cur->getA() == 0)
			{
				prev->setNext(cur->getNext());
				cur->setNext(0);
				delete cur;
			}
		}
	};
	void addMonom(int64 sv, int a)
	{
		monom * tmp = new monom(a, sv);
		addMonom(tmp);
	};
	void addMonom(string st, int maxSt, int nx) {
		monom *tmp = new monom(st, maxSt, nx);
		addMonom(tmp);
	};
#pragma endregion
	
#pragma region operators

	cyclelist operator*  (      int         tmp) {
		cyclelist result(*this);
		monom * cur = result.first->getNext();
		
		while (cur != result.first){
			cur->setA(cur->getA() * tmp);
			cur = cur->getNext();
		}
		return result;
	}
	cyclelist operator*  (const cyclelist & tmp) {
		cyclelist result;
		monom * cur1 = first->getNext(), *cur2 = tmp.first->getNext(), *m;
		while (cur1 != first)
		{
			while (cur2 != tmp.first)
			{
				m = new monom();
				*m = cur1->multipli(cur2,10);
				if (m->getSv()!=-1)
				result.addMonom(m);
			    cur2 = cur2->getNext();
			}
			cur2 = tmp.first->getNext();
			cur1 = cur1->getNext();
		}
		return result;
	}
	cyclelist operator+  (const cyclelist & tmp) {
		
		cyclelist result;
		monom * cur1 = first->getNext(), *cur2 = tmp.first->getNext(), *m;
		while (cur1 != first)
		{
			m = new monom(*cur1);
            result.addMonom(m);
			cur1 = cur1->getNext();
		}
		while (cur2 != tmp.first)
		{
			m = new monom(*cur2);
			result.addMonom(m);
			cur2 = cur2->getNext();
		}
		return result;
	}
	cyclelist operator-  (      cyclelist & tmp) {

		cyclelist result = tmp * (-1) ;
		result = result +  *this;
		return result;

	}
	cyclelist & operator=(const cyclelist & tmp) {
	
		monom *cur1 = tmp.first->getNext(), *cur2 = first;

		while (cur1 != tmp.first)
		{
			monom *m = new monom(*cur1);
			cur2->setNext(m);
			cur1 = cur1->getNext();
			cur2 = m;
		}
		cur2->setNext(first);

		return(*this);
	};

#pragma endregion


	string toString(int maxSt =10, int nx =10) {
		monom * cur=first->getNext();
		string s = "";
		while (cur != first) {
			if (cur->getA() > 0) s += "+";
			s +=cur->toString(maxSt,nx);
			cur = cur->getNext();
		}
		return s;
	}
	~cyclelist() {
		monom *p = first->getNext(), *last = first ,* next ;
		while (p != first) {
			p = p->getNext();
			last = p;
		}
		last->setNext(0);
		p = first;
		while (p!=0)
		{
			last = p;
			p = p->getNext();
			delete last;
		}
		/*
		monom * next = first->getNext(), * cur = first;

		while (next != first)
		{
		cur->setNext(0);
		delete cur;
		cur = next;
		next = next->getNext();
		}
		if (next == first)
		{
		cur->setNext(0);
		//delete cur;
		}
		*/
		
		

	};
};

