#ifndef TERM_H
#define TERM_H

#include <vector>
#include "atom.h"

class Multiset //an atomic labelled-multiset (non-nested)
{
    private:
		Atom label;
		std::vector<Atom> bag; //for illustration purpose, we use a vector to represent a multiset

    public:
	    Multiset(Atom = 'a');
		Multiset(Atom, std::vector<Atom>&);
		~Multiset();

		void setMultiset(Atom, std::vector<Atom>&);
	    void produceAtom(Atom);
		bool consumeAtom(Atom);
		void printTerms();
		bool rewrite(Atom, Atom);
		bool rewrite(Atom, std::vector<Atom>&);
};

#endif