#include "pch.h"
TEST_F(MemorySetUp, DeleteTest)
{
    for (int i = 0; i < 10; i++) EXPECT_NO_THROW(tree.Delete(i));
}
TEST_F(MemorySetUp, FindTest)
{
    for (int i = 0; i < 10; i++) EXPECT_NO_THROW(tree.Delete(i));
}