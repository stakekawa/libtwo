/*!
 *  \file c_worker.h
 *
 *  \brief This file contains the declaration of C_Worker class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_WORKER_H
#define TWO_C_WORKER_H


#define C_WORKER_NAME_DEFAULT                              std::string("Worker")
#define C_WORKER_WAIT_TIMEOUT_DEFAULT                                       2000 /* milliseconds */
#define C_WORKER_WAIT_TIMEOUT_PAUSED                                     INT_MAX
#define C_WORKER_STARTSTOPASYNC_DEFAULT                                     true
#define C_WORKER_STARTSTOPASYNC_TIMEOUT                                     2000 /* milliseconds */
#define C_WORKER_WAIT_TIMEOUT_SYNC                                            10 /* milliseconds */


#include <atomic>             // std::atomic
#include <climits>            // INT_MAX
#include <condition_variable> // std::condition_variable
#include <functional>         // std::function
#include <mutex>              // std::mutex
#include <string>             // std::string
#include <vector>             // std::vector


namespace two {


/*!
 *  \brief The C_Worker class provides a base class for working objects
 *         The C_Worker handles different states. Use the function to control the
 *         states and accessors to get current states.
 *
 *         The idea is to provide a standard worker class to be inheritated by
 *         implementation of specialized worker. The specialization should be just
 *         overriding of methods PrepareToStart(), PrepareToStop(), BeforeWork(),
 *         AfterWork(), ExitAfterWakeUpIfStopped() and WorkerJob(). Their return
 *         values should be true (i. e. continue, keep working) or false (i. e.
 *         failed, therefore stop, do not start, stop working...).
 *
 *         The worker does work in a separate thread, every time it times out or
 *         when it is woken up.
 */
class C_Worker
{

    /*!
     *  \brief The WORKER_STATUS_ENUM enumeration lists all possibile states
     */
    enum class WorkerStatusEnum : size_t
    {
        WorkerStatusStopped,  /*< C_Worker is stopped  */
        WorkerStatusStopping, /*< C_Worker is stopping */
        WorkerStatusStarted,  /*< C_Worker is started  */
        WorkerStatusStarting, /*< C_Worker is starting */
        WorkerStatusPaused,   /*< C_Worker is paused   */
        WorkerStatusSize      /*<  */
    };


public:

    /*!
     *  \brief Constructor
     *
     *  \param p_workerName name to assign to the worker
     */
    explicit C_Worker(const std::string& p_workerName = C_WORKER_NAME_DEFAULT);

    /*!
     *  \brief Destructor
     */
    virtual ~C_Worker();

    /*!
     *  \brief Wake the worker
     */
    void WakeUp();

    /*!
     *  \brief Set worker timeout [milliseconds]
     */
    void SetTimeout(const int p_milliseconds) { m_workerTimeout = p_milliseconds; }

    /*!
     *  \brief Get worker timeout [milliseconds]
     */
    int GetTimeout() const { return m_workerTimeout; }

    /*!
     *  \brief Query if the worker is stopped
     */
    bool IsStopped() const  { return WorkerStatusEnum::WorkerStatusStopped == GetStatus();  }

    /*!
     *  \brief Query if the worker is stopping
     */
    bool IsStopping() const { return WorkerStatusEnum::WorkerStatusStopping == GetStatus(); }

    /*!
     *  \brief Query if the worker is started
     */
    bool IsStarted() const  { return WorkerStatusEnum::WorkerStatusStarted == GetStatus();  }

    /*!
     *  \brief Query if the worker is starting
     */
    bool IsStarting() const { return WorkerStatusEnum::WorkerStatusStarting == GetStatus(); }

    /*!
     *  \brief Query if the worker is paused
     *  \return
     */
    bool IsPaused() const  { return WorkerStatusEnum::WorkerStatusPaused == GetStatus();    }

    /*!
     *  \brief Configure whether the Start() and the Stop() should be done asynchronously
     *         (i. e. starting detached threads to run stuff) or synchronously (i. e. blocking
     *         the thread calling Start() and Stop()). Default is asynchronous behaviour.
     */
    void SetStartStopAsync(const bool p_startStopAsync) { m_startStopAsync = p_startStopAsync; }

    /*!
     *  \brief Configure the max timeout during Start() and Stop() when the C_Worker is started
     *         and stopped in synchrounous mode
     */
    void SetStartStopAsyncTimeout(const bool p_milliseconds) { m_startStopAsyncTimeout = p_milliseconds; }

    /*!
     *  \brief Return the name of the worker
     */
    const std::string& GetName() const { return m_workerName; }

    /*!
     *  \brief Function to start the worker. The function checks
     *         the current state and then it creates another thread that
     *         executes the PrepareToStart() function. This is done to
     *         reduce latency in the calling thread, if the PrepareToStart()
     *         function requires long time execution.
     */
    virtual void Start() final;

