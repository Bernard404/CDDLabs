//Bernard Steemers
//20/11/2019
//Licence: Attribution 4.0 International (CC BY 4.0)
//You are free to:
//	- Share — copy and redistribute the material in any medium or format
//	- Adapt — remix, transform, and build upon the material for any purpose, even commercially.
//	- Link: https://creativecommons.org/licenses/by/4.0/legalcode

#include "Semaphore.h"
/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/



/*! \fn void Signal
	\brief Sends signal to wait
 */
void Semaphore::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });
      --m_uiCount;
}

template< typename R,typename P >
bool Semaphore::Wait(const std::chrono::duration<R,P>& crRelTime)
{
      std::unique_lock< std::mutex > lock(m_mutex);
      if (!m_condition.wait_for(lock,crRelTime,[&]()->bool{ return m_uiCount>0; })){
	  return false;
      }
      --m_uiCount;
      return true;
}


/*! \fn void Signal
	\brief Sends signal to release
 */
void Semaphore::Signal()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}
