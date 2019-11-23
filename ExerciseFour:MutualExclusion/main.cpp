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
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \file main.cpp
    \brief An Implementation of Mutual Exclusion using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

 */

/*! \fn void updateTask
    \brief updates shared variable One at a time
*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){

 
  for(int i=0;i<numUpdates;i++){
    //UPDATE SHARED VARIABLE HERE!
    //
    firstSem->Wait();
    sharedVariable++;
    firstSem->Signal();
  }

}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
