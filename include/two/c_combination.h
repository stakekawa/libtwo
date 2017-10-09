/*!
 *  \file c_combination.h
 *
 *  \brief This file contains the declaration of C_Combination class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_COMBINATION_H
#define TWO_C_COMBINATION_H


#include <algorithm> // std::sort
#include <cassert>   // assert
#include <list>      // std::list
#include <ostream>   // std::ostream
#include <vector>    // std::vector


namespace two {


/*!
 *  \brief The C_Combination class represents a math combination of elements. Elements
 *         are always sorted and not duplicated. Therefore the data type T must have
 *         operator>, operator<, operator== and operator!=.
 */
template <typename T>
class C_Combination
{


public:

    /*!
     *  \brief Default constructor. The mutex is locked once upon construction
     *
     *  \param p_mutex reference to pthread_mutex_t to lock
     */
    C_Combination();

    /*!
     *  \brief Constructor using a std::vector of elements
     *
     *  \param p_elements reference to std::vector of elements
     */
    explicit C_Combination(const std::vector<T>& p_elements);

    /*!
     *  \brief Constructor using a std::vector of elements
     *
     *  \param p_elements r-value to std::vector of elements
     */
    explicit C_Combination(std::vector<T>&& p_elements);

    /*!
     *  \brief Constructor using a std::list of elements
     *
     *  \param p_elements reference to std::list of elements
     */
    explicit C_Combination(const std::list<T>& p_elements);

    /*!
     *  \brief Destructor. The mutex is unlocked once upon destruction
     */
    virtual ~C_Combination();

    /*!
     *  \brief Deleted copy constructor
     */
    C_Combination<T>(const C_Combination<T>& p_orig);

    /*!
     *  \brief Deleted copy assignment
     */
    C_Combination<T>& operator=(const C_Combination<T>& p_other);

    /*!
     *  \brief Deleted move constructor
     */
    C_Combination<T>(C_Combination<T>&& p_orig);

    /*!
     *  \brief Deleted move assignment
     */
    C_Combination<T>& operator=(C_Combination<T>&& p_other);

    /*!
     *  \brief Get the number of element of the combination
     */
    int GetNumberOfElements() const;

    /*!
     *  \brief Add an element to the combination.
     *
     *  \param p_element reference of element to add
     */
    void AddElement(const T& p_element);

    /*!
     *  \brief Add an element to the combination.
     *
     *  \param p_element r-value of element to add
     */
    void AddElement(const T&& p_element);

    /*!
     *  \brief Replace the elements
     *
     *  \param p_elements reference to std::vector with new elements
     */
    void ReplaceElements(const std::vector<T>& p_elements);

    /*!
     *  \brief Replace the elements
     *
     *  \param p_elements r-value to std::vector with new elements
     */
    void ReplaceElements(std::vector<T>&& p_elements);

    /*!
     *  \brief Remove the element at requested index
     */
    void RemoveElementByIndex(const int p_index);

    /*!
     *  \brief Remove an element equal to the requested value
     */
    void RemoveElementByValue(const T& p_value);

    /*!
     *  \brief Get an element
     *
     *  \param p_index index of the element
     */
    const T& GetElement(const int p_index) const;

    /*!
     *  \brief Get the std::vector of all elements
     */
    const std::vector<T>& GetElements() const;

    /*!
     * \brief Get a copy of an element
     *
     * \param p_index index of the element
     */
    T GetElementCopy(const int p_index) const;

    /*!
     *  \brief Get a copy of all elements
     *  \return
     */
    std::vector<T> GetElementsCopy() const;

    /*!
     *  \brief Get the minimum element
     */
    T GetElementMin() const;

    /*!
     *  \brief Get the maximum element
     */
    T GetElementMax() const;

    /*!
     *  \brief Equality operator
     */
    bool operator==(const C_Combination<T>& p_other);

    /*!
     * \brief Inequality operator
     */
    bool operator!=(const C_Combination<T>& p_other);

    /*!
     *  \brief operator<
     */
    bool operator<(const C_Combination<T>& p_other);

    /*!
     *  \brief operator>
     */
    bool operator>(const C_Combination<T>& p_other);

    /*!
     *  \brief Add to elements the same value. Addition depends on the implementation of
     *         the operator+ of the data type T
     *
     *  \param p_value value to add
     */
    void AddToElements(const T& p_value);

    /*!
     *  \brief Subtract to elements the same value. Subtraction depends on the implementation of
     *         the operator+ of the data type T
     *
     *  \param p_value value to subtract
     */
    void SubtractToElements(const T& p_value);


private:

    /*!
     *  \brief Sort elements
     */
    void SortElements();

    /*!
     *  \brief Remove duplicated elements
     */
    void RemoveDuplicatedElements();

    std::vector<T> m_elements;


};


/*!
 *  \brief Inserction operator
 */
