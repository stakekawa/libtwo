/*!
 *  \file c_worker.cpp
 *
 *  \brief This file contains the implementation of c_worker class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */


#include <iostream>   // std::cerr
#include <thread>     // std::thread
#include "c_worker.h"


namespace two {


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* explicit */
C_Worker::C_Worker(const std::string& p_workerName /* = std::string(C_WORKER_NAME_DEFAULT) */) :
    m_workerName(p_workerName),
    m_workerStatus(WorkerStatusEnum::WorkerStatusStopped),
    m_workerTimeout(C_WORKER_WAIT_TIMEOUT_DEFAULT),
    m_workerTimeoutBackup(C_WORKER_WAIT_TIMEOUT_DEFAULT),
    m_startStopAsync(C_WORKER_STARTSTOPASYNC_DEFAULT),
    m_startStopAsyncTimeout(C_WORKER_STARTSTOPASYNC_TIMEOUT),
    m_statusMutex(),
    m_workerMutex(),
    m_workerConditionVariable()
{

}


/* virtual */
C_Worker::~C_Worker()
{

}


std::cv_status C_Worker::WaitForMilliseconds(const int p_milliseconds /* = C_WORKER_WAIT_TIMEOUT_DEFAULT */)
{
    std::unique_lock<std::mutex> l_lock(m_workerMutex);
    std::chrono::duration<int, std::milli> p_waitTime(p_milliseconds);
    std::cv_status l_timeout = m_workerConditionVariable.wait_for(l_lock, p_waitTime);

    /* m_workerMutex is unlocked at return of this */
    /* function when l_lock is destroyed           */

    return l_timeout;
}


void C_Worker::Start()
{
    if (true == IsStarted())
    {
        std::cerr << GetName() << " already started..." << std::endl;
    }
    else if (true == IsStarting())
    {
        std::cerr << GetName() << " already starting..." << std::endl;
    }
    else if (true == IsPaused())
    {
        std::cerr << GetName() << " is paused..." << std::endl;
    }
    else
    {
        SetStarting();

        if (true == m_startStopAsync)
        {
            /* start starting thread */

            std::thread l_thread(&C_Worker::StartingThread, this);

            l_thread.detach();
        }
        else
        {
            /* blocking call */

            StartingThread();

            const std::chrono::steady_clock::time_point l_stopTime = std::chrono::steady_clock::now();

            while (true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(C_WORKER_WAIT_TIMEOUT_SYNC));

                if (true == IsStarted())
                {
                    break;
                }

                const int l_millisecondsWaited = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - l_stopTime).count());

                if (m_startStopAsyncTimeout < l_millisecondsWaited)
                {
                    std::cerr << GetName() << " Failed to start after" << l_millisecondsWaited << "milliseconds" << std::endl;
                    break;
                }

            } /* end while (true) */

        } /* end if (true == m_startStopAsync) */

    } /* end if (true == IsStarted()) else */

}


void C_Worker::Stop()
{
    if (true == IsStopped())
    {
        std::cerr << GetName() << " already stopped..." << std::endl;
    }
    else if (true == IsStopping())
    {
        std::cerr << GetName() << " already stopping..." << std::endl;
    }
    else
    {
        SetStopping();

        if (true == m_startStopAsync)
        {
            /* start stopping thread */

            std::thread l_thread(&C_Worker::StoppingThread, this);

            l_thread.detach();
        }
        else
        {
            /* blocking call */

            StoppingThread();

            const std::chrono::steady_clock::time_point l_startTime = std::chrono::steady_clock::now();

            while (true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(C_WORKER_WAIT_TIMEOUT_SYNC));

                if (true == IsStopped())
                {
                    break;
                }

                const int l_millisecondsWaited = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - l_startTime).count());

                if (m_startStopAsyncTimeout < l_millisecondsWaited)
                {
                    std::cerr << GetName() << " Failed to stop after" << l_millisecondsWaited << "milliseconds" << std::endl;
                    break;
                }

            } /* end while (true) */

        } /* end if (true == m_startStopAsync) */

    } /* end if (true == IsStopped()) else */

}


