#ifndef PROG_H
#define PROG_H

#include "multiset.h"
//using a namespace as needed

#include <string>

void runProgram();
void rewrite();
bool applyRules(Multiset&);

#ifdef __linux__
    void* worker(void* parameters); //Linux, using pthread
#else
    void worker(); //Windows, Macosx, using thread
#endif

#endif