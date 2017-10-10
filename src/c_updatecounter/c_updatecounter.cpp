/*!
 *  \file c_updatecounter.cpp
 *
 *  \brief This file contains the implementation of C_UpdateCounter class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include "c_updatecounter.h"


namespace two {


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


static constexpr int64_t k_numberOfUpdatesDefault = 0;


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


C_UpdateCounter::C_UpdateCounter() :
    m_lastUpdate(std::chrono::steady_clock::now()),
    m_numberOfUpdates(k_numberOfUpdatesDefault),
    m_mutex()
{

}


/* virtual */
C_UpdateCounter::~C_UpdateCounter()
{

}


/* virtual */
void C_UpdateCounter::SetLastUpdate()
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);
    m_lastUpdate = std::chrono::steady_clock::now();
    ++m_numberOfUpdates;
}


int C_UpdateCounter::GetLastUpdateMilliseconds() const
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);
    return static_cast<int>((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_lastUpdate)).count());
}


int C_UpdateCounter::GetLastUpdateSeconds() const
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);
    return static_cast<int>((std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - m_lastUpdate)).count());
}


int64_t C_UpdateCounter::GetNumberOfUpdates() const
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);
    return m_numberOfUpdates;
}


void C_UpdateCounter::Reset()
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);
    m_lastUpdate = std::chrono::steady_clock::now();
    m_numberOfUpdates = k_numberOfUpdatesDefault;
}


} /* namespace two { */
