/*!
 *  \file c_textfilereader.cpp
 *  \brief Main source of c_textfilereader test
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <two.h>


static const std::string k_programName = std::string("c_textfilereader");


void testFunction1()
{
    const std::string l_fileName1("/usr/include/math.h");
    const std::string l_fileName2("/usr/non/esisto.txt");
    const std::string l_fileName3("/usr/include/linux/limits.h");

    std::string l_stringEnum;
    std::string l_line;
    int         l_nLines = 0;

    two::C_TextFileReader l_textFileReader1;

    two::TwoReturnCodeEnum l_returnCode = l_textFileReader1.Open(l_fileName1);

    if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess != two::enumToStdString(l_returnCode, l_stringEnum))
    {
        std::cout << " " << __func__ << " Opening " << l_fileName1 << " returned " << static_cast<size_t>(l_returnCode) << " .\n";
    }
    else
    {
        std::cout << " " << __func__ << " Opening " << l_fileName1 << " returned " << l_stringEnum << " \n";
    }

    l_returnCode = l_textFileReader1.Open(l_fileName2);

    if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess != two::enumToStdString(l_returnCode, l_stringEnum))
    {
        std::cout << " " << __func__ << " Opening " << l_fileName2 << " returned " << static_cast<size_t>(l_returnCode) << " .\n";
    }
    else
    {
        std::cout << " " << __func__ << " Opening " << l_fileName2 << " returned " << l_stringEnum << " \n";
    }

    two::C_TextFileReader l_textFileReader2(l_fileName3);

    std::cout << " " << __func__ << " File " << l_fileName3 << " size is " << l_textFileReader2.GetFileSize() << " bytes.\n";

    std::cout << " " << __func__ << " File " << l_fileName3 << " filename is " << l_textFileReader2.GetFileName() << " .\n";

    std::cout << " " << __func__ << " File " << l_fileName3 << " is open? " << std::boolalpha << l_textFileReader2.IsOpen() << " .\n";

    std::cout << " " << __func__ << " File " << l_fileName3 << " is eof? " << std::boolalpha << l_textFileReader2.IsEof() << " .\n";

    std::cout << " " << l_fileName3 << " contents:\n\n";

    do
    {
        l_returnCode = l_textFileReader2.GetLine(l_line, l_nLines);

        if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess == l_returnCode)
        {
            std::cout << " " << l_nLines << "\t" << l_line << "\n";
        }

    } while (two::TwoReturnCodeEnum::TwoReturnCodeSuccess == l_returnCode);

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
