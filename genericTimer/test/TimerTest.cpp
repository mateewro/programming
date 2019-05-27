#include "Timer.h"
#include "ClockMock.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>

using namespace testing;
using namespace std;
using namespace std::chrono;

struct GenericTimerTestSuite : public testing::Test
{
    void waitToRunTheTimer()
    {
        std::this_thread::sleep_for(10ms);
    }

    void waitToChangeState(int& trigger)
    {
        while(trigger != 1){}
    }

    NiceMock<ClockMock> m_clock;
};

TEST_F(GenericTimerTestSuite, TestSetsTimeoutWithCallbackFunction)
{
    auto trigger = 0;
    EXPECT_CALL(m_clock, sleep_for(_))
                .Times(AtLeast(1));
    auto timePoint = system_clock::now();
    EXPECT_CALL(m_clock, now())
                .WillOnce(Return(timePoint))
                .WillOnce(Return(timePoint + 1001ms));
    Timer m_timer(m_clock);
    auto timeToFireTimer = 1000;
    m_timer.setTimeoutInMs([&]{++trigger;}, timeToFireTimer);
    waitToChangeState(trigger);
    EXPECT_EQ(trigger, 1);
}

TEST_F(GenericTimerTestSuite, TestSetsIntervalWithCallbackFunction)
{
    auto trigger = 0;
    EXPECT_CALL(m_clock, sleep_for(_))
                .Times(AtLeast(1));
    auto timePoint = system_clock::now();
    EXPECT_CALL(m_clock, now())
                .WillOnce(Return(timePoint))
                .WillOnce(Return(timePoint + 1001ms))
                .WillOnce(Return(timePoint + 2001ms))
                .WillRepeatedly(Return(timePoint + 2001ms));
    Timer m_timer(m_clock);
    auto timeToFireTimer = 1000;
    m_timer.setIntervalInMs([&]{++trigger;}, timeToFireTimer);
    waitToRunTheTimer();
    EXPECT_EQ(trigger, 2);
    m_timer.abort();
}

TEST_F(GenericTimerTestSuite, TestAbortsTimerWithIntervalRunning)
{
    auto trigger = 0;
    auto timePoint = system_clock::now();
    EXPECT_CALL(m_clock, now())
                .WillOnce(Return(timePoint))
                .WillRepeatedly(Return(timePoint + 500ms));
    Timer m_timer(m_clock);
    auto timeToFireTimer = 1000;
    m_timer.setIntervalInMs([&]{++trigger;}, timeToFireTimer);
    waitToRunTheTimer();
    m_timer.abort();
    EXPECT_EQ(trigger, 0);
}

TEST_F(GenericTimerTestSuite, TestAbortsTimerWithTimeoutRunning)
{
    auto trigger = 0;
    auto timePoint = system_clock::now();
    EXPECT_CALL(m_clock, now())
                .WillOnce(Return(timePoint))
                .WillRepeatedly(Return(timePoint + 500ms));
    Timer m_timer(m_clock);
    auto timeToFireTimer = 1000;
    m_timer.setTimeoutInMs([&]{trigger = !trigger;}, timeToFireTimer);
    waitToRunTheTimer();
    m_timer.abort();
    EXPECT_EQ(trigger, 0);
}

TEST_F(GenericTimerTestSuite, TestChecksCalculationOfTimeToFireTimer)
{
    Timer m_timer(m_clock);
    auto timeToFireTimer = 1000;
    m_timer.setTimeoutInMs([&]{}, timeToFireTimer);
    EXPECT_EQ(m_timer.getTimeToFireInMs(),timeToFireTimer);
    m_timer.abort();
}

TEST_F(GenericTimerTestSuite, TestChecksCalculationOfTimeToFireTimerWhenTimerIsNotSet)
{
    Timer m_timer(m_clock);
    auto timeToFireTimer = 0;
    EXPECT_EQ(m_timer.getTimeToFireInMs(),timeToFireTimer);
    m_timer.abort();
}

TEST_F(GenericTimerTestSuite, TestChecksCalculationOfTimeToFireWhenTimerIsInIntervalMode)
{
    auto trigger = 0;
    auto timeToFireTimer = 1000;
    auto timePoint = system_clock::now();
    EXPECT_CALL(m_clock, now())
                .WillOnce(Return(timePoint))
                .WillRepeatedly(Return(timePoint + 1001ms));
    Timer m_timer(m_clock);
    m_timer.setIntervalInMs([&]{++trigger;}, timeToFireTimer);
    waitToRunTheTimer();
    EXPECT_EQ(m_timer.getTimeToFireInMs(), 999);
    m_timer.abort();
}

TEST_F(GenericTimerTestSuite, TestIfTimerStopsWhenExceptionOccurs)
{
    auto trigger = 0;
    auto timeToFireTimer = 1000;
    auto timePoint = system_clock::now();
    EXPECT_CALL(m_clock, now())
                .WillOnce(Return(timePoint))
                .WillRepeatedly(Return(timePoint + 1001ms));
    Timer m_timer(m_clock);
    m_timer.setIntervalInMs([&]{++trigger;throw("exception");}, timeToFireTimer);
    waitToRunTheTimer();
    EXPECT_ANY_THROW(m_timer.getException());
}

TEST_F(GenericTimerTestSuite, TestChecksCalculationOfTimeToFireWhenExceptionOccurs)
{
    auto trigger = 0;
    auto timeToFireTimer = 1000;
    auto timePoint = system_clock::now();
    EXPECT_CALL(m_clock, now())
                .WillOnce(Return(timePoint))
                .WillRepeatedly(Return(timePoint + 1001ms));
    Timer m_timer(m_clock);
    m_timer.setIntervalInMs([&]{++trigger;throw("exception");}, timeToFireTimer);
    waitToRunTheTimer();
    EXPECT_EQ(m_timer.getTimeToFireInMs(), 0);
}