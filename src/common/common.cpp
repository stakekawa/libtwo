/*!
 *  \file common.cpp
 *
 *  \brief This file contains the implementation of common stuff used in the C++
           Two library.
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <ctime>    // time_t, tm*
#include <iostream> // std::cerr
#include "common.h"
#include "two.h"


namespace two {


/*                                                                            */
/* public functions                                                           */
/*                                                                            */


std::string getTwoLibVersion()
{
    return std::string(TWO_LIBRARY_VERSION_STRING);
}


TwoReturnCodeEnum enumToStdString(const TwoReturnCodeEnum p_enum, std::string& p_stringEnum)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    switch (p_enum)
    {
        case TwoReturnCodeEnum::TwoReturnCodeSuccess:
            p_stringEnum = std::string("TwoReturnCodeSuccess");
            break;
        case TwoReturnCodeEnum::TwoReturnCodeError:
            p_stringEnum = std::string("TwoReturnCodeError");
            break;
        case TwoReturnCodeEnum::TwoReturnCodeOutOfRange:
            p_stringEnum = std::string("TwoReturnCodeOutOfRange");
            break;
        case TwoReturnCodeEnum::TwoReturnCodeNotCorverted:
            p_stringEnum = std::string("TwoReturnCodeNotCorverted");
            break;
        case TwoReturnCodeEnum::TwoReturnCodeFileError:
            p_stringEnum = std::string("TwoReturnCodeFileError");
            break;
        case TwoReturnCodeEnum::TwoReturnCodeFileEnd:
            p_stringEnum = std::string("TwoReturnCodeFileEnd");
            break;
        case TwoReturnCodeEnum::TwoReturnCodeSize:
            p_stringEnum = std::string("TwoReturnCodeSize");
            break;
        default:
            p_stringEnum = std::string("TwoReturnCodeEnum not converted ") + std::to_string(static_cast<size_t>(p_enum));
            l_returnCode = TwoReturnCodeEnum::TwoReturnCodeNotCorverted;
            break;
    }

    return l_returnCode;
}


std::string getLocalTime(const bool p_onlyNumbers)
{
          std::string l_timeString;
    const std::string l_zero("0");
    const std::string l_slash("/");
    const std::string l_space(" ");
    const std::string l_colon(":");
    const std::string l_dot(".");

    std::time_t l_time = time(0);
    struct std::tm* l_currentTime = std::localtime(&l_time);

    l_timeString += std::to_string(1900+l_currentTime->tm_year);

    if (9 > l_currentTime->tm_mon)
    {
        l_timeString += l_zero;
    }

    if (false == p_onlyNumbers)
    {
        l_timeString += l_slash;
    }

    l_timeString += std::to_string(1+l_currentTime->tm_mon);

    if (false == p_onlyNumbers)
    {
        l_timeString += l_slash;
    }

    if (10 > l_currentTime->tm_mday)
    {
        l_timeString += l_zero;
    }

    l_timeString += std::to_string(l_currentTime->tm_mday);

    if (false == p_onlyNumbers)
    {
        l_timeString += l_space;
    }

    if (10 > l_currentTime->tm_hour)
    {
        l_timeString += l_zero;
    }

    l_timeString += std::to_string(l_currentTime->tm_hour);

    if (false == p_onlyNumbers)
    {
        l_timeString += l_colon;
    }

    if (10 > l_currentTime->tm_min)
    {
        l_timeString += l_zero;
    }

    l_timeString += std::to_string(l_currentTime->tm_min);

    if (false == p_onlyNumbers)
    {
        l_timeString += l_colon;
    }

    if (10 > l_currentTime->tm_sec)
    {
        l_timeString += l_zero;
    }

    l_timeString += std::to_string(l_currentTime->tm_sec);

    return l_timeString;
}


void removeCharacterFromStdString(std::string& p_string, const char p_charToRemove)
{
    /* check the character is really ASCII */

    if (false == p_string.empty())
    {
        auto it_char = p_string.begin();

        while (p_string.end() != it_char)
        {
            if (p_charToRemove == *it_char)
            {
                it_char = p_string.erase(it_char);
            }
            else
            {
                ++it_char;
            }
        }
    }
}

void removeCharacterFromStdStringEdges(std::string& p_string, const char p_charToRemove)
{
    if (false == p_string.empty())
    {
        auto it_char = p_string.begin();

        while (p_string.end() != it_char)
        {
            if (p_charToRemove == *it_char)
            {
                it_char = p_string.erase(it_char);
            }
            else
            {
                break;
            }
        }

        it_char = p_string.end();

        --it_char;

        while (p_string.begin() != it_char)
        {
            if (p_charToRemove == *it_char)
            {
                it_char = p_string.erase(it_char);

                it_char = p_string.end();

                --it_char;
            }
            else
            {
                break;
            }
        }

    } /* end if (false == p_string.empty()) */

}



void splitStdString(const std::string& p_string,
                    std::vector<std::string>& p_stringPieces,
                    const char p_token,
                    const bool p_removeSpacesFromPieces)
{
    p_stringPieces.clear();

    if (false == p_string.empty())
    {
        std::string l_string(p_string);

        std::size_t l_positionInString = 0;

        while ((false == l_string.empty()) &&
               (std::string::npos != l_positionInString))
        {
            l_positionInString = l_string.find(p_token);

            std::string l_subString = l_string.substr(0, l_positionInString);

            if (true == p_removeSpacesFromPieces)
            {
                removeCharacterFromStdStringEdges(l_subString, ' ');
            }

            p_stringPieces.push_back(l_subString);

            l_string = l_string.substr(l_positionInString + 1, l_string.size() - l_positionInString);
        }

    } /* end if (false == p_string.empty()) */

}


std::string stdStringLatin1toUtf8(const char p_chars[], const size_t p_length)
{
    std::string l_string_out;

    for (size_t i = 0; i < p_length; ++i)
    {
        unsigned char l_char = 0x00;
        l_char |= p_chars[i];

        std::string l_adding;

        if (0x00 == l_char)
        {
            /* skip MULL */
        }
        else if (0x20 == l_char) /* translate the space into a non-breaking space */
        {
            l_char = 0xA0;
            l_adding.push_back(static_cast<char>(0xc0 | ((l_char & 0xc0) >> 6))); /* first byte, simplified since range is only 8-bits */
            l_adding.push_back(static_cast<char>(0x80 | (l_char & 0x3f)));
        }
        else if ((0x80 > l_char) &&
                 (0x1F < l_char))
        {
            l_adding.push_back(static_cast<char>(l_char));
        }
        else if (0xAD == l_char)
        {
            l_adding = std::string("-");
        }
        else if (0x9F < l_char)
        {
            l_adding.push_back(static_cast<char>(0xc0 | ((l_char & 0xc0) >> 6))); /* first byte, simplified since range is only 8-bits */
            l_adding.push_back(static_cast<char>(0x80 | (l_char & 0x3f)));
        }
        else
        {
            std::cerr << __func__ << " Character " << l_char << " not handled" << std::endl;
        }

        l_string_out += l_adding;
    }

    return l_string_out;
}



} /* end namespace two */
