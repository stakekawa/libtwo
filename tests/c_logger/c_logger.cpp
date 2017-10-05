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


static const std::string k_programName = std::string("c_logger");


void testFunction1()
{
    LOGGER.SetLogThreshold(two::C_Logger::LoggerLevelEnum::LoggerLevelDebug);

    LOGGER_VERBOSE << "verbose level" << LOGGER_ENDL;
    LOGGER_DEBUG   << "debug level" << LOGGER_ENDL;
    LOGGER_INFO    << "info level" << LOGGER_ENDL;
    LOGGER_WARN    << "warn level" << LOGGER_ENDL;
    LOGGER_ERROR   << "error level" << LOGGER_ENDL;
    LOGGER_FATAL   << "fatal level" << LOGGER_ENDL;
    LOGGER_HIGH    << "highlight level" << LOGGER_ENDL;

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


int main(int argc, char* argv[])
{
    int l_exitValue = EXIT_SUCCESS;

    std::cout << "\n";

    std::cout << " " << k_programName << "\n\n";

    testFunction1();

    std::cout << std::endl;

    return l_exitValue;
}
