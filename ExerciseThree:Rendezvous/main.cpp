//Bernard Steemers
//20/11/2019
//Licence: Attribution 4.0 International (CC BY 4.0)
//You are free to:
//	- Share — copy and redistribute the material in any medium or format
//	- Adapt — remix, transform, and build upon the material for any purpose, even commercially.
//	- Link: https://creativecommons.org/licenses/by/4.0/legalcode


#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \file main.cpp
    \brief An Implementation of a Rendezvous using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads
*/
	
/*!
	\fn taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
	\brief taskOne displays a message that is split in to 2 sections to show how a rendezvous works 
*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  secondSem->Signal();
  firstSem->Wait();
  //THIS IS THE RENDEZVOUS POINT!
  std::cout << "Task One has left!"<<std::endl;
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay) 
	\fn brief taskTwo displays a message that is split in to 2 sections to show how a rendezvous works
*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  firstSem->Signal();
  std::cout <<"Task Two has arrived "<<std::endl;
  secondSem->Wait();
  //THIS IS THE RENDEZVOUS POINT!
  std::cout << "Task Two has left "<<std::endl;
}

/*! \fn int main(void)
	\brief creates two threads with delay times and joins them to main thread
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);  /**< Creating Semaphores */
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();/**< Joining to main thread */
  threadTwo.join();
  return 0;
}
