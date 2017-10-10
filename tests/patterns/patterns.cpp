/*!
 *  \file patterns.cpp
 *  \brief Main source of patterns test
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <two.h>


static const std::string k_programName = std::string("patterns");


enum class TestEventEnum : size_t
{
    TestEvent0,
    TestEvent1,
    TestEvent2,
    TestEventSize
};


two::TwoReturnCodeEnum enumToString(const TestEventEnum p_enum, std::string& p_stringEnum)
{
    two::TwoReturnCodeEnum l_returnCode = two::TwoReturnCodeEnum::TwoReturnCodeSuccess;

    switch (p_enum)
    {
        case TestEventEnum::TestEvent0:
            p_stringEnum = std::string("TestEvent0");
            break;
        case TestEventEnum::TestEvent1:
            p_stringEnum = std::string("TestEvent1");
            break;
        case TestEventEnum::TestEvent2:
            p_stringEnum = std::string("TestEvent2");
            break;
        case TestEventEnum::TestEventSize:
            p_stringEnum = std::string("TestEventSize");
            break;
        default:
            p_stringEnum += std::string("Not converted ") + std::to_string(static_cast<size_t>(p_enum));
            l_returnCode = two::TwoReturnCodeEnum::TwoReturnCodeNotCorverted;
            break;
    }

    return l_returnCode;
}


class C_TestObserver : public two::C_Observer<TestEventEnum>
{


public:

    C_TestObserver() : two::C_Observer<TestEventEnum>(), m_name() { /* empty */ }

    virtual ~C_TestObserver() { /* empty */ }

    virtual bool Update(const TestEventEnum& p_event, void* p_arg);

    void SetName(const std::string& p_name) { m_name = p_name; }

    void SetName(std::string&& p_name) { std::swap(m_name, p_name); }


private:

    std::string m_name;

};


bool C_TestObserver::Update(const TestEventEnum& p_event, void*)
{
    std::string l_stringEnum;

    const bool l_return = two::TwoReturnCodeEnum::TwoReturnCodeSuccess == enumToString(p_event, l_stringEnum);

    if (true == l_return)
    {
        std::cout << " " << __func__ << " " << m_name << " Got event " << l_stringEnum << " .\n";
    }

    return l_return;
}


class C_TestObservable : public two::C_Observable<TestEventEnum>
{


public:

    C_TestObservable() : two::C_Observable<TestEventEnum>() { /* empty */ }

    virtual ~C_TestObservable() { /* empty */ }

    bool TestNotify(const TestEventEnum& p_event);


};


bool C_TestObservable::TestNotify(const TestEventEnum& p_event)
{
    return Notify(p_event, NULL);
}


void testFunction1()
{
    C_TestObserver   l_observer1;
    C_TestObserver   l_observer2;
    C_TestObservable l_observable;

    l_observer1.SetName("Observer 1");
    l_observer2.SetName("Observer 2");

    l_observable.Subscribe(TestEventEnum::TestEvent0, &l_observer1);
    l_observable.Subscribe(TestEventEnum::TestEvent1, &l_observer1);
    l_observable.Subscribe(TestEventEnum::TestEvent1, &l_observer2);

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent0))
    {
        std::cout << __func__ << " Failed to notify TestEvent0\n";
    }

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent1))
    {
        std::cout << __func__ << " Failed to notify TestEvent1\n";
    }

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent2))
    {
        std::cout << __func__ << " Failed to notify TestEvent2\n";
    }

    std::cout << "\n " << __func__ << " Observer 1 unsubscribe TestEvent0\n\n";

    l_observable.Unsubscribe(TestEventEnum::TestEvent0, &l_observer1);

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent0))
    {
        std::cout << __func__ << " Failed to notify TestEvent0\n";
    }

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent1))
    {
        std::cout << __func__ << " Failed to notify TestEvent1\n";
    }

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent2))
    {
        std::cout << __func__ << " Failed to notify TestEvent2\n";
    }

    std::cout << "\n " << __func__ << " Observer 2 unsubscribe TestEvent1\n\n";

    l_observable.Unsubscribe(TestEventEnum::TestEvent1, &l_observer2);

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent0))
    {
        std::cout << __func__ << " Failed to notify TestEvent0\n";
    }

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent1))
    {
        std::cout << __func__ << " Failed to notify TestEvent1\n";
    }

    if (false == l_observable.TestNotify(TestEventEnum::TestEvent2))
    {
        std::cout << __func__ << " Failed to notify TestEvent2\n";
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
