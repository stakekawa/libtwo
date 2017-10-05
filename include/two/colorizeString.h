/*!
 *  \file colorizeStdString.h
 *
 *  \brief This file collects the declaration of functions to color
           a std::string suitable for std::cout << or std::cerr <<
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */


#ifndef TWO_COLORIZEDSTRING_H
#define TWO_COLORIZEDSTRING_H


#include <string> // std::string


namespace two {


/*!
 *  \brief The StdStringColorEnum identifies available colors
 */
enum class StdStringColorEnum : size_t
{
    StdStringColorRed,         /*!< Red color         */
    StdStringColorGreen,       /*!< Green color       */
    StdStringColorYellow,      /*!< Yellow color      */
    StdStringColorBlue,        /*!< Blue color        */
    StdStringColorViolet,      /*!< Violet color      */
    StdStringColorCyan,        /*!< Cyan color        */
    StdStringColorWhite,       /*!< White color       */
    StdStringColorBoldRed,     /*!< Bold Red color    */
    StdStringColorBoldGreen,   /*!< Bold Green color  */
    StdStringColorBoldYellow,  /*!< Bold Yellow color */
    StdStringColorBoldBlue,    /*!< Bold Blue color   */
    StdStringColorBoldViolet,  /*!< Bold Violet color */
    StdStringColorBoldCyan,    /*!< Bold Cyan color   */
    StdStringColorBoldWhite,   /*!< Bold White color  */
    StdStringColorSize         /*!< Number of colors  */
};


/*!
 *  \brief Colorize a std::string with requested color to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *  \param p_color StdStringColorEnum with requested color
 *
 *  \return a new string colorized with requested color
 */
std::string colorizeStdString(const std::string& p_string, StdStringColorEnum&& p_color);


/*!
 *  \brief Colorize a std::string with requested color to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *  \param p_color StdStringColorEnum with requested color
 *
 *  \return a new string colorized with requested color
 */
std::string colorizeStdString(const std::string& p_string, const StdStringColorEnum& p_color);


/*!
 *  \brief Colorize a std::string with red to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with red
 */
inline std::string colorizeStdStringRed(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorRed);
}


/*!
 *  \brief Colorize a std::string with green to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with green
 */
inline std::string colorizeStdStringGreen(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorGreen);
}


/*!
 *  \brief Colorize a std::string with yellow to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with yellow
 */
inline std::string colorizeStdStringYellow(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorYellow);
}


/*!
 *  \brief Colorize a std::string with blue to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with blue
 */
inline std::string colorizeStdStringBlue(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorBlue);
}


/*!
 *  \brief Colorize a std::string with violet to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with violet
 */
inline std::string colorizeStdStringViolet(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorViolet);
}


/*!
 *  \brief Colorize a std::string with cyan to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with cyan
 */
inline std::string colorizeStdStringCyan(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorCyan);
}


/*!
 *  \brief Colorize a std::string with white to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with white
 */
inline std::string colorizeStdStringWhite(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorWhite);
}


/*!
 *  \brief Colorize a std::string with bold red to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with bold red
 */
inline std::string colorizeStdStringBoldRed(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorBoldRed);
}


/*!
 *  \brief Colorize a std::string with bold green to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with bold green
 */
inline std::string colorizeStdStringBoldGreen(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorBoldGreen);
}


/*!
 *  \brief Colorize a std::string with bold yellow to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with bold yellow
 */
inline std::string colorizeStdStringBoldYellow(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorBoldYellow);
}


/*!
 *  \brief Colorize a std::string with bold blue to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with bold blue
 */
inline std::string colorizeStdStringBoldBlue(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorBoldBlue);
}


/*!
 *  \brief Colorize a std::string with bold violet to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with bold violet
 */
inline std::string colorizeStdStringBoldViolet(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorBoldViolet);
}


/*!
 *  \brief Colorize a std::string with bold cyan to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with bold cyan
 */
inline std::string colorizeStdStringBoldCyan(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorBoldCyan);
}


/*!
 *  \brief Colorize a std::string with bold white to use on std::cout or std::cerr
 *
 *  \param p_string reference to std::string to colorize
 *
 *  \return new string colorized with bold white
 */
inline std::string colorizeStdStringBoldWhite(const std::string& p_string)
{
    return colorizeStdString(p_string, StdStringColorEnum::StdStringColorBoldWhite);
}


} /* end namespace two */


#endif // TWO_COLORIZEDSTRING_H
