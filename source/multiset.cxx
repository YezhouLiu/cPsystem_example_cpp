#include <iostream>
#include "multiset.h"

Multiset::Multiset(Atom a)
{
	label = a;
}

Multiset::Multiset(Atom a, std::vector<Atom>& v)
{
	setMultiset(a, v);
}

Multiset::~Multiset(){}

void Multiset::produceAtom(Atom a)
{
	bag.push_back(a);
}

void Multiset::setMultiset(Atom a, std::vector<Atom>& v)
{
	label = a;
	for (auto a: v)
		bag.push_back(a); //simply make a deepcopy
}

bool Multiset::consumeAtom(Atom a)
{
	bool succ = false;
	while (true)
	{
		auto pos = std::find(bag.begin(), bag.end(), a);
		if (pos != bag.end())
		{
			bag.erase(pos);
			succ = true;
		}
		else
			break;
	}
	return succ;
}

void Multiset::printTerms()
{
	std::cout << label << "(";
	for (auto a: bag)
		std::cout << a;
	std::cout << ")\n";
}

bool Multiset::rewrite(Atom a, Atom b)
{
	bool succ = false;
	for (int i = 0; i < bag.size(); ++i)
		if(bag[i] == a) 
		{
			bag[i] = b;
			succ = true;
		}
	return succ;
}

bool Multiset::rewrite(Atom a, std::vector<Atom>& v)
{
	if (v.empty()) return false;
	bool succ = false;
	std::vector<Atom> temp;
	for (int i = 0; i < bag.size(); ++i)
		if(bag[i] == a) 
		{
			bag[i] = v[0];
			for (int j = 1; j < v.size(); ++j)
				temp.push_back(v[j]);
			succ = true;
		}
	for (auto b: temp)
		v.push_back(b);
	return succ;
}