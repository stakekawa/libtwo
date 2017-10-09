/*!
 *  \file pthread_mutexlocker_t.h
 *
 *  \brief This file contains the declaration of pthread_mutexlocker_t class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_PTHREAD_MUTEXLOCKER_T_H
#define TWO_PTHREAD_MUTEXLOCKER_T_H


#include <atomic>    // std::atomic
#include <pthread.h> // pthread_mutex_t
#include "common.h"


namespace two {


/*!
 *  \brief The pthread_mutexlocker_t class provides an equivalent of the std::lock_guard
 *         for the pthread_mutex_t
 */
class pthread_mutexlocker_t
{


public:

    /*!
     *  \brief Default constructor. The mutex is locked once upon construction
     *
     *  \param p_mutex reference to pthread_mutex_t to lock
     */
    pthread_mutexlocker_t(pthread_mutex_t& p_mutex);

    /*!
     *  \brief Destructor. The mutex is unlocked once upon destruction
     */
    ~pthread_mutexlocker_t();

    /*!
     *  \brief Query if the pthread_mutex_t is actually locked
     */
    bool IsLocked() const { return 0 != m_lockCounter.load(); }

    /*!
     *  \brief Get the number of locks of the mutex
     */
    int GetLockCounter() const { return m_lockCounter.load(); }

    /*!
     *  \brief Lock the pthread_mutex_t
     */
    TwoReturnCodeEnum Lock();

    /*!
     *  \brief UnLock the pthread_mutex_t
     */
    TwoReturnCodeEnum Unlock();

    /*!
     *  \brief Deleted copy constructor
     */
    pthread_mutexlocker_t(const pthread_mutexlocker_t&) = delete;

    /*!
     *  \brief Deleted copy assignment
     */
    pthread_mutexlocker_t& operator=(const pthread_mutexlocker_t&) = delete;

    /*!
     *  \brief Deleted move constructor
     */
    pthread_mutexlocker_t(pthread_mutexlocker_t&&) = delete;

    /*!
     *  \brief Deleted move assignment
     */
    pthread_mutexlocker_t& operator=(pthread_mutexlocker_t&&) = delete;


private:

    pthread_mutex_t&  m_mutex;
    std::atomic<int>  m_lockCounter;


};


} /* end namespace two { */


#endif // TWO_PTHREAD_MUTEXLOCKER_T_H
