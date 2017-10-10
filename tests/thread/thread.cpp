/*!
 *  \file thread.cpp
 *  \brief Main source of thread test
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <two.h>


static const std::string k_programName = std::string("thread");


void testFunction1()
{
    pthread_mutex_t l_mutex;

    if (0 != pthread_mutex_init(&l_mutex, NULL))
    {
        std::cout << __func__ << " failed to init the mutex\n\n";
    }
    else
    {
        two::pthread_mutexlocker_t l_lock(l_mutex);

        std::cout << " " << __func__ << " mutex is locked: " << std::boolalpha << l_lock.IsLocked() << " .\n";

        l_lock.Unlock();

        std::cout << " " << __func__ << " mutex is locked: " << std::boolalpha << l_lock.IsLocked() << " .\n";

        l_lock.Lock();

        std::cout << " " << __func__ << " mutex is locked: " << std::boolalpha << l_lock.IsLocked() << " .\n";

        std::cout << " " << __func__ << " lock counts: " << l_lock.GetLockCounter() << " .\n";
    }
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
