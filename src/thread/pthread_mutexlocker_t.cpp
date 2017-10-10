/*!
 *  \file pthread_mutexlocker_t.cpp
 *
 *  \brief This file contains the implementation of pthread_mutexlocker_t class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include "pthread_mutexlocker_t.h"


namespace two {



pthread_mutexlocker_t::pthread_mutexlocker_t(pthread_mutex_t& p_mutex) :
    m_mutex(p_mutex),
    m_lockCounter(0)
{
    Lock();
}


pthread_mutexlocker_t::~pthread_mutexlocker_t()
{
    Unlock();
}


TwoReturnCodeEnum pthread_mutexlocker_t::Lock()
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeError;

    if (0 == pthread_mutex_lock(&m_mutex))
    {
        ++m_lockCounter;

        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;
    }

    return  l_returnCode;
}


TwoReturnCodeEnum pthread_mutexlocker_t::Unlock()
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeError;

    if (0 == pthread_mutex_unlock(&m_mutex))
    {
        --m_lockCounter;

        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;
    }

    return  l_returnCode;
}


} /* namespace two { */