    /*!
     *  \brief Function to stop the worker. The function checks
     *         the current state and then it creates another thread that
     *         executes the PrepareToStop() function. This is done to
     *         reduce latency in the calling thread, if the PrepareToStop()
     *         function requires long time execution.
     */
    virtual void Stop() final;

    /*!
     *  \brief Function to pause the worker.
     */
    virtual void Pause() final;

    /*!
     *  \brief Function to resume the worker.
     */
    virtual void Resume() final;


protected:

    /*!
     *  \brief Wait function on std::condition_variable
     *
     *  \param p_milliseconds number of milliseconds to wait
     */
    std::cv_status WaitForMilliseconds(const int p_milliseconds = C_WORKER_WAIT_TIMEOUT_DEFAULT);

    /*!
     *  \brief This functions is called before the worker get into the started state. This
     *         function should be override to be customized.
     *
     *  \return true if the worker can start, false if not
     */
    virtual bool PrepareToStart();

    /*!
     *  \brief This functions is called before the worker get into the stopped state. This
     *         function should be override to be customized.
     *
     *  \return true if the worker can stop, false if not
     */
    virtual bool PrepareToStop();

    /*!
     *  \brief This function is executed in the worker thread, after the worker reached
     *         the state started before the loop.
     *
     *  \return true if the worker can continue, false if the worker should stop
     */
    virtual bool BeforeWork();

    /*!
     *  \brief This function is executed in the worker thread, after that it exits the
     *         loop, before reaching the stopped state. Nota bene: the worker stops for
     *         all return values.
     *
     *  \return true if everything ok, false if something was wrong.
     */
    virtual bool AfterWork();

    /*!
     *  \brief This function returns a condition that states if the worker has to exit
     *         its loop asap after it was woken up
     *
     *  \return true to stop asap, false to do job once more before stopping
     */
    virtual bool StopAfterWakeUpIfStopped();

    /*!
     *  \brief This function is executed in the worker thread loop every time the
     *         worker is woken up or the timeout has reached.
     *
     *  \return true everything is ok, false to stop the worker
     */
    virtual bool WorkerJob();


private:

    /*!
     *  \brief The copy constructor is deleted
     */
    C_Worker(const C_Worker& p_orig) = delete;

    /*!
     *  \brief The copy assignment operator is deleted
     */
    C_Worker& operator=(const C_Worker& p_other) = delete;

    /*!
     *  \brief The move constructor is deleted
     */
    C_Worker(const C_Worker&& p_orig) = delete;

    /*!
     *  \brief The move assignment operator is deleted
     */
    C_Worker& operator=(const C_Worker&& p_other) = delete;

    /*!
     *  \brief Set the worker status
     */
    void SetStatus(const WorkerStatusEnum p_status) { std::lock_guard<std::mutex> l_lock(m_statusMutex); m_workerStatus = p_status; }

    /*!
     *  \brief Set that the worker is stopped
     */
    void SetStopped()  { SetStatus(WorkerStatusEnum::WorkerStatusStopped);  }

    /*!
     *  \brief Set that the worker is stopping
     */
    void SetStopping() { SetStatus(WorkerStatusEnum::WorkerStatusStopping); }

    /*!
     *  \brief Set that the worker is started
     */
    void SetStarted()  { SetStatus(WorkerStatusEnum::WorkerStatusStarted);  }

    /*!
     *  \brief Set that the worker is starting
     */
    void SetStarting() { SetStatus(WorkerStatusEnum::WorkerStatusStarting); }

    /*!
     *  \brief Set that the worker is paused
     */
    void SetPaused()   { SetStatus(WorkerStatusEnum::WorkerStatusPaused);   }

    /*!
     *  \brief Get the worker status
     */
    WorkerStatusEnum GetStatus() const { std::lock_guard<std::mutex> l_lock(m_statusMutex); return m_workerStatus; }

    /*!
     *  \brief Function executed by the working thread. It must be not virtual.
     */
    void WorkerThread();

    /*!
     *  \brief Function executed by the starting thread. It must be not virtual.
     */
    void StartingThread();

    /*!
     *  \brief Function executed by the stopping thread. It must be not virtual.
     */
    void StoppingThread();

    const   std::string             m_workerName;
            WorkerStatusEnum        m_workerStatus;
            std::atomic<int>        m_workerTimeout;
            std::atomic<int>        m_workerTimeoutBackup;
            std::atomic<bool>       m_startStopAsync;
            std::atomic<int>        m_startStopAsyncTimeout;
    mutable std::mutex              m_statusMutex;
            std::mutex              m_workerMutex;
            std::condition_variable m_workerConditionVariable;


};


} /* namespace two { */


#endif // TWO_C_WORKER_H
