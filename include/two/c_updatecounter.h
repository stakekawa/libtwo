/*!
 *  \file c_updatecounter.h
 *
 *  \brief This file contains the declaration of C_UpdateCounter class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_UPDATECOUNTER_H
#define TWO_C_UPDATECOUNTER_H


#include <chrono>
#include <mutex>


namespace two {


/*!
 *  \brief The C_UpdateCounter offers methods to track last updates and count elapsed time
 */
class C_UpdateCounter
{


public:

    /*!
     *  \brief Constructor
     */
    C_UpdateCounter();

    /*!
     *  \brief Destructor
     */
    ~C_UpdateCounter();

    /*!
     *  \brief Set last update and restart the time counter since last update
     */
    void SetLastUpdate();

    /*!
     *  \brief Return the time in milliseconds since last update
     */
    int GetLastUpdateMilliseconds() const;

    /*!
     *  \brief Return the time in seconds since last update
     */
    int GetLastUpdateSeconds() const;

    /*!
     *  \brief Return the number of updates
     */
    int64_t GetNumberOfUpdates() const;

    /*!
     *  \brief Reset the C_UpdateCounter
     */
    void Reset();


private:

    std::chrono::steady_clock::time_point m_lastUpdate;
    int64_t                               m_numberOfUpdates;
    mutable std::recursive_mutex          m_mutex;


};


} /* namespace two { */


#endif // TWO_C_UPDATECOUNTER_H
