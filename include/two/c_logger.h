/*!
 *  \file c_logger.h
 *
 *  \brief This file contains the declaration of c_logger class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */


#ifndef TWO_C_LOGGER_H
#define TWO_C_LOGGER_H


#if defined(__AVX__) || defined(__SSE__)
#include "immintrin.h"
#endif

//#include <cstdint>
#include <map>        // std::map
#include <memory>     // std::shared_ptr
#include <mutex>      // std::mutex, std::recursive_mutex
#include <queue>      // std::queue
#include <sstream>    // std::stringstream
#include <string>     // std::string
#include "c_worker.h"


#define LOGGER_ENDL                 two::C_Logger::LoggerCmdEnum::LoggerCmdEndl
#define LOGGER_RESET                two::C_Logger::LoggerCmdEnum::LoggerCmdReset
#define LOGGER_START                two::C_Logger::LoggerCmdEnum::LoggerCmdStart
#define LOGGER_CLOSE                two::C_Logger::LoggerCmdEnum::LoggerCmdClose
#define LOGGER                                         two::C_Logger::Instance()

#define LOGGER_VERBOSE              LOGGER << two::C_Logger::LoggerLevelEnum::LoggerLevelVerbose
#define LOGGER_DEBUG                LOGGER << two::C_Logger::LoggerLevelEnum::LoggerLevelDebug
#define LOGGER_INFO                 LOGGER << two::C_Logger::LoggerLevelEnum::LoggerLevelInfo
#define LOGGER_WARN                 LOGGER << two::C_Logger::LoggerLevelEnum::LoggerLevelWarn
#define LOGGER_ERROR                LOGGER << two::C_Logger::LoggerLevelEnum::LoggerLevelError
#define LOGGER_FATAL                LOGGER << two::C_Logger::LoggerLevelEnum::LoggerLevelFatal
#define LOGGER_HIGH                 LOGGER << two::C_Logger::LoggerLevelEnum::LoggerLevelHighligth


#define LOGGER_NAME_DEFAULT                                             "Logger"
#define LOGGER_WAIT_TIMEOUT_DEFAULT                                         5000 /* milliseconds */


namespace two {


/*!
 *  \brief The C_Logger class provides a unique point to log message for and application.
 *         It is fully multithreading and it allows logging from different threads. Time
 *         ordering should be respected by queueing messages as LoggerCmdEnum::LoggerCmdEndl
 *         is inserted. Defines are provided to simplify the use of the C_Logger object.
 *         The C_Logger object automatically start in its constructor.
 *
 *         Examples:
 *
 *         - LOGGER << "Test message" << 4 << std::string("Foo Bar") << std::vector<double>(10, 0) << LOGGER_ENDL;
 *         - LOGGER << LOGGER_CLOSE;
 *         - LOGGER << LOGGER_START;
 */
class C_Logger : C_Worker
{


public:

    /*!
     *  \brief The LoggerLevelEnum enumeration defines the handled logging levels
     */
    enum class LoggerLevelEnum : size_t
    {
        LoggerLevelVerbose,   /*< Verbose logging level: really a lot of messages       */
        LoggerLevelDebug,     /*< Debugging logging level: debugging messages           */
        LoggerLevelInfo,      /*< Info logging level: information messages              */
        LoggerLevelWarn,      /*< Warn logging level: warning in the application        */
        LoggerLevelError,     /*< Error logging level: handled error in the application */
        LoggerLevelFatal,     /*< Fatal logging level: the application usually exits    */
        LoggerLevelHighligth, /*< Highlight logging level: important messages           */
        LoggerLevelSize       /*< Number of logging levels                              */
    };

    /*!
     *  \brief The LoggerCmdEnum enumerations defines commands to be passed to the C_Logger object
     */
    enum class LoggerCmdEnum : size_t
    {
        LoggerCmdEndl,  /*!< Request end of line and log the inserted data since previous LoggerCmdEndl */
        LoggerCmdReset, /*!< Reset the current date inserted since previous LoggerCmdEndl               */
        LoggerCmdStart, /*!< Start the C_Logger object if stopped                                       */
        LoggerCmdClose, /*!< Close the log and stop the C_Logger object                                 */
        LoggerCmdSize   /*!< Number of LoggerCmdEnum enumerations                                       */
    };

    /*!
     *  \brief The LoggerConnectedEnum enumerations maps the C_Logger object connection status
     */
    enum class LoggerConnectedEnum : size_t
    {
        LoggerConnectedYes,                          /*!< The C_Logger object is connected                        */
        LoggerConnectedNo,                           /*!< The C_Logger object is disconnected                     */
        LoggerConnectedUnknown,                      /*!< The connection status of the C_Logger object is unknown */
        LoggerConnectedSize = LoggerConnectedUnknown /*!< Alias to LoggerConnectedUnknown                         */
    };

