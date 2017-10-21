/*!
 *  \file c_onlinemeansigma.h
 *
 *  \brief This file contains the declaration of the C_OnlineMeanSigma class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_ONLINEMEANSIGMA_H
#define TWO_C_ONLINEMEANSIGMA_H


#include <mutex> // std::recursive_mutex


namespace two {


/*!
 *  \brief The C_OnlineMeanSigma class can be used to the get the online mean
 *         and the standard deviation of a population / signal. It has no
 *         history of the data. The C_OnlineMeanSigma has low memory footprint and
 *         does little calculation when a new sample is added. The only stored
 *         datas are the number of the samples added since last reset, the sum
 *         of the samples, the sum of the squared samples.
 *         The C_OnlineMeanSigma class is thread-safe.
 */
class C_OnlineMeanSigma
{

public:

    /*!
     *  \brief Constructor
     */
    C_OnlineMeanSigma();

    /*!
     *  \brief Destructor
     */
    ~C_OnlineMeanSigma();

    /*!
     *  \brief Add a new sample
     *
     *  \param p_sample new sample to add
     */
    void AddSample(const double p_sample);

    /*!
     *  \brief Get the mean value of samples accumulated since last reset
     *
     *  \return the mean value or NAN if the number of samples is zero
     */
    double GetMean() const;

    /*!
     *  \brief Get the standard deviation of the samples accumulated since last reset
     *
     *  \return the standard deviation or NAN if the number of samples is zero
     */
    double GetStandardDeviation() const;

    /*!
     *  \brief Get the number of the samples accumulated since last reset
     *  \return
     */
    int GetNumberOfSamples() const;

    /*!
     *  \brief Reset the C_OnlineMeanSigma object
     */
    void Reset();


protected:

    /*!
     *  \brief Lock the mutex
     */
    void MutexLock() const;

    /*!
     *  \brief Unlock the mutex
     */
    void MutexUnlock() const;


private:

    int                          m_nSamples;
    double                       m_sampleSum;
    double                       m_sample2Sum;

    mutable std::recursive_mutex m_mutex;


};


} /* namespace two { */


#endif // TWO_C_ONLINEMEANSIGMA_H
