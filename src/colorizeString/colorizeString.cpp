/*!
 *  \file colorizeString.cpp
 *
 *  \brief This file contains the implementation of function to color
           a std::string suitable for std::cout << or std::cerr <<
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <array>            // std::array
#include <utility>          // std::forward
#include "colorizeString.h"
#include "common.h"


namespace two {


/*                                                                            */
/* private data                                                               */
/*                                                                            */


static const std::array<std::string,
                        static_cast<size_t>(StdStringColorEnum::StdStringColorSize)> k_colorStrings = { std::string("\033[0;31m"),
                                                                                                        std::string("\033[0;32m"),
                                                                                                        std::string("\033[0;33m"),
                                                                                                        std::string("\033[0;34m"),
                                                                                                        std::string("\033[0;35m"),
                                                                                                        std::string("\033[0;36m"),
                                                                                                        std::string("\033[0;37m"),
                                                                                                        std::string("\033[1;31m"),
                                                                                                        std::string("\033[1;32m"),
                                                                                                        std::string("\033[1;33m"),
                                                                                                        std::string("\033[1;34m"),
                                                                                                        std::string("\033[1;35m"),
                                                                                                        std::string("\033[1;36m"),
                                                                                                        std::string("\033[1;37m") };
static const std::string k_colorEnd = std::string("\033[0m");


/*                                                                            */
/* private functions                                                          */
/*                                                                            */


TwoReturnCodeEnum convertEnumClass(StdStringColorEnum&& p_color, std::string& p_colorString)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeOutOfRange;

    const size_t l_colorStringIndex = static_cast<size_t>(p_color);

    if (l_colorStringIndex < k_colorStrings.size())
    {
        p_colorString = k_colorStrings[l_colorStringIndex];
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;
    }

    return l_returnCode;
}


TwoReturnCodeEnum convertEnumClass(const StdStringColorEnum& p_color, std::string& p_colorString)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeOutOfRange;

    const size_t l_colorStringIndex = static_cast<size_t>(p_color);

    if (l_colorStringIndex < k_colorStrings.size())
    {
        p_colorString = k_colorStrings[l_colorStringIndex];
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;
    }

    return l_returnCode;
}


/*                                                                            */
/* public functions                                                           */
/*                                                                            */


std::string colorizeStdString(const std::string& p_string, StdStringColorEnum&& p_color)
{
    std::string l_colorizedString(p_string);
    std::string l_colorString;

    if (TwoReturnCodeEnum::TwoReturnCodeSuccess == convertEnumClass(std::forward<StdStringColorEnum>(p_color), l_colorString))
    {
        l_colorizedString.insert(0, l_colorString);  /* add the color code at the beginning of the string */
        l_colorizedString.append(k_colorEnd);        /* append the color close at the end of the string   */
    }

    return l_colorizedString;
}


std::string colorizeStdString(const std::string& p_string, const StdStringColorEnum& p_color)
{
    std::string l_colorizedString(p_string);
    std::string l_colorString;

    if (TwoReturnCodeEnum::TwoReturnCodeSuccess == convertEnumClass(p_color, l_colorString))
    {
        l_colorizedString.insert(0, l_colorString);  /* add the color code at the beginning of the string */
        l_colorizedString.append(k_colorEnd);        /* append the color close at the end of the string   */
    }

    return l_colorizedString;
}


} /* namespace two { */