/* virtual */
void C_Worker::Pause()
{
    if (true == IsStopped())
    {
        std::cerr << GetName() << " already stopped..." << std::endl;
    }
    else if (true == IsStopping())
    {
        std::cerr << GetName() << " already stopping..." << std::endl;
    }
    else if (true == IsPaused())
    {
        std::cerr << GetName() << " already in pause..." << std::endl;
    }
    else
    {
        m_workerTimeoutBackup = m_workerTimeout.load();

        SetTimeout(C_WORKER_WAIT_TIMEOUT_PAUSED);

        SetPaused();

        WakeUp();
    }
}


/* virtual */
void C_Worker::Resume()
{
    if (false == IsPaused())
    {
        std::cerr << GetName() << " was not in pause..." << std::endl;
    }
    else
    {
        SetTimeout(m_workerTimeoutBackup);

        SetStarted();

        WakeUp();
    }
}



void C_Worker::WakeUp()
{
    std::unique_lock<std::mutex> l_lock(m_workerMutex);
    m_workerConditionVariable.notify_one();
}


/* ************************************************************************** */
/* Protected members                                                          */
/* ************************************************************************** */


/* virtual */
bool C_Worker::PrepareToStart()
{
    std::cerr << GetName() << __func__ << "not overrided" << std::endl;
    return true;
}


/* virtual */
bool C_Worker::PrepareToStop()
{
    std::cerr << GetName() << __func__ << "not overrided" << std::endl;
    return true;
}


/* virtual */
bool C_Worker::BeforeWork()
{
    std::cerr << GetName() << __func__ << "not overrided" << std::endl;
    return true;
}


/* virtual */
bool C_Worker::AfterWork()
{
    std::cerr << GetName() << __func__ << "not overrided" << std::endl;
    return true;
}


/* virtual */
bool C_Worker::StopAfterWakeUpIfStopped()
{
    std::cerr << GetName() << __func__ << "not overrided" << std::endl;
    return false;
}


/* virtual */
bool C_Worker::WorkerJob()
{
    std::cerr << GetName() << __func__ << "not overrided" << std::endl;
    return not IsStopped() || not IsStopping();
}


/*                                                                            */
/* Private members                                                            */
/*                                                                            */


void C_Worker::WorkerThread()
{
    /* set the worker started */

    SetStarted();

    if (false == BeforeWork())
    {
        std::cerr << GetName() << " failed to do before work..." << std::endl;
    }
    else
    {
        std::cout << GetName() << " started" << std::endl;

        while (true == IsStarted())
        {

            /* take the timeout to use to wait */

            const int l_timeout = (true == IsPaused()) ? C_WORKER_WAIT_TIMEOUT_PAUSED : GetTimeout();

            /* wait until woken up or timed out */

            std::cv_status l_status = WaitForMilliseconds(l_timeout);

            /* log at negative log level */

            if (std::cv_status::timeout == l_status)
            {
                /* timed out */
            }
            else
            {
                /* woken up */
            }

            /* exit asap if requested */

            if (true == StopAfterWakeUpIfStopped())
            {
                break;
            }

            if (false == WorkerJob())
            {
                break;
            }

        } /* end while (true == IsStarted()) */

    } /* if (false == BeforeWork()) */

    if (false == AfterWork())
    {
        std::cerr << GetName() << " failed to do after work..." << std::endl;
    }

    /* set the worker stopped just */
    /* before thread exit          */

    SetStopped();

    std::cout << GetName() << " stopped" << std::endl;
}


void C_Worker::StartingThread()
{
    if (false == PrepareToStart())
    {
        std::cerr << GetName() << " failed to prepare to start" << std::endl;

        /* set the worker to stopped since   */
        /* it has failed to prepare to start */

        SetStopped();
    }
    else
    {
        std::cout << GetName() << " starting..." << std::endl;

        /* start worker thread */

        std::thread l_thread(&C_Worker::WorkerThread, this);

        l_thread.detach();

    } /* end if (false == PrepareToStart()) */
}


void C_Worker::StoppingThread()
{
    if (false == PrepareToStop())
    {
        std::cerr << GetName() << " failed to prepare to stop" << std::endl;

        /* set the worker to started since  */
        /* it has failed to prepare to stop */

        SetStarted();
    }
    else
    {
        std::cout << GetName() << " stopping..." << std::endl;

        /* wake up worker thread */

        WakeUp();

    } /* else if (false == PrepareToStop()) */
}


} /* end namespace two { */
