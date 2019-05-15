#include "GenericTimer.h"
#include "gmock/gmock.h"

using namespace testing;

class GenericTimerTest : public testing::Test
{
public:
    GenericTimer genericTimer;
};

TEST_F(GenericTimerTest, EmptyTest)
{
    ASSERT_TRUE(true);
}
