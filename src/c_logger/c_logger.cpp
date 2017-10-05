/*!
 *  \file c_logger.cpp
 *
 *  \brief This file contains the implementation of c_logger class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */


#include <array>            // std::array
#include <iostream>         // std::cerr
#include <thread>           // std::thread
#include "c_logger.h"
#include "common.h"
#include "colorizeString.h"


namespace two {


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


C_Logger* C_Logger::s_instance               = NULL;

static constexpr int    k_sleepAfterDisconnect  = 5; /* milliseconds */
static constexpr size_t k_messageCounterDefault = 0;
static size_t           g_messageCounter        = k_messageCounterDefault;
static bool             g_validSheel            = true;

static const std::array<StdStringColorEnum,
                        static_cast<size_t>(C_Logger::LoggerLevelEnum::LoggerLevelSize)> k_logColors = { StdStringColorEnum::StdStringColorWhite,
                                                                                                         StdStringColorEnum::StdStringColorWhite,
                                                                                                         StdStringColorEnum::StdStringColorWhite,
                                                                                                         StdStringColorEnum::StdStringColorYellow,
                                                                                                         StdStringColorEnum::StdStringColorRed,
                                                                                                         StdStringColorEnum::StdStringColorBoldRed,
                                                                                                         StdStringColorEnum::StdStringColorBoldCyan };

/*                                                                            */
/* Private members                                                            */
/*                                                                            */


TwoReturnCodeEnum enumToStdString(const C_Logger::LoggerLevelEnum p_enum, std::string& p_stringEnum)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    switch (p_enum)
    {
        case C_Logger::LoggerLevelEnum::LoggerLevelVerbose:
            p_stringEnum = std::string("Verbose");
            break;
        case C_Logger::LoggerLevelEnum::LoggerLevelDebug:
            p_stringEnum = std::string("Debug");
            break;
        case C_Logger::LoggerLevelEnum::LoggerLevelInfo:
            p_stringEnum = std::string("Info");
            break;
        case C_Logger::LoggerLevelEnum::LoggerLevelWarn:
            p_stringEnum = std::string("Warn");
            break;
        case C_Logger::LoggerLevelEnum::LoggerLevelError:
            p_stringEnum = std::string("Error");
            break;
        case C_Logger::LoggerLevelEnum::LoggerLevelFatal:
            p_stringEnum = std::string("Fatal");
            break;
        case C_Logger::LoggerLevelEnum::LoggerLevelHighligth:
            p_stringEnum = std::string("Highlight");
            break;
        case C_Logger::LoggerLevelEnum::LoggerLevelSize:
            p_stringEnum = std::string("Size");
            break;
        default:
            p_stringEnum = std::string("LoggerLevelEnum not converted ") + std::to_string(static_cast<size_t>(p_enum));
            l_returnCode = TwoReturnCodeEnum::TwoReturnCodeNotCorverted;
            break;
    }

    return l_returnCode;
}


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* static */
C_Logger& C_Logger::Instance()
{
    if (NULL == s_instance)
    {
        s_instance = new C_Logger();
    }

    return *s_instance;
}


#ifdef __SSE__
C_Logger& C_Logger::operator<<(const __m128d& p_value)
{
    const unsigned int l_pid = getThreadPid();

    /* now access the __m256d structure */

    union
    {
        __m128d tempv;
        double  tempd[2];
    };

    tempv = p_value;

    std::string l_string;
    l_string.push_back(s_loggerCharBrkOpen);
    l_string += std::to_string(tempd[0]);
    l_string.push_back(s_loggerCharComma);
    l_string.push_back(s_loggerCharSpace);
    l_string += std::to_string(tempd[1]);
    l_string.push_back(s_loggerCharComma);
    l_string.push_back(s_loggerCharSpace);
    l_string.push_back(s_loggerCharBrkClose);

    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << l_string << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();

    return *this;
}
#endif // __SSE__


#ifdef __AVX__
C_Logger& C_Logger::operator<<(const __m256d& p_value)
{
    const unsigned int l_pid = getThreadPid();

    /* now access the __m256d structure */

    union
    {
        __m256d tempv;
        double  tempd[4];
    };

    tempv = p_value;

    std::string l_string;
    l_string.push_back(s_loggerCharBrkOpen);
    l_string += std::to_string(tempd[0]);
    l_string.push_back(s_loggerCharComma);
    l_string.push_back(s_loggerCharSpace);
    l_string += std::to_string(tempd[1]);
    l_string.push_back(s_loggerCharComma);
    l_string.push_back(s_loggerCharSpace);
    l_string += std::to_string(tempd[2]);
    l_string.push_back(s_loggerCharComma);
    l_string.push_back(s_loggerCharSpace);
    l_string += std::to_string(tempd[3]);
    l_string.push_back(s_loggerCharBrkClose);

    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << l_string << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();

    return *this;
}
#endif // __AVX__


