#pragma once

#include <array>

namespace ipv4 {

class Ipv4 {
 public:
  using IpByte = unsigned char;

  constexpr Ipv4(IpByte first = 0, IpByte second = 0, IpByte third = 0, IpByte fought = 0) :
	  data_{first, second, third, fought} {}

  constexpr Ipv4(const Ipv4 &other) noexcept = default;
  constexpr Ipv4 &operator=(const Ipv4 &other) noexcept = default;

  std::string to_string() const;
  constexpr unsigned long to_ulong() const noexcept {
	return (static_cast<unsigned long>(data_[0]) << 24) | (static_cast<unsigned long>(data_[1]) << 16) |
		(static_cast<unsigned long>(data_[2]) << 8) | static_cast<unsigned long>(data_[3]);
  }

  Ipv4 &operator++() {
	*this = Ipv4(1 + to_ulong());
	return *this;
  }

  Ipv4 operator++(int) {
	Ipv4 result(*this);
	++(*this);
	return result;
  }

  friend std::ostream &operator<<(std::ostream &os, const Ipv4 &ipv_4);
  friend std::istream &operator>>(std::istream &is, Ipv4 &ipv_4);

  friend bool operator==(const Ipv4 &left, const Ipv4 &right) noexcept {
	return left.data_ == right.data_;
  }

  friend bool operator!=(const Ipv4 &left, const Ipv4 &right) noexcept {
	return !(left == right);
  }

  friend constexpr bool operator<(const Ipv4 &left, const Ipv4 &right) noexcept {
	return left.to_ulong() < right.to_ulong();
  }

  friend constexpr bool operator>(const Ipv4 &left, const Ipv4 &right) noexcept {
	return right < left;
  }

  friend constexpr bool operator<=(const Ipv4 &left, const Ipv4 &right) noexcept {
	return !(left > right);
  }

  friend constexpr bool operator>=(const Ipv4 &left, const Ipv4 &right) noexcept {
	return !(left < right);
  }

 private:
  explicit constexpr Ipv4(unsigned long ip) :
	  data_{static_cast<IpByte>((ip >> 24) & 0xFF),
			static_cast<IpByte>((ip >> 16) & 0xFF),
			static_cast<IpByte>((ip >> 8) & 0xFF),
			static_cast<IpByte>(ip & 0xFF)} {}

  constexpr unsigned long to_ulong() const noexcept {
	return (static_cast<unsigned long>(data_[0]) << 24) | (static_cast<unsigned long>(data_[1]) << 16) |
		(static_cast<unsigned long>(data_[2]) << 8) | static_cast<unsigned long>(data_[3]);
  }

  std::array<IpByte, 4> data_;
};

}
