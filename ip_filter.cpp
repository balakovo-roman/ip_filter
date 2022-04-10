#include "ipv4.h"

#include <iostream>

using namespace ipv4;

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[]) {
  IpList ip_list = ReadIpList(std::cin);
  ip_list.shrink_to_fit();

  // reverse lexicographically sort
  std::sort(ip_list.begin(), ip_list.end(), std::greater<>{});

  std::cout << ip_list;

  auto filter = [&ip_list](const Ipv4::IpByte &first_byte, auto &&...params) {
	FilterTemplateFunc(std::cout, ip_list, first_byte, std::forward<decltype(params)>(params)...);
  };

  // filter by first byte and output
  filter(1);

  // filter by first and second bytes and output
  filter(46, 70);

  // filter by any byte and output
  auto filter_any = [&ip_list](const Ipv4::IpByte ip_byte) {
	FilterAnyIpImpl(std::cout, ip_list, ip_byte);
  };

  filter_any(46);

  return 0;
}