C_Logger& C_Logger::operator<<(const char p_char)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    std::string l_string;
    l_string.resize(1, p_char);
    m_messages[l_pid].message << l_string << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(const size_t p_value)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << p_value << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(const unsigned int p_value)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << p_value << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(const int p_value)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << p_value << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(const int64_t p_value)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << p_value << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(const double p_value)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << std::fixed << p_value << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(const float p_value)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << std::fixed << p_value << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(const std::string& p_string)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << p_string << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(std::string&& p_string)
{
    const unsigned int l_pid = getThreadPid();
    m_messages[l_pid].mutex.lock();
    m_messages[l_pid].message << p_string << s_loggerCharSpace;
    m_messages[l_pid].mutex.unlock();
    return *this;
}


C_Logger& C_Logger::operator<<(const LoggerCmdEnum p_enum)
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);

    const unsigned int l_pid = getThreadPid();

    switch (p_enum)
    {
        case LoggerCmdEnum::LoggerCmdEndl:
        {
            m_messages[l_pid].mutex.lock();    /* lock    */
            std::shared_ptr<LogQueue_t> l_message = std::make_shared<LogQueue_t>();
            l_message->pid      = l_pid;
            l_message->logLevel = m_messages[l_pid].logLevel;
            l_message->message  = m_messages[l_pid].message.str();
            l_message->time     = std::string(" ") + getLocalTime(false) + std::string(" ");
            m_messages[l_pid].message.str("");
            m_messages[l_pid].message.clear();
            m_messages[l_pid].mutex.unlock();  /* unlock */

            if (false == l_message->message.empty())
            {
                l_message->message = l_message->message.substr(0, l_message->message.size() - 1); /* remove last character equal to s_loggerCharSpace */

                m_queueMutex.lock();
                m_queue.push(l_message);
                m_queueMutex.unlock();

                WakeUp();
            }
        }
            break;
        case LoggerCmdEnum::LoggerCmdReset:
            m_messages[l_pid].mutex.lock();
            m_messages[l_pid].message.str("");
            m_messages[l_pid].message.clear();
            m_messages[l_pid].mutex.unlock();
            break;
        case LoggerCmdEnum::LoggerCmdStart:
            Start();
            break;
        case LoggerCmdEnum::LoggerCmdClose:
            Stop();
            break;
        default:
            break;
    }

    return *this;
}


C_Logger& C_Logger::operator<<(const LoggerLevelEnum p_logLevel)
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);

    const unsigned int l_pid = getThreadPid();

    m_messages[l_pid].logLevel = p_logLevel;

    *this << LOGGER_ENDL;

    return *this;
}


void C_Logger::SetLogThreshold(const LoggerLevelEnum p_logThreshold)
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);

    m_logThreshold = p_logThreshold;

    std::string l_stringEnum;

    TwoReturnCodeEnum l_returnCode = enumToStdString(p_logThreshold, l_stringEnum);

    if (TwoReturnCodeEnum::TwoReturnCodeSuccess == l_returnCode)
    {
        *this << LoggerLevelEnum::LoggerLevelHighligth << "Setting log threshold to" << l_stringEnum << LOGGER_ENDL;
    }
    else
    {
        *this << LoggerLevelEnum::LoggerLevelHighligth << "Setting log threshold to" << static_cast<size_t>(p_logThreshold) << LOGGER_ENDL;
    }
}


C_Logger::LoggerLevelEnum C_Logger::GetLogThreshold() const
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);

    return m_logThreshold;
}


void C_Logger::SetUseColor(const bool p_useColor)
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);

    m_useColor = p_useColor;
}


bool C_Logger::GetUseColor() const
{
    std::lock_guard<std::recursive_mutex> l_lock(m_mutex);

    return m_useColor;
}


/*                                                                            */
/* Protected members                                                          */
/*                                                                            */


/* virtual */
bool C_Logger::PrepareToStart()
{
    CheckConnection();

    return true;
}


/* virtual */
bool C_Logger::PrepareToStop()
{
    return true;
}


/* virtual */
bool C_Logger::BeforeWork()
{
    /* set logger synchronous during stop */

    SetStartStopAsync(false);

    return true;
}


/* virtual */
bool C_Logger::AfterWork()
{
    Disconnect();

    /* set logger asynchronous during start */

    SetStartStopAsync(true);

    /* reset to zero the message counter */

    g_messageCounter = k_messageCounterDefault;

    return true;
}


