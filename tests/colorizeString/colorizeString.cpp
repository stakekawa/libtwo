/*!
 *  \file colorizeString.cpp
 *  \brief Main source of colorizeString test
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <two.h>


static const std::string k_programName = std::string("colorizeString");


void testFunction1()
{
    const std::string l_string("This is a test: ");

    std::cout << " " << two::colorizeStdStringRed(l_string + std::string("red"))                << "\n";
    std::cout << " " << two::colorizeStdStringGreen(l_string + std::string("green"))            << "\n";
    std::cout << " " << two::colorizeStdStringYellow(l_string + std::string("yellow"))          << "\n";
    std::cout << " " << two::colorizeStdStringBlue(l_string + std::string("blue"))              << "\n";
    std::cout << " " << two::colorizeStdStringViolet(l_string + std::string("violet"))          << "\n";
    std::cout << " " << two::colorizeStdStringCyan(l_string + std::string("cyan"))              << "\n";
    std::cout << " " << two::colorizeStdStringWhite(l_string + std::string("white"))            << "\n";
    std::cout << " " << two::colorizeStdStringBoldRed(l_string + std::string("bold red"))       << "\n";
    std::cout << " " << two::colorizeStdStringBoldGreen(l_string + std::string("bold green"))   << "\n";
    std::cout << " " << two::colorizeStdStringBoldYellow(l_string + std::string("bold yellow")) << "\n";
    std::cout << " " << two::colorizeStdStringBoldBlue(l_string + std::string("bold blue"))     << "\n";
    std::cout << " " << two::colorizeStdStringBoldViolet(l_string + std::string("bold violet")) << "\n";
    std::cout << " " << two::colorizeStdStringBoldCyan(l_string + std::string("bold cyan"))     << "\n";
    std::cout << " " << two::colorizeStdStringBoldWhite(l_string + std::string("bold white"))   << "\n";
}


int main(int argc, char* argv[])
{
    int l_exitValue = EXIT_SUCCESS;

    std::cout << "\n";

    std::cout << " " << k_programName << "\n\n";

    testFunction1();

    std::cout << std::endl;

    return l_exitValue;
}
