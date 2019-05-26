#include <iostream>
#include "Timer.h"
#include "IClock.h"
#include "Clock.h"

using namespace std;

int main(void)
{
    auto trigger = 0;
    Clock myClock;
    Timer timer(myClock);
    cout << timer.getTimeToFireInMs() << endl;
    auto countTriggers = [&] {++trigger; cout << "lambda setInterval " << trigger << endl;throw("...");};
    timer.setIntervalInMs(countTriggers, 1000);
    for(auto i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(200ms);
        cout << timer.getTimeToFireInMs() << endl;
    }
    try
    {
        timer.getException();
    }
    catch(...)
    {
        std::exception_ptr e = std::current_exception();
        cout << "Exception handled." << endl;
    }
    timer.abort();
    cout << "Counter after timer run=" << trigger << endl;
    return 0;
}
