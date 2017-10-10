/*!
 *  \file c_combinator.h
 *
 *  \brief This file contains the declaration of C_Combinator class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_COMBINATOR_H
#define TWO_C_COMBINATOR_H


#include <memory>          // std::shared_ptr
#include "c_combination.h"
#include "common.h"


namespace two {


/*!
 *  \brief Compute the number of possibile combinations

 *  \param p_nElements number of elements
 *  \param p_k size of the combinations
 *  \param p_nCombinations number of combinations
 *
 *  \return TwoReturnCodeEnum
 */
TwoReturnCodeEnum computeNumberOfCombinations(const int p_nElements, const int p_K, size_t& p_nCombinations);


/*!
 *  \brief The C_Combinator class represents is an helper to create combinations
 */
template <typename T>
class C_Combinator
{


public:

    /*!
     *  \brief Default constructor
     */
    C_Combinator();

    /*!
     *  \brief Destructor
     */
    ~C_Combinator();

    /*!
     *  \brief Deleted copy constructor
     */
    C_Combinator<T>(const C_Combinator<T>& p_orig) = delete;

    /*!
     *  \brief Deleted copy assignment
     */
    C_Combinator<T>& operator=(const C_Combinator<T>& p_other) = delete;

    /*!
     *  \brief Deleted move constructor
     */
    C_Combinator<T>(C_Combinator<T>&& p_orig) = delete;

    /*!
     *  \brief Deleted move assignment
     */
    C_Combinator<T>& operator=(C_Combinator<T>&& p_other) = delete;

    /*!
     *  \brief Create combinations using the elements passed
     *
     *  \param p_elements std::list of elements to use for the combinations
     *  \param p_k size of the combination
     *  \param p_combinations std::list updated with the produced combinations
     *
     *  \return TwoReturnCodeEnum
     */
    static TwoReturnCodeEnum CreateCombinations(const std::list<T>& p_elements, const int p_K, std::list<std::shared_ptr<C_Combination<T> > >& p_combinations);


private:


};



template <typename T>
C_Combinator<T>::C_Combinator()
{

}


/* virtual */
template <typename T>
C_Combinator<T>::~C_Combinator()
{

}


/* static */
template <typename T>
TwoReturnCodeEnum C_Combinator<T>::CreateCombinations(const std::list<T>& p_elements, const int p_K, std::list<std::shared_ptr<C_Combination<T> > >& p_combinations)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    const size_t l_nElements = p_elements.size();

    p_combinations.clear();

    if (0 == l_nElements)
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeInvalidParameters;
    }
    else if (0 >= p_K)
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeInvalidParameters;
    }
    else if (l_nElements < static_cast<size_t>(p_K))
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeInvalidParameters;
    }
    else
    {
        /* create a bit mask */

        std::string l_bitMask(static_cast<size_t>(p_K), '1'); /* first p_K elements set to 1      */
        l_bitMask.resize(l_nElements, '\0');                  /* fill with zero up to l_nElements */

        /* build a combination */

        std::list<T> l_elements;

        do
        {
            l_elements.clear();

            auto it_element = p_elements.cbegin();

            for (size_t i = 0; i < l_nElements; ++i)
            {
                if ('1' == l_bitMask[i])
                {
                    l_elements.push_back(*it_element);
                }

                ++it_element;
            }

            p_combinations.emplace_back(std::make_shared<C_Combination<T> >(l_elements));

        } while (true == std::prev_permutation(l_bitMask.begin(), l_bitMask.end()));
    }

    return l_returnCode;
}


} /* namespace two { */


#endif // TWO_C_COMBINATOR