    /*!
     * \brief The LogMux_t struct is used as a POD to group logLevel, message and the mutex controlling
     *        access to the former two data members of the LogMux_t struct
     */
    struct LogMux_t
    {
        LoggerLevelEnum              logLevel;
        std::stringstream            message;
        mutable std::recursive_mutex mutex;
    };

    /*!
     *  \brief The LogQueue_t struct is used as a POD to queue messages to be logged after LoggerCmdEndl is received
     */
    struct LogQueue_t
    {
        unsigned int    pid;
        LoggerLevelEnum logLevel;
        std::string     message;
        std::string     time;
    };


    /*!
     *  \brief Singleton instance
     */
    static C_Logger& Instance();

#ifdef __SSE__
    C_Logger& operator<<(const __m128d& p_value);
#endif // __SSE__

#ifdef __AVX__
    C_Logger& operator<<(const __m256d& p_value);
#endif // __AVX__

    C_Logger& operator<<(const bool p_value) { if (true == p_value) { return *this << std::string("true"); } else { return *this << std::string("false"); } }

    C_Logger& operator<<(const char p_char);

    C_Logger& operator<<(const size_t p_value);

    C_Logger& operator<<(const unsigned int p_value);

    C_Logger& operator<<(const int p_value);

    C_Logger& operator<<(const int64_t p_value);

    C_Logger& operator<<(const double p_value);

    C_Logger& operator<<(const float p_value);

    C_Logger& operator<<(const char* p_string) { if (NULL == p_string) { return *this << "NULL"; } else { return *this << std::string(p_string); } }

    C_Logger& operator<<(const std::string& p_string);

    C_Logger& operator<<(std::string&& p_string);

    template <typename T>
    C_Logger& operator<<(const std::vector<T>& p_vector);

    C_Logger& operator<<(const LoggerCmdEnum p_enum);

    C_Logger& operator<<(const LoggerLevelEnum p_logLevel);

    bool IsConnected() const { return LoggerConnectedEnum::LoggerConnectedYes == m_connected; }

    /*!
     *  \brief Set the minimum log level. All messages below this thresholds are filtered and not
     *         logged using the logging function.
     *
     *  \param p_logThreshold mininum log level
     */
    void SetLogThreshold(const LoggerLevelEnum p_logThreshold);

    /*!
     *  \brief Get the mininum log level
     */
    LoggerLevelEnum GetLogThreshold() const;

    /*!
     *  \brief Set whether to colorize the output or not
     *
     *  \param p_useColor true / false
     */
    void SetUseColor(const bool p_useColor);

    /*!
     *  \brief Get if the output is colorized or not
     */
    bool GetUseColor() const;


protected:

    bool PrepareToStart() override;
    bool PrepareToStop() override;
    bool BeforeWork() override;
    bool AfterWork() override;
    bool StopAfterWakeUpIfStopped() override;
    bool WorkerJob() override;


private:

    /*!
     *  \brief Constructor
     */
    C_Logger();

    /*!
     *  \brief Destructor
     */
    virtual ~C_Logger();

    /*!
     *  \brief Copy constructor (deleted)
     */
    C_Logger(const C_Logger&) = delete;

    /*!
     *  \brief Copy assignment operator (deleted)
     */
    C_Logger& operator=(const C_Logger&) = delete;

    bool Connect();

    void Disconnect();

    void CheckConnection();

    void DefaultLogFunction(LogQueue_t& p_logQueue);

    void ColorizeMessage(LogQueue_t& p_logQueue) const;

    static constexpr char                    s_loggerCharComma    = ',';
    static constexpr char                    s_loggerCharSpace    = ' ';
    static constexpr char                    s_loggerCharBrkOpen  = '[';
    static constexpr char                    s_loggerCharBrkClose = ']';
    static constexpr char                    s_loggerCharParOpen  = '(';
    static constexpr char                    s_loggerCharParClose = ')';

    static C_Logger*                         s_instance;
    LoggerConnectedEnum                      m_connected;
    std::map<unsigned int, LogMux_t>         m_messages;

    LoggerLevelEnum                          m_logThreshold;
    bool                                     m_useColor;

    std::function<void(LogQueue_t&)>         m_logFunction;

    std::queue<std::shared_ptr<LogQueue_t> > m_queue;
    std::mutex                               m_queueMutex;

    mutable std::recursive_mutex             m_mutex;


}; /* end class C_Logger */


template <typename T>
C_Logger& C_Logger::operator<<(const std::vector<T>& p_vector)
{
    std::string l_string = std::string("[Empty]");

    if (false == p_vector.empty())
    {
        l_string.clear();
        l_string.push_back(s_loggerCharBrkOpen);

        for (const T& l_value : p_vector)
        {
            l_string += std::to_string(l_value);
            l_string.push_back(s_loggerCharComma);
            l_string.push_back(s_loggerCharSpace);
        }
        l_string = l_string.substr(0, l_string.size() - 2) + s_loggerCharBrkClose;
    }

    return *this << l_string;
}


} /* namespace two */


#endif // TWO_C_LOGGER_H
