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
  char d1{}, d2{}, d3{};
  int b1{}, b2{}, b3{}, b4{};

  if (bool ok{is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4};
	  ok && d1 == '.' && d2 == '.' && d3 == '.')
	ipv_4 = Ipv4(b1, b2, b3, b4);
  else
	is.setstate(std::ios_base::failbit);

  return is;
}

}
