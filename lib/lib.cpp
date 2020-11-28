#include "lib.h"

#include <iostream>
#include <algorithm>
#include <iterator>

ip_address get_ip(std::string& str)
{
    std::string::size_type sz{0};
    ip_address temp{};
    temp[0] = std::stoi(str, &sz);
    temp[1] = std::stoi(str.erase(0, sz + 1), &sz);
    temp[2] = std::stoi(str.erase(0, sz + 1), &sz);
    temp[3] = std::stoi(str.erase(0, sz + 1));
    return temp;
}

void input_ip_list(std::istream& istream, ip_list& ip_pool) {
    //TODO: add parser ip address and checks it 
    for (std::string line; std::getline(istream, line);) {
        ip_pool.emplace_back(get_ip(line));
    }
}

std::ostream& operator<<(std::ostream& ostream, const ip_address& ipAddress) {
    for (auto it = ipAddress.cbegin(); it != ipAddress.cend(); ++it) {
        if (it != ipAddress.cbegin())
            ostream << ".";
        ostream << +*it;
    }
    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const ip_list& ipList) {
    for (const auto& address : ipList)
        ostream << address << "\n";
    return ostream;
}

void filter_any_ip_impl(std::ostream& ostream, const ip_list& ip_pool, const ip_byte anyIpByte) {
    for (const auto& ipAddress : ip_pool) {
        if (std::any_of(ipAddress.cbegin(), ipAddress.cend(), [anyIpByte](const ip_byte ipByte) {return anyIpByte == ipByte; })) {
            ostream << ipAddress << "\n";
        }
    }
}
