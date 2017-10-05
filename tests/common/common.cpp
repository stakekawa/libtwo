/*!
 *  \file common.cpp
 *  \brief Main source of common test
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <two.h>


static const std::string k_programName = std::string("common");


void testFunction1()
{
    std::cout << " " << "Two library version: " << two::getTwoLibVersion() << "\n\n";
}


void testFunction2()
{
          std::string l_emptyString;
    const std::string l_testString("This is a test. Removing 'i'.");
          std::string l_parseString(l_testString);

    const char l_char = 'i';

    two::removeCharacterFromStdString(l_emptyString, 'i');
    two::removeCharacterFromStdString(l_parseString, l_char);

    std::cout << " Empty string is still empty? " << l_emptyString << "\n";
    std::cout << " " << l_testString << " -> " << l_parseString << "\n\n";
}


void testFunction3()
{
    const std::string l_testString("This is a test. Removing 'i'.");
    const char l_char = ' ';
    std::vector<std::string> l_pieces;

    two::splitStdString(l_testString, l_pieces, l_char, false);

    std::cout << " String: " << l_testString << " divided using '" << l_char << "' -> ";

    for (size_t i = 0; i < l_pieces.size(); ++i)
    {
        std::cout << i << ") " << l_pieces[i] << " ";
    }

    std::cout << "\n";

    two::splitStdString(l_testString, l_pieces, '.', false);

    std::cout << " String: " << l_testString << " divided using '.' -> ";

    for (size_t i = 0; i < l_pieces.size(); ++i)
    {
        std::cout << i << ") " << l_pieces[i] << " ";
    }

    std::cout << "\n";

    two::splitStdString(l_testString, l_pieces, '.', true);

    std::cout << " String: " << l_testString << " divided using '.' -> ";

    for (size_t i = 0; i < l_pieces.size(); ++i)
    {
        std::cout << i << ") " << l_pieces[i] << " ";
    }

    std::cout << "\n\n";
}


void testFunction4()
{
    std::vector<char> l_chars;

    for (unsigned char i = 0x20; i < 0x7f; ++i)
    {
        l_chars.push_back(i);
    }

    for (unsigned char i = 0xa0; i<0xff; i++)
    {
        if ((0x81 == i) ||
            (0x8d == i) ||
            (0x8f == i) ||
            (0x90 == i) ||
            (0x9d == i))
        {
            continue;
        }

        l_chars.push_back(i);
    }

    std::string l_convertedString = two::stdStringLatin1toUtf8(&l_chars[0], l_chars.size());

    std::cout << " Converted ISO-8859-1 string is ";

    for (const char l_char : l_convertedString)
    {
        std::cout << l_char;
    }

    std::cout << "\n\n";
}


void testFunction5()
{
    std::cout << " Time full format:  " << two::getLocalTime(false) << "\n";
    std::cout << " Time only numbers: " << two::getLocalTime(true)  << "\n";
}


int main(int argc, char* argv[])
{
    int l_exitValue = EXIT_SUCCESS;

    std::cout << "\n";

    std::cout << " " << k_programName << "\n\n";

    testFunction1();

    testFunction2();

    testFunction3();

    testFunction4();

    testFunction5();

    std::cout << std::endl;

    return l_exitValue;
}
