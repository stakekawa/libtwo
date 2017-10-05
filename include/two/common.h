/*!
 *  \file common.h
 *
 *  \brief This file collects the declaration of common stuff used in the C++
           Two library.
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */


#ifndef TWO_COMMON_H
#define TWO_COMMON_H


#include <cstdio>        // stdout
#include <string>        // std::string
#include <sys/syscall.h> // syscall
#include <vector>        // std::vector
#include <unistd.h>      // syscall


namespace two {


/*!
 *  \brief Return a std::string containing the Two library version
 */
std::string getTwoLibVersion();


/*                                                                            */
/* enumerations                                                               */
/*                                                                            */


enum class TwoReturnCodeEnum
{
    TwoReturnCodeSuccess,      /*!< No error                      */
    TwoReturnCodeError,        /*!< Generic error                 */
    TwoReturnCodeOutOfRange,   /*!< Out of range error            */
    TwoReturnCodeNotCorverted, /*!< Conversion failed             */
    TwoReturnCodeFileError,    /*!< Generic file error            */
    TwoReturnCodeSize          /*!< The number of the enumeration */
};


/*!
 *  \brief Convert a TwoReturnCodeEnum to a human readable std::String
 *
 *  \param p_enum enumeration to convert
 *  \param p_stringEnum std::string with text
 *
 *  \return TwoReturnCodeSuccess or TwoReturnCodeNotCorverted
 */
TwoReturnCodeEnum enumToStdString(const TwoReturnCodeEnum p_enum, std::string& p_stringEnum);


/*                                                                            */
/* console                                                                    */
/*                                                                            */


/*!
 *  \brief Query if the application is running in a valid shell
 */
inline bool isValidShell()
{
    return isatty(fileno(stdout));
}


/*                                                                            */
/* time                                                                    */
/*                                                                            */


/*!
 *  \brief Get the current local time
 *
 *  \param p_onlyNumbers if true time format is YYYYMMDDHHmmss otherwise YYYY/MM/DD HH:mm::ss
 *
 *  \return a std::string filled with time
 */
std::string getLocalTime(const bool p_onlyNumbers);


/*                                                                            */
/* threads                                                                    */
/*                                                                            */


inline unsigned int getThreadPid()
{
    const pid_t p_tid = syscall(SYS_gettid);
    return static_cast<unsigned int>(0xFFFFFFFF & p_tid);
}


/*                                                                            */
/* std::string functions                                                      */
/*                                                                            */


/*!
 *  \brief Remove all occurrencies of an ASCII character from a std::string
 *
 *  \param p_string reference to std::string which character is removed from
 *  \param p_charToRemove
 */
void removeCharacterFromStdString(std::string& p_string, const char p_charToRemove);


/*!
 *  \brief Remove all contiguous occurrencies of an ASCII character from the beginning
 *         and the end of a std::string
 *
 *  \param p_string reference to std::string which character is removed from
 *  \param p_charToRemove
 */
void removeCharacterFromStdStringEdges(std::string& p_string, const char p_charToRemove);


/*!
 *  \brief Split a std::string in pieces using the parameter token
 *
 *  \param p_string reference to std::string to split
 *  \param p_stringPieces reference to std::vector of std::string which is filled with splitted pieces
 *  \param p_token token to use to split
 *  \param p_removeSpacesFromPieces set true to remove spaces from begin and end of each splitted pieces
 */
void splitStdString(const std::string& p_string,
                    std::vector<std::string>& p_stringPieces,
                    const char p_token,
                    const bool p_removeSpacesFromPieces);

/*!
 *  \brief Convert an array of characters coded in ISO-8859-1 (Latin 1) to a std::string coded in UTF-8
 *
 *  \param p_chars array of characters coded in ISO-8859-1 (Latin 1)
 *  \param p_length lenght of the array
 *
 *  \return std::string with p_chars converted to UTF-8
 */
std::string stdStringLatin1toUtf8(const char p_chars[], const size_t p_length);


} /* end namespace two */


#endif // TWO_COMMON_H
