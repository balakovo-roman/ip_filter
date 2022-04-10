#include <gtest/gtest.h>

#include "ipv4_test.h"
#include "filter_test.h"

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}