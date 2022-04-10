#ifndef IP_FILTER_TESTS_FILTER_TEST_H_
#define IP_FILTER_TESTS_FILTER_TEST_H_

#include <gtest/gtest.h>
#include <fstream>

#include "ipv4.h"

using namespace ipv4;
using namespace std::string_literals;

TEST(ip_filter, read_ip_list_extra_data) {
  // Arrange
  std::stringstream in{"192.168.1.0 4 5\n"
					   "123.33.44.5 6 7\n"s};
  auto result = IpList{{192, 168, 1, 0},
					   {123, 33, 44, 5}};

  // Act
  auto ip_list = ReadIpList(in);

  // Assert
  ASSERT_EQ(ip_list, result);
}

TEST(ip_filter, read_ip_list_wrong_ip) {
  // Arrange
  std::stringstream in{"192.168.10 4 5\n"
					   "123.33.44.5 6 7\n"s};
  auto result = IpList{{123, 33, 44, 5}};

  // Act
  auto ip_list = ReadIpList(in);

  // Assert
  ASSERT_EQ(ip_list, result);
}

struct IpFilterFixture : public testing::Test {
  std::ifstream input_file;
  std::fstream test_file;
  std::ifstream right_result_file;

  static void SetUpTestSuite() {
	std::cout << "SetUpTestSuite"s << std::endl;
  }

  static void TearDownTestSuite() {
	std::cout << "TearDownTestSuite"s << std::endl;
  }

  void SetUp() override {
	input_file.open("ip_filter.tsv", std::fstream::in);
	test_file.open("test_file.tst", std::fstream::trunc | std::fstream::in | std::fstream::out);
	right_result_file.open("ip_filter.tst", std::fstream::in);
  }

  void TearDown() override {
	input_file.close();
	test_file.close();
	right_result_file.close();
  }
};

TEST_F(IpFilterFixture, filtering) {
  // Arrange
  IpList ip_list = ReadIpList(input_file);

  // Act
  std::sort(ip_list.begin(), ip_list.end(), std::greater<>{});
  test_file << ip_list;

  FilterTemplateFunc(test_file, ip_list, 1);
  FilterTemplateFunc(test_file, ip_list, 46, 70);
  FilterAnyIpImpl(test_file, ip_list, 46);
  test_file.seekg(0);

  // Assert
  std::string test_result;
  for (std::string line; std::getline(test_file, line);)
	test_result.append(line);

  std::string right_result;
  for (std::string line; std::getline(right_result_file, line);) {
	right_result.append(line);
  }

  ASSERT_EQ(std::hash<std::string>{}(test_result), std::hash<std::string>{}(right_result));
}

#endif //IP_FILTER_TESTS_FILTER_TEST_H_
