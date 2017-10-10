/*!
 *  \file c_observable.h
 *
 *  \brief This file contains the declaration of C_Observable class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_OBSERVABLE_H
#define TWO_C_OBSERVABLE_H


#include <algorithm>    // std::find
#include <map>          // std::map
#include <mutex>        // std::recursive_mutex
#include <list>         // std::vector
#include "c_observer.h"


namespace two {


/*!
 *  \brief Observable class of the observer design pattern. The class is a template
 *         to allow to create C_Observable on different event types
 */
template <typename T>
class C_Observable
{

    using observersList_t = std::list<C_Observer<T>*>;

    struct ObserverData_t
    {
        std::recursive_mutex mutex;
        observersList_t      observersList;

        ObserverData_t() :
            mutex(),
            observersList()
        { /* empty */ }

    };

    using ObserverMap_t  = std::map<T, ObserverData_t>;


public:

    /*!
     *  \brief Constructor
     */
    C_Observable();

    /*!
     *  \brief Destructor
     */
    virtual ~C_Observable();

    /*!
     *  \brief Subscribe to the notification system for an event
     *
     *  \param p_event
     *  \param p_observer
     *
     *  \return true if success, otherwise false
     */
    bool Subscribe(const T& p_event, C_Observer<T>* p_observer);

    /*!
     *  \brief Unsubscribe from the notification system for an event
     *
     *  \param p_event
     *  \param p_observer
     *
     *  \return true if success, otherwise false
     */
    bool Unsubscribe(const T& p_event, C_Observer<T>* p_observer);


protected:

    /*!
     *  \brief Notification function of the C_Observable. The method Update(void* p_arg) of
     *         each C_Observer, subscribed to the event) is called.
     *
     *  \param p_event
     *  \param p_arg
     *
     *  \return true if success, otherwise false
     */
    virtual bool Notify(const T& p_event, void* p_arg);


private:

    ObserverMap_t m_observersMap;         /*!< map of event types and observers */
    mutable std::recursive_mutex m_mutex; /*!< mutex to protect m_observersMap and notification system */


};


template <typename T>
C_Observable<T>::C_Observable() :
    m_observersMap(),
    m_mutex()
{

}


template <typename T>
C_Observable<T>::~C_Observable()
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);
    m_observersMap.clear();
}


template <typename T>
bool C_Observable<T>::Subscribe(const T& p_event, C_Observer<T>* p_observer)
{
    bool l_subscribed = true;

    if (NULL == p_observer)
    {
        l_subscribed = false;
    }
    else
    {
        std::lock_guard<std::recursive_mutex> l_lock(m_mutex);

        std::lock_guard<std::recursive_mutex> l_listLock(m_observersMap[p_event].mutex);

        auto l_observer = std::find(m_observersMap[p_event].observersList.begin(),
                                    m_observersMap[p_event].observersList.end(),
                                    p_observer);

        /* add the observer only if not already subscribed */

        if (m_observersMap[p_event].observersList.end() == l_observer)
        {
            m_observersMap[p_event].observersList.push_back(p_observer);
        }

    } /* end if (NULL == p_observer) */

    return l_subscribed;
}


template <typename T>
bool C_Observable<T>::Unsubscribe(const T& p_event, C_Observer<T>* p_observer)
{
    bool l_subscribed = true;

    if (NULL == p_observer)
    {
        l_subscribed = false;
    }
    else
    {
        std::lock_guard<std::recursive_mutex> l_lock(m_mutex);

        std::lock_guard<std::recursive_mutex> l_listLock(m_observersMap[p_event].mutex);

        auto l_observer = std::find(m_observersMap[p_event].observersList.begin(),
                                    m_observersMap[p_event].observersList.end(),
                                    p_observer);

        while (m_observersMap[p_event].observersList.end() != l_observer)
        {
            l_observer = m_observersMap[p_event].observersList.erase(l_observer);

            l_observer = std::find(l_observer,
                                   m_observersMap[p_event].observersList.end(),
                                   p_observer);
        }

    } /* end if (NULL == p_observer) */

    return l_subscribed;
}


/* virtual */
template <typename T>
bool C_Observable<T>::Notify(const T& p_event, void *p_arg)
{
    bool l_return = true;
    m_mutex.lock();
    std::lock_guard<std::recursive_mutex> l_listLock(m_observersMap[p_event].mutex);
    m_mutex.unlock();

    for (C_Observer<T>* l_observer : m_observersMap[p_event].observersList)
    {
        l_return = l_return && l_observer->Update(p_event, p_arg);
    }

    return l_return;
}



} /* namespace two { */


#endif // TWO_C_OBSERVABLE_H
