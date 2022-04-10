#pragma once

#include <algorithm>
#include <array>
#include <vector>

namespace ipv4 {

class Ipv4 {
 public:
  using IpByte = unsigned char;

  constexpr Ipv4(IpByte first = 0, IpByte second = 0, IpByte third = 0, IpByte fought = 0) :
	  data_{first, second, third, fought} {}

  constexpr Ipv4(const Ipv4 &other) noexcept = default;
  constexpr Ipv4 &operator=(const Ipv4 &other) noexcept = default;

  std::string to_string() const;

  constexpr auto begin() const noexcept {
	return data_.cbegin();
  }
  constexpr auto begin() noexcept {
	return data_.begin();
  }

  constexpr auto end() const noexcept {
	return data_.cend();
  }
  constexpr auto end() noexcept {
	return data_.end();
  }

  constexpr const IpByte &operator[](int n) const noexcept {
	return data_[n];
  }

  IpByte &operator[](int n) noexcept {
	return data_[n];
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

using IpList = std::vector<Ipv4>;

IpList ReadIpList(std::istream &istream);
std::ostream &operator<<(std::ostream &ostream, const IpList &ip_list);

template<typename ...Args>
void FilterTemplateFunc(std::ostream &ostream, const IpList &ip_list, const Ipv4::IpByte &ip_byte, Args &&... ip_bytes) {
  auto ipv_4 = Ipv4{ip_byte, static_cast<Ipv4::IpByte>(ip_bytes)...};

  auto [begin, end] = std::make_pair(ip_list.cbegin(), ip_list.end());

  for (size_t cnt = 0; cnt < (1 + sizeof...(ip_bytes)); ++cnt) {
	std::tie(begin, end) = std::equal_range(begin, end, ipv_4,
											[cnt](const Ipv4 &lhs, const Ipv4 &rhs) {
											  return lhs[cnt] > rhs[cnt];
											}
	);
  }

  ostream << IpList(begin, end);
}

void FilterAnyIpImpl(std::ostream &os, const IpList &ip_list, Ipv4::IpByte ip_byte);

}
