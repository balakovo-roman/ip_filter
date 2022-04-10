#ifndef IP_FILTER_TESTS_IPV4_TEST_H_
#define IP_FILTER_TESTS_IPV4_TEST_H_

#include <gtest/gtest.h>

#include "ipv4.h"

using namespace ipv4;
using namespace std::string_literals;

TEST(ipv4, construct) {
  // Arrange
  Ipv4 ip_default;
  Ipv4 ip{192, 168, 0, 1};
  Ipv4 ip_copy_op;

  // Act
  Ipv4 ip_copy = ip;
  ip_copy_op = ip;

  // Assert
  ASSERT_EQ(ip_default, Ipv4(0,0,0,0));
  ASSERT_EQ(ip_copy, Ipv4(192,168,0,1));
  ASSERT_EQ(ip_copy_op, Ipv4(192,168,0,1));
}

TEST(ipv4, write_to_stream) {
  // Arrange
  Ipv4 ip{192, 168, 0, 1};
  std::stringstream result;

  // Act
  result << ip;

  // Assert
  ASSERT_EQ(result.str(), "192.168.0.1"s);
}

TEST(ipv4, right_read_from_stream) {
  // Arrange
  Ipv4 ip;
  std::stringstream right_input{"192.168.0.1"s};

  // Act
  right_input >> ip;

  // Assert
  ASSERT_EQ(ip, Ipv4(192,168,0,1));
}

TEST(ipv4, wrong_read_from_stream) {
  // Arrange
  Ipv4 ip;
  std::stringstream wrong_input{"192.168.01"s};

  // Act
  wrong_input >> ip;

  // Assert
  ASSERT_EQ(wrong_input.fail(), true);
  ASSERT_EQ(ip, Ipv4(0,0,0,0));

  // Act
  wrong_input = std::stringstream{"192.168.0."s};
  ASSERT_EQ(wrong_input.fail(), false);
  wrong_input >> ip;

  // Assert
  ASSERT_EQ(wrong_input.fail(), true);
  ASSERT_EQ(ip, Ipv4(0,0,0,0));

  // Act
  wrong_input = std::stringstream{"192.168.0.a"s};
  ASSERT_EQ(wrong_input.fail(), false);
  wrong_input >> ip;

  // Assert
  ASSERT_EQ(wrong_input.fail(), true);
  ASSERT_EQ(ip, Ipv4(0,0,0,0));
}

TEST(ipv4, to_string) {
  // Arrange
  Ipv4 ip{192,168,0,1};

  // Assert
  ASSERT_EQ(ip.to_string(), "192.168.0.1"s);
}

TEST(ipv4, postfix_increment)
{
  // Arrange
  Ipv4 ip{1,2,3,4};

  // Assert
  ASSERT_EQ(ip++, Ipv4(1,2,3,4));
  ASSERT_EQ(ip, Ipv4(1,2,3,5));
}

TEST(ipv4, prefix_increment)
{
  // Arrange
  Ipv4 ip{1,2,3,4};

  // Assert
  ASSERT_EQ(++ip, Ipv4(1,2,3,5));
  ASSERT_EQ(ip, Ipv4(1,2,3,5));
}

TEST(ipv4, some_behaviour)
{
  // Arrange
  Ipv4 ip{255,1,2,255};
  Ipv4 ip2;
  std::stringstream input{"192.168.0.257"s};

  // Act
  ++ip;
  input >> ip2;

  // Assert
  ASSERT_EQ(ip, Ipv4(255,1,3,0));
  ASSERT_EQ(ip2, Ipv4(192,168,0,1));
}

TEST(ipv4, compare)
{
  // Arrange
  Ipv4 ip{1,2,3,4};
  Ipv4 ip2{1,2,2,4};
  Ipv4 ip3{1,2,5,4};

  // Assert
  ASSERT_EQ(ip > ip2, true);
  ASSERT_EQ(ip > ip3, false);
}

TEST(ipv4, index_operator)
{
  // Arrange
  Ipv4 ip{192,168,1,1};

  // Assert
  ASSERT_EQ(ip[0], 192);
  ASSERT_EQ(ip[1], 168);
  ASSERT_EQ(ip[2], 1);
  ASSERT_EQ(ip[3], 1);
}

TEST(ipv4, const_for_loop)
{
  // Arrange
  Ipv4 ip{192,168,1,1};
  std::vector<Ipv4::IpByte> result{192, 168, 1, 1};
  std::vector<Ipv4::IpByte> output;

  // Act
  for (const auto ip_byte : ip)
	output.emplace_back(ip_byte);

  // Assert
  ASSERT_EQ(output, result);
}

TEST(ipv4, changed_for_loop)
{
  // Arrange
  Ipv4 ip{192,168,1,1};

  // Act
  for (auto &ip_byte : ip)
	ip_byte = 255;

  // Assert
  ASSERT_EQ(ip, Ipv4(255,255,255,255));
}

TEST(ipv4, compile_time)
{
  // Arrange
  constexpr Ipv4 ip{192,168,1,1};
  constexpr Ipv4 ip2{192,168,2,1};

  // Assert
  static_assert(ip < ip2);
  static_assert(ip[1] == 168);
  static_assert(*(ip2.begin() + 2) == 2);
}


#endif //IP_FILTER_TESTS_IPV4_TEST_H_