bool C_Logger::StopAfterWakeUpIfStopped()
{
    return false;
}


/* virtual */
bool C_Logger::WorkerJob()
{
    CheckConnection();

    m_queueMutex.lock();
    size_t l_queueLenght = m_queue.size();
    m_queueMutex.unlock();

    while (0 < l_queueLenght)
    {
        m_queueMutex.lock();
        std::shared_ptr<LogQueue_t> l_message = m_queue.front();
        m_queue.pop();
        m_queueMutex.unlock();

        m_logFunction(*l_message);

        m_queueMutex.lock();
        l_queueLenght = m_queue.size();
        m_queueMutex.unlock();
    }

    return true;
}


/*                                                                            */
/* Private members                                                            */
/*                                                                            */


C_Logger::C_Logger() :
    C_Worker(std::to_string(getThreadPid()) + std::string(" ") + std::to_string(static_cast<size_t>(LoggerLevelEnum::LoggerLevelHighligth)) + std::string(" ") + std::string(LOGGER_NAME_DEFAULT)),
    m_connected(LoggerConnectedEnum::LoggerConnectedUnknown),
    m_messages(),
    m_logThreshold(LoggerLevelEnum::LoggerLevelInfo),
    m_useColor(true),
    m_logFunction([this](LogQueue_t& p_logQueue){ DefaultLogFunction(p_logQueue); }),
    m_queue(),
    m_queueMutex(),
    m_mutex()
{
    C_Worker::SetTimeout(LOGGER_WAIT_TIMEOUT_DEFAULT);

    /* query if created in a valid shell */

    g_validSheel = isValidShell();

    if (false == Connect())
    {
        std::cerr << GetName() << " Failed to connect!" << std::endl;
    }
    else
    {
        m_connected = LoggerConnectedEnum::LoggerConnectedYes;

        LogQueue_t l_logQueue;

        l_logQueue.pid      = getThreadPid();
        l_logQueue.logLevel = LoggerLevelEnum::LoggerLevelHighligth;
        l_logQueue.message  = std::string("Hello!");
        l_logQueue.time     = std::string(" ") + getLocalTime(false) + std::string(" ");

        m_logFunction(l_logQueue);
    }

    C_Worker::Start();
}


/* virtual */
C_Logger::~C_Logger()
{

}


bool C_Logger::Connect()
{
    return true;
}


void C_Logger::Disconnect()
{
    LogQueue_t l_logQueue;

    l_logQueue.pid      = getThreadPid();
    l_logQueue.logLevel = LoggerLevelEnum::LoggerLevelHighligth;
    l_logQueue.message  = std::string("Bye Bye!");
    l_logQueue.time     = std::string(" ") + getLocalTime(false) + std::string(" ");

    m_logFunction(l_logQueue);

    std::this_thread::sleep_for(std::chrono::milliseconds(k_sleepAfterDisconnect));

    m_connected = LoggerConnectedEnum::LoggerConnectedNo;
}


void C_Logger::CheckConnection()
{
    if (LoggerConnectedEnum::LoggerConnectedYes == m_connected)
    {
        /* nothing to do */
    }
    else if (false == Connect())
    {
        std::cerr << GetName() << " Failed to connect!" << std::endl;

        m_connected = LoggerConnectedEnum::LoggerConnectedNo;
    }
    else
    {
        m_connected = LoggerConnectedEnum::LoggerConnectedYes;

        LogQueue_t l_logQueue;

        l_logQueue.pid      = getThreadPid();
        l_logQueue.logLevel = LoggerLevelEnum::LoggerLevelHighligth;
        l_logQueue.message  = std::string("Reconnected!");
        l_logQueue.time     = std::string(" ") + getLocalTime(false) + std::string(" ");
    }
}


void C_Logger::DefaultLogFunction(LogQueue_t& p_logQueue)
{
    std::string l_stringEnum;

    if (m_logThreshold > p_logQueue.logLevel)
    {
        /* logging below the threshold */
    }
    else
    {
        ColorizeMessage(p_logQueue);
        std::cout <<  p_logQueue.pid << " " << static_cast<size_t>(p_logQueue.logLevel) << p_logQueue.time << g_messageCounter << " " << p_logQueue.message << "\n";
        ++g_messageCounter;
    }
}


void C_Logger::ColorizeMessage(LogQueue_t& p_logQueue) const
{
    if ((true == g_validSheel) &&
        (true == m_useColor))
    {
        p_logQueue.message = colorizeStdString(p_logQueue.message, k_logColors[static_cast<size_t>(p_logQueue.logLevel)]);
    }
}


} /* namespace two */
