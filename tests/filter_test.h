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

TEST(ip_filter, filtering) {
  std::fstream file("ip_filter.tsv", std::fstream::in);
  IpList ip_list = ReadIpList(file);
  file.close();

  file.open("test_file.tst", std::fstream::out);
  if (!file.is_open()) {
	exit(1);
  }
  std::sort(ip_list.begin(), ip_list.end(), std::greater<>{});
  file << ip_list;

  FilterTemplateFunc(file, ip_list, 1);
  FilterTemplateFunc(file, ip_list, 46, 70);
  FilterAnyIpImpl(file, ip_list, 46);
  file.close();

  file.open("test_file.tst", std::fstream::in);
  std::string test_file;
  for (std::string line; std::getline(file, line);)
	test_file += line;
  file.close();

  file.open("ip_filter.tst", std::fstream::in);
  std::string ref_file;
  for (std::string line; std::getline(file, line);) {
	ref_file += line;
  }
  file.close();

  ASSERT_EQ(std::hash<std::string>{}(test_file), std::hash<std::string>{}(ref_file));
}

#endif //IP_FILTER_TESTS_FILTER_TEST_H_
