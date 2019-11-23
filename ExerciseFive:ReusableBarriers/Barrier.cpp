//Bernard Steemers
//20/11/2019
//Licence: Attribution 4.0 International (CC BY 4.0)
//You are free to:
//	- Share — copy and redistribute the material in any medium or format
//	- Adapt — remix, transform, and build upon the material for any purpose, even commercially.
//	- Link: https://creativecommons.org/licenses/by/4.0/legalcode
#include "Barrier.h"

#include "Semaphore.h"


Barrier::Barrier(int numOfThreads)
{
    this->numOfThreads = numOfThreads;
    this->mutex = std::shared_ptr<Semaphore>(new Semaphore(1));
    this->turnOne = std::shared_ptr<Semaphore>(new Semaphore(0));
    this->turnTwo = std::shared_ptr<Semaphore>(new Semaphore(1));
    
}


Barrier::~Barrier()
{
}

void Barrier::phaseOne()
{
    mutex->Wait();
    ++threadCount;
    if (threadCount==numOfThreads)
    {
        turnTwo->Wait();
        TurnOne->Signal();
    }
    mutex->Signal();
    TurnOne->Wait();
    TurnOne->Signal();
}

void Barrier::phaseTwo()
{
    mutex->Wait();
    --threadCount;
    if(threadCount==0)
    {
        TurnOne->Wait();
        turnTwo->Signal();
    }
    mutex->Signal();
    turnTwo->Wait();
    turnTwo->Signal();
}
void Barrier::wait()
{
    phaseOne();
    phaseTwo();
}