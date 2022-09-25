#ifndef SYSTEM_H
#define SYSTEM_H

#include <mutex>
#include "multiset.h"

//using a namespace as needed

struct SimpleSystem
{
    inline static Multiset bag1, bag2, bag3; //build a system with three multisets as an example
    inline static int workingBag = 1;
    inline static bool canEvolve1 = true, canEvolve2 = true, canEvolve3 = true;
    inline static std::mutex m1, m2, m3, mWorking, mEvolve;
};

#endif