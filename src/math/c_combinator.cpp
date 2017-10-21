/*!
 *  \file c_combinator.cpp
 *
 *  \brief This file contains the implementation of the C_Combinator class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include "c_combinator.h"


namespace two {


TwoReturnCodeEnum computeNumberOfCombinations(const int p_nElements, const int p_K, size_t& p_nCombinations)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    if ((0 == p_K) &&
        (0 == p_nElements))
    {
        p_nCombinations = 0;
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeInvalidParameters;
    }
    else if (0 > p_nElements)
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeInvalidParameters;
    }
    else if (0 > p_K)
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeInvalidParameters;
    }
    else if (0 == p_K)
    {
        p_nCombinations = 1;
    }
    else if (0 == p_nElements)
    {
        p_nCombinations = 1;
    }
    else if (p_nElements < p_K)
    {
        p_nCombinations = 1;
    }
    else if (p_nElements == p_K)
    {
        p_nCombinations = 1;
    }
    else if (1 == p_K)
    {
        p_nCombinations = static_cast<size_t>(p_nElements);
    }
    else
    {
        /* the number of combinations without repetitions is                    */
        /* n! / ( k! * (n - k)! ) == p_nElements! / p_K! * (p_nElements - p_K)! */
        /* which simplifies in                                                  */
        /* n * (n - 1) * ... * (n - k + 1) / k!                                 */

        uint64_t l_nCombinations = 1;
        uint64_t l_n = static_cast<uint64_t>(p_nElements);
        uint64_t l_K = static_cast<uint64_t>(p_K);

        while (l_n > static_cast<uint64_t>(p_nElements - p_K))
        {
            l_nCombinations *= l_n;
            --l_n;
        }

        l_K = 2;

        while (l_K <= static_cast<uint64_t>(p_K))
        {
            l_nCombinations /= l_K;
            ++l_K;
        }

        p_nCombinations = static_cast<size_t>(l_nCombinations);
    }

    return l_returnCode;
}




} /* namespace two { */
