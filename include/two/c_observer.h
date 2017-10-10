/*!
 *  \file c_observable.h
 *
 *  \brief This file contains the declaration of C_Observable class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_OBSERVER_H
#define TWO_C_OBSERVER_H


namespace two {


/*!
 *  \brief C_Observer is the observer class of the observer design pattern
 */
template <typename T>
class C_Observer
{


public:

    /*!
     *  \brief Constructor
     */
    C_Observer();

    /*!
     *  \brief Destructor
     */
    virtual ~C_Observer();

    /*!
     *  \brief Update function. Each observer has to implement its own
     *         functions that is called by the observable
     */
    virtual bool Update(const T& p_event, void* p_arg) = 0;


};


template <typename T>
C_Observer<T>::C_Observer()
{

}


template <typename T>
C_Observer<T>::~C_Observer()
{

}


} /* namespace two { */


#endif // TWO_C_OBSERVER_H
