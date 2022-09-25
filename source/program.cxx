#include <mutex>
#include <iostream>
#include <limits>
#include <vector>
#include "simplesystem.h"
#include "program.h"

#ifdef __linux__
#include <pthread.h>
#else
#include <thread>
#endif

void runProgram()
{
	std::vector<Atom> v1(5,'a'), v2(4,'b'), v3(3,'c');
	SimpleSystem::bag1.setMultiset('f', v1);
	SimpleSystem::bag2.setMultiset('f', v2);
	SimpleSystem::bag3.setMultiset('f', v3);
	std::cout << "*******************************\n" << "Initial multisets:\n";
	SimpleSystem::bag1.printTerms();
	SimpleSystem::bag2.printTerms();
	SimpleSystem::bag3.printTerms();
	std::cout << "*******************************\n";
	rewrite();
	std::cout << "*******************************\n" << "The system halts:\n";
	SimpleSystem::bag1.printTerms();
	SimpleSystem::bag2.printTerms();
	SimpleSystem::bag3.printTerms();
}

void rewrite()
{
	#ifdef __linux__
		pthread_t worker;
		pthread_create(&worker, nullptr, workerThread, nullptr);
	#else
		std::thread* worker1 = new std::thread(worker);
		std::thread* worker2 = new std::thread(worker);
		std::thread* worker3 = new std::thread(worker);
	#endif

	try{
		//only wait for the workers to finish their job
		#ifdef __linux__
			pthread_join(worker, nullptr);
		#else
			worker1->join();
			worker2->join();
			worker3->join();
			delete worker1;
			delete worker2;
			delete worker3;
		#endif
	}
	catch (std::exception& e)
	{
		#ifndef __linux__
			delete worker1;
			delete worker2;
			delete worker3;
		#endif
		std::cout << "error " << e.what() << "\n";
	}
}


#ifdef __linux__
void* worker(void* parameters)
#else //windows, macos...
void worker()
#endif
{
	while (true)
	{
		int workingOn;
		std::unique_lock<std::mutex> lock0(SimpleSystem::mWorking); //RAII lock, when using std::lock_guard<std::mutex> beware of deadlock! since std::lock_guard<std::mutex> will not unlock unless it go out of its scope, which cannot be unlocked manually.
		workingOn = SimpleSystem::workingBag;
		if (workingOn == 1)
			SimpleSystem::workingBag = 2;
		else if (workingOn == 2)
			SimpleSystem::workingBag = 3;
		else
			SimpleSystem::workingBag = 1;
		auto th_id = std::this_thread::get_id();
		#ifndef __linux__
		std::cout << "Current working bag: " << workingOn << ", thread " << th_id << "\n";
		#endif
		lock0.unlock();

		if (workingOn == 1)
		{
			std::unique_lock<std::mutex> lock1(SimpleSystem::m1);
			std::unique_lock<std::mutex> lockE(SimpleSystem::mEvolve);
			if (SimpleSystem::canEvolve1)
			{
				if(!applyRules(SimpleSystem::bag1))
					SimpleSystem::canEvolve1 = false;
			}
			lockE.unlock();
			lock1.unlock();
		}
		else if (workingOn == 2)
		{
			std::unique_lock<std::mutex> lock2(SimpleSystem::m2); 
			std::unique_lock<std::mutex> lockE(SimpleSystem::mEvolve);
			if (SimpleSystem::canEvolve2)
			{
				if(!applyRules(SimpleSystem::bag2))
					SimpleSystem::canEvolve2 = false;
			}
			lockE.unlock();
			lock2.unlock();
		}
		else
		{
			std::unique_lock<std::mutex> lock3(SimpleSystem::m3); 
			std::unique_lock<std::mutex> lockE(SimpleSystem::mEvolve);
			if (SimpleSystem::canEvolve3)
			{
				if(!applyRules(SimpleSystem::bag3))
					SimpleSystem::canEvolve3 = false;
			}
			lockE.unlock();
			lock3.unlock();
		}

		std::unique_lock<std::mutex> lockE(SimpleSystem::mEvolve);
		if(SimpleSystem::canEvolve1 || SimpleSystem::canEvolve2 || SimpleSystem::canEvolve3)
		{
			lockE.unlock();
			continue;
		}
		else
		{	
			lockE.unlock();
			break;
		}
	}
#ifdef __linux__
	return nullptr;
#endif
}

bool applyRules(Multiset& bag){ //f(a) -> f(e), f(b) -> f(dfg), f(c) -> f()
 	bool succ = false;
	std::vector<Atom> dfg;
	dfg.push_back('d');
	dfg.push_back('f');
	dfg.push_back('g');
	if (bag.rewrite('a','e') || bag.rewrite('b', dfg) || bag.consumeAtom('c')){
		bag.printTerms();
		succ = true;
	}
	return succ;
}