template <typename T>
std::ostream& operator<<(std::ostream& p_ostream, const C_Combination<T>& p_combination)
{
    p_ostream << "{ ";

    const int l_nElements = p_combination.GetNumberOfElements();
    for (int i = 0; i < l_nElements - 1; ++i)
    {
        p_ostream << p_combination.GetElement(i) << ", ";
    }

    if (0 < l_nElements)
    {
        p_ostream << p_combination.GetElement(l_nElements - 1);
    }

    p_ostream << " }";

    return p_ostream;
}


/*!
 *  \brief operator+. Add the elements of the second C_Combination object to the former.
 */
template <typename T>
C_Combination<T> operator+(const C_Combination<T>& p_comb1, const C_Combination<T>& p_comb2)
{
    const int l_nElements1 = p_comb1.GetNumberOfElements();
    const int l_nElements2 = p_comb2.GetNumberOfElements();

    std::list<T> l_elements;

    for (int i = 0; i < l_nElements1; ++i)
    {
        l_elements.push_back(p_comb1.GetElement(i));
    }

    for (int i = 0; i < l_nElements2; ++i)
    {
        l_elements.push_back(p_comb2.GetElement(i));
    }

    C_Combination<T> l_result(l_elements);

    return l_result;
}


/*!
 *  \brief operator+. Add the elements of the second C_Combination object to the former.
 */
template <typename T>
C_Combination<T> operator+(C_Combination<T>&& p_comb1, const C_Combination<T>& p_comb2)
{
    const int l_nElements2 = p_comb2.GetNumberOfElements();

    std::vector<T> l_elements(p_comb1.GetElements());

    for (int i = 0; i < l_nElements2; ++i)
    {
        l_elements.push_back(p_comb2.GetElement(i));
    }

    p_comb1.ReplaceElements(l_elements);

    return p_comb1;
}


/*!
 *  \brief operator+. Add the elements of the second C_Combination object to the former.
 */
template <typename T>
C_Combination<T> operator+(const C_Combination<T>& p_comb1, C_Combination<T>&& p_comb2)
{
    const int l_nElements1 = p_comb1.GetNumberOfElements();

    std::vector<T> l_elements(p_comb2.GetElements());

    for (int i = 0; i < l_nElements1; ++i)
    {
        l_elements.push_back(p_comb1.GetElement(i));
    }

    p_comb2.ReplaceElements(l_elements);

    return p_comb2;
}


/*!
 *  \brief operator-. Remove the elements of the second C_Combination object from the former.
 */
template <typename T>
C_Combination<T> operator-(const C_Combination<T>& p_comb1, const C_Combination<T>& p_comb2)
{
    const int l_nElements2 = p_comb2.GetNumberOfElements();

    C_Combination<T> l_result(p_comb1);

    for (int i = 0; i < l_nElements2; ++i)
    {
        l_result.RemoveElementByValue(p_comb2.GetElement(i));
    }

    return l_result;
}


/*!
 *  \brief operator-. Remove the elements of the second C_Combination object from the former.
 */
template <typename T>
C_Combination<T> operator-(C_Combination<T>&& p_comb1, const C_Combination<T>& p_comb2)
{
    const int l_nElements2 = p_comb2.GetNumberOfElements();

    for (int i = 0; i < l_nElements2; ++i)
    {
        p_comb1.RemoveElementByValue(p_comb2.GetElement(i));
    }

    return p_comb1;
}


template <typename T>
C_Combination<T>::C_Combination() :
    m_elements()
{

}


template <typename T>
C_Combination<T>::C_Combination(const std::vector<T>& p_elements) :
    m_elements(p_elements)
{
    SortElements();
    RemoveDuplicatedElements();
}


template <typename T>
C_Combination<T>::C_Combination(std::vector<T>&& p_elements) :
    m_elements()
{
    std::swap(m_elements, p_elements);
    SortElements();
    RemoveDuplicatedElements();
}


template <typename T>
C_Combination<T>::C_Combination(const std::list<T>& p_elements) :
    m_elements(p_elements.begin(), p_elements.end())
{
    SortElements();
    RemoveDuplicatedElements();
}


template <typename T>
C_Combination<T>::~C_Combination()
{

}


template <typename T>
C_Combination<T>::C_Combination(const C_Combination<T>& p_orig) :
    m_elements(p_orig.m_elements)
{

}


template <typename T>
C_Combination<T>& C_Combination<T>::operator=(const C_Combination<T>& p_other)
{
    if (this != &p_other)
    {
        m_elements.assign(p_other.m_elements.begin(), p_other.m_elements.end());
    }

    return *this;
}


template <typename T>
C_Combination<T>::C_Combination(C_Combination<T>&& p_orig) :
    m_elements(std::move(p_orig.m_elements))
{

}


template <typename T>
C_Combination<T>& C_Combination<T>::operator=(C_Combination<T>&& p_other)
{
    if (this != &p_other)
    {
        std::swap(m_elements, p_other.m_elements);
    }

    return *this;
}


