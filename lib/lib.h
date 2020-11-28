#pragma once

#include <vector>
#include <array>
#include <string>

using ip_byte = unsigned char;
using ip_address = std::array<ip_byte, 4>;
using ip_list = std::vector<ip_address>;
using ip_list_ci = ip_list::const_iterator;

void input_ip_list(std::istream& ostream, ip_list& ip_pool);
std::ostream& operator<<(std::ostream& ostream, const ip_address& ipAddress);
std::ostream& operator<<(std::ostream& ostream, const ip_list& ipList);

template<typename ...Args>
void filter_template_func(std::ostream& ostream, const ip_list& ipList, const ip_byte& ipByte, Args&&... ip_bytes) {
    auto ipAddress = ip_address{ ipByte, (ip_byte)ip_bytes... };

    auto interval = std::make_pair(ipList.cbegin(), ipList.end());

    for (size_t cnt = 0; cnt < (1 + sizeof...(ip_bytes)); ++cnt) {
        interval = std::equal_range(interval.first, interval.second, ipAddress,
            [cnt](const ip_address& lhs, const ip_address& rhs) {
                return lhs.at(cnt) > rhs.at(cnt);
            }
        );
    }

    ostream << ip_list(interval.first, interval.second);
}

void filter_any_ip_impl(std::ostream& ostream, const ip_list &ip_pool, const ip_byte ipByte);
