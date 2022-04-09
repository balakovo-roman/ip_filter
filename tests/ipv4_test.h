#ifndef IP_FILTER_TESTS_IPV4_TEST_H_
#define IP_FILTER_TESTS_IPV4_TEST_H_

#include <gtest/gtest.h>

#include "ipv4.h"

using namespace ipv4;
using namespace std::string_literals;

TEST(ipv4, write_to_stream)
{
  // Arrange
  Ipv4 ipv_4{123, 111, 1, 4};
  std::stringstream result;

  // Act
  result << ipv_4;

  // Assert
  ASSERT_EQ(result.str(), "123.111.1.4"s);
}

#endif //IP_FILTER_TESTS_IPV4_TEST_H_
