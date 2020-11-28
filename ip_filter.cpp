#include "lib.h"

#include <iostream>
#include <algorithm>

int main([[maybe_unused]] int argc, [[maybe_unused]] char const* argv[]) {

    try {
        ip_list ip_pool;
        input_ip_list(std::cin, ip_pool);
        ip_pool.shrink_to_fit();

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ip_address>());

        std::cout << ip_pool;

        auto filter = [&ip_pool](const ip_byte&first_byte, auto&& ...params) {
            filter_template_func(std::cout, ip_pool, first_byte, std::forward<decltype(params)>(params)...);
        };

        // TODO filter by first byte and output
        filter(1);

        // TODO filter by first and second bytes and output
        filter(46, 70);

        // TODO filter by any byte and output
        auto filter_any = [&ip_pool](const ip_byte ipByte) {
            filter_any_ip_impl(std::cout, ip_pool, ipByte);
        };
        filter_any(46);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}