/*!
 *  \file c_onlinemeansigma.cpp
 *
 *  \brief This file contains the implementation of the C_OnlineMeanSigma class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <cmath>
#include "c_onlinemeansigma.h"

#include <iostream>


namespace two {


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


static constexpr int    k_nSamplesDefault   = 0;
static constexpr double k_sampleSumDefault  = 0.;
static constexpr double k_sample2SumDefault = 0.;


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


C_OnlineMeanSigma::C_OnlineMeanSigma() :
    m_nSamples(k_nSamplesDefault),
    m_sampleSum(k_sampleSumDefault),
    m_sample2Sum(k_sample2SumDefault),
    m_mutex()
{

}


C_OnlineMeanSigma::~C_OnlineMeanSigma()
{

}


void C_OnlineMeanSigma::AddSample(const double p_sample)
{
    std::unique_lock<std::recursive_mutex> l_lock(m_mutex);

    m_sampleSum  += p_sample;
    m_sample2Sum += p_sample*p_sample;
    ++m_nSamples;
}


double C_OnlineMeanSigma::GetMean() const
{
    double l_mean(double(NAN));

    std::unique_lock<std::recursive_mutex> l_lock(m_mutex);

    if (k_nSamplesDefault != m_nSamples)
    {
        l_mean = m_sampleSum / double(m_nSamples);
    }

    return l_mean;
}


double C_OnlineMeanSigma::GetStandardDeviation() const
{
    double l_standardDeviation(double(NAN));

    std::unique_lock<std::recursive_mutex> l_lock(m_mutex);

    if (1 < m_nSamples) /* because it is the corrected stardard deviation */
    {
        const double l_nSamples = double(m_nSamples);
        l_standardDeviation     = sqrt(l_nSamples*m_sample2Sum-m_sampleSum*m_sampleSum) / l_nSamples; /* computation of deviation standard */
        l_standardDeviation    *= sqrt(l_nSamples / (l_nSamples - 1.));                               /* correct for the corrected one     */
    }

    return l_standardDeviation;
}


int C_OnlineMeanSigma::GetNumberOfSamples() const
{
    std::unique_lock<std::recursive_mutex> l_lock(m_mutex);
    return m_nSamples;
}


void C_OnlineMeanSigma::Reset()
{
    m_nSamples   = k_nSamplesDefault;
    m_sampleSum  = k_sampleSumDefault;
    m_sample2Sum = k_sample2SumDefault;
}


} /* namespace two { */
