#include "ipv4.h"

#include <sstream>

namespace ipv4 {

std::string Ipv4::to_string() const {
  std::stringstream result;
  result << *this;
  return result.str();
}

std::ostream &operator<<(std::ostream &os, const Ipv4 &ipv_4) {
  return os << static_cast<int>(ipv_4.data_[0]) << '.' << static_cast<int>(ipv_4.data_[1]) << '.'
			<< static_cast<int>(ipv_4.data_[2]) << '.' << static_cast<int>(ipv_4.data_[3]);
}
std::istream &operator>>(std::istream &is, Ipv4 &ipv_4) {
  int b1{};
  if (!(is >> b1)) {
	is.setstate(std::ios_base::failbit);
	return is;
  }

  if (is.peek() != '.') {
	is.setstate(std::ios_base::failbit);
	return is;
  }
  is.ignore(1);

  int b2{};
  if (!(is >> b2)) {
	is.setstate(std::ios_base::failbit);
	return is;
  }

  if (is.peek() != '.') {
	is.setstate(std::ios_base::failbit);
	return is;
  }
  is.ignore(1);

  int b3{};
  if (!(is >> b3)) {
	is.setstate(std::ios_base::failbit);
	return is;
  }

  if (is.peek() != '.') {
	is.setstate(std::ios_base::failbit);
	return is;
  }
  is.ignore(1);

  int b4{};
  if (is >> b4)
	ipv_4 = Ipv4(b1, b2, b3, b4);
  else
	is.setstate(std::ios_base::failbit);

  return is;
}

IpList ReadIpList(std::istream &is) {
  IpList ip_list;

  while (!is.eof() && !is.bad())
  {
	Ipv4 ip;
	is >> ip;

	if (is.fail()) {
	  is.clear();
	  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} else {
	  ip_list.emplace_back(ip);
	}
  }

  return ip_list;
}

std::ostream &operator<<(std::ostream &os, const IpList &ip_list) {
  for (const auto &ip : ip_list)
	os << ip << '\n';

  return os;
}

void FilterAnyIpImpl(std::ostream &os, const IpList &ip_list, Ipv4::IpByte any_ip_byte) {
  for (const auto &ip : ip_list) {
	if (std::any_of(std::cbegin(ip),
					std::cend(ip),
					[any_ip_byte](const Ipv4::IpByte ip_byte) { return any_ip_byte == ip_byte; })) {
	  os << ip << '\n';
	}
  }
}

}