template <typename T>
inline int C_Combination<T>::GetNumberOfElements() const
{
    return static_cast<int>(m_elements.size());
}


template <typename T>
void C_Combination<T>::AddElement(const T& p_element)
{
    m_elements.push_back(p_element);
    SortElements();
    RemoveDuplicatedElements();
}


template <typename T>
void C_Combination<T>::AddElement(const T&& p_element)
{
    m_elements.emplace_back(p_element);
    SortElements();
    RemoveDuplicatedElements();
}


template <typename T>
void C_Combination<T>::ReplaceElements(const std::vector<T>& p_elements)
{
    m_elements.assign(p_elements.begin(), p_elements.end());
    SortElements();
    RemoveDuplicatedElements();
}


template <typename T>
void C_Combination<T>::ReplaceElements(std::vector<T>&& p_elements)
{
    m_elements.clear();
    std::swap(m_elements, p_elements);
    SortElements();
    RemoveDuplicatedElements();
}


template <typename T>
void C_Combination<T>::RemoveElementByIndex(const int p_index)
{
    assert(p_index < GetNumberOfElements());
    m_elements.erase(m_elements.begin() + p_index);
}


template <typename T>
void C_Combination<T>::RemoveElementByValue(const T& p_value)
{
    auto it_element = std::remove_if(m_elements.begin(), m_elements.end(), [&](const T& p_element){ return p_element == p_value; });
    m_elements.erase(it_element, m_elements.end());
}


template <typename T>
inline const T& C_Combination<T>::GetElement(const int p_index) const
{
    assert(p_index < GetNumberOfElements());
    return m_elements[static_cast<size_t>(p_index)];
}


template <typename T>
inline const std::vector<T>& C_Combination<T>::GetElements() const
{
    return m_elements;
}


template <typename T>
T C_Combination<T>::GetElementCopy(const int p_index) const
{
    assert(p_index < GetNumberOfElements());
    return T(m_elements[static_cast<size_t>(p_index)]);
}


template <typename T>
std::vector<T> C_Combination<T>::GetElementsCopy() const
{
    return std::vector<T>(m_elements);
}


template <typename T>
T C_Combination<T>::GetElementMin() const
{
    assert(0 < GetNumberOfElements());
    return m_elements.begin();
}


template <typename T>
T C_Combination<T>::GetElementMax() const
{
    assert(0 < GetNumberOfElements());
    return m_elements.rbegin();
}


template <typename T>
bool C_Combination<T>::operator==(const C_Combination<T>& p_other)
{
    const int l_nElements = GetNumberOfElements();

    if (p_other.GetNumberOfElements() != l_nElements)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < l_nElements; ++i)
        {
            if (p_other.GetElement(i) != m_elements[i])
            {
                return false;
            }
        }
    }

    return true;
}


template <typename T>
bool C_Combination<T>::operator!=(const C_Combination<T>& p_other)
{
    const int l_nElements = GetNumberOfElements();

    if (p_other.GetNumberOfElements() != l_nElements)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < l_nElements; ++i)
        {
            if (p_other.GetElement(i) != m_elements[i])
            {
                return true;
            }
        }
    }

    return false;
}


template <typename T>
bool C_Combination<T>::operator<(const C_Combination<T>& p_other)
{
    const int l_nElements = GetNumberOfElements();

    if (p_other.GetNumberOfElements() > l_nElements)
    {
        return true;
    }
    else if (p_other.GetNumberOfElements() < l_nElements)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < l_nElements; ++i)
        {
            if (p_other.GetElement(i) > m_elements[i])
            {
                return true;
            }
        }
    }

    return false;
}


template <typename T>
bool C_Combination<T>::operator>(const C_Combination<T>& p_other)
{
    const int l_nElements = GetNumberOfElements();

    if (p_other.GetNumberOfElements() < l_nElements)
    {
        return true;
    }
    else if (p_other.GetNumberOfElements() > l_nElements)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < l_nElements; ++i)
        {
            if (p_other.GetElement(i) < m_elements[i])
            {
                return true;
            }
        }
    }

    return false;
}


template <typename T>
void C_Combination<T>::AddToElements(const T& p_value)
{
    for (T& l_element: m_elements)
    {
        l_element = std::plus<T>()(l_element, p_value);
    }
}


template <typename T>
void C_Combination<T>::SubtractToElements(const T& p_value)
{
    for (T& l_element: m_elements)
    {
        l_element = std::minus<T>()(l_element, p_value);
    }
}


template <typename T>
inline void C_Combination<T>::SortElements()
{
    std::sort(m_elements.begin(), m_elements.end());
}


template <typename T>
inline void C_Combination<T>::RemoveDuplicatedElements()
{
    m_elements.erase(std::unique(m_elements.begin(), m_elements.end()), m_elements.end());
}


} /* end namespace two { */


#endif // TWO_C_COMBINATION_H
