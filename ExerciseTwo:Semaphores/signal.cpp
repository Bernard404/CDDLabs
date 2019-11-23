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
#include <unistd.h>
/*! \class signal
    \brief An Implementation of Threads Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 

*/
/*! displays a message first*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
}
/*! displays a message second*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}


int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
