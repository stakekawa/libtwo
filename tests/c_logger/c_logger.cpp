/*!
 *  \file c_logger.cpp
 *  \brief Main source of c_logger test
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <two.h>


static const std::string k_programName = std::string("c_logger");


void testFunction1()
{
    LOGGER.SetLogThreshold(two::C_Logger::LoggerLevelEnum::LoggerLevelDebug);

    LOGGER_VERBOSE << "Verbose level" << LOGGER_ENDL;
    LOGGER_DEBUG   << "Debug level" << LOGGER_ENDL;
    LOGGER_INFO    << "Info level" << LOGGER_ENDL;
    LOGGER_WARN    << "Warn level" << LOGGER_ENDL;
    LOGGER_ERROR   << "Error level" << LOGGER_ENDL;
    LOGGER_FATAL   << "Fatal level" << LOGGER_ENDL;
    LOGGER_HIGH    << "Highlight level" << LOGGER_ENDL;

    for (size_t i = 0; i < 10; ++i)
    {
        LOGGER_INFO << __func__ << i << LOGGER_ENDL;

        if (0 != sleep(1))
        {
            LOGGER_ERROR << __func__ << "Failed to sleep" << LOGGER_ENDL;
        }
    }

    LOGGER.SetLogThreshold(two::C_Logger::LoggerLevelEnum::LoggerLevelWarn);

    LOGGER_WARN << __func__ << "No messages for 10 seconds because filtered" << LOGGER_ENDL;

    for (size_t i = 0; i < 10; ++i)
    {
        LOGGER_INFO << __func__ << i << LOGGER_ENDL;

        if (0 != sleep(1))
        {
            LOGGER_ERROR << __func__ << "Failed to sleep" << LOGGER_ENDL;
        }
    }

    LOGGER << LOGGER_CLOSE;

    LOGGER << LOGGER_START;

    LOGGER.SetLogThreshold(two::C_Logger::LoggerLevelEnum::LoggerLevelVerbose);

    for (size_t i = 0; i < 10; ++i)
    {
        LOGGER_INFO << __func__ << i << LOGGER_ENDL;

        if (0 != sleep(1))
        {
            LOGGER_ERROR << __func__ << "Failed to sleep" << LOGGER_ENDL;
        }
    }

    LOGGER << LOGGER_CLOSE;
}


void testFunction2()
{
    const std::string l_logFile("logfile.txt");

    std::cout << " Setting log on file " << l_logFile << "\n";

    two::TwoReturnCodeEnum l_returnCode = LOGGER.SetLogFunctionFile(l_logFile);

    if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess != l_returnCode)
    {
        std::string l_stringEnum;

        if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess != two::enumToStdString(l_returnCode, l_stringEnum))
        {
            std::cout << __func__ << " Failed to set logger to log file " << l_logFile << " with error " << static_cast<size_t>(l_returnCode) << "\n";
        }
        else
        {
            std::cout << __func__ << " Failed to set logger to log file " << l_logFile << " with error " << l_stringEnum << "\n";
        }
    }
    else
    {
        LOGGER.SetLogThreshold(two::C_Logger::LoggerLevelEnum::LoggerLevelVerbose);

        for (size_t i = 0; i < 10; ++i)
        {
            LOGGER_INFO << __func__ << i << LOGGER_ENDL;

            if (0 != sleep(1))
            {
                LOGGER_ERROR << __func__ << "Failed to sleep" << LOGGER_ENDL;
            }
        }

        std::cout << " Setting echo while log on file\n";

        LOGGER.SetEchoStdOut(true);

        for (size_t i = 10; i < 19; ++i)
        {
            LOGGER_INFO << __func__ << i << LOGGER_ENDL;

            if (0 != sleep(1))
            {
                LOGGER_ERROR << __func__ << "Failed to sleep" << LOGGER_ENDL;
            }
        }
    }

    std::cout << " Setting log on standard output\n";

    l_returnCode = LOGGER.SetLogFunctionStdCout();

    if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess != l_returnCode)
    {
        std::string l_stringEnum;

        if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess != two::enumToStdString(l_returnCode, l_stringEnum))
        {
            std::cout << __func__ << " Failed to set logger to standard output with error " << static_cast<size_t>(l_returnCode) << "\n";
        }
        else
        {
            std::cout << __func__ << " Failed to set logger to standard output with error " << l_stringEnum << "\n";
        }
    }
    else
    {
        LOGGER.SetLogThreshold(two::C_Logger::LoggerLevelEnum::LoggerLevelDebug);

        for (size_t i = 0; i < 10; ++i)
        {
            LOGGER_INFO << __func__ << i << LOGGER_ENDL;

            if (0 != sleep(1))
            {
                LOGGER_ERROR << __func__ << "Failed to sleep" << LOGGER_ENDL;
            }
        }
    }

    LOGGER << LOGGER_CLOSE;
}


int main(int argc, char* argv[])
{
    int l_exitValue = EXIT_SUCCESS;

    std::cout << "\n";

    std::cout << " " << k_programName << "\n\n";

    testFunction1();

    testFunction2();

    std::cout << std::endl;

    return l_exitValue;
}
