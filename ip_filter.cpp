#include "lib.h"

#include <iostream>
#include <algorithm>
#include <chrono>

class Timer
{
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};

int main(int argc, char const* argv[]) {

    try {
        ip_list ip_pool;
        input_ip_list(ip_pool);
        ip_pool.shrink_to_fit();

        // TODO reverse lexicographically sort
        Timer t;
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ip_address>());
        auto tt = t.elapsed();
        std::cout << "Time sort elapsed: " << tt << std::endl;

        t.reset();
        std::cout << ip_pool;
        tt = t.elapsed();
        std::cout << "Time cout elapsed: " << tt << std::endl;

        auto filter = [&ip_pool](const ip_byte&first_byte, auto&& ...params) {
            filter_template_func(ip_pool, first_byte, std::forward<decltype(params)>(params)...);
        };

        // TODO filter by first byte and output
        t.reset();
        filter(1);
        tt = t.elapsed();
        std::cout << "Time filter(1) elapsed: " << tt << std::endl;

        // TODO filter by first and second bytes and output
        t.reset();
        filter(46, 70);
        tt = t.elapsed();
        std::cout << "Time filter(46, 70) elapsed: " << tt << std::endl;

        // TODO filter by any byte and output
        auto filter_any = [&ip_pool](const ip_byte ipByte) {
            filter_any_ip_impl(ip_pool, ipByte);
        };
        t.reset();
        filter_any(46);
        tt = t.elapsed();
        std::cout << "Time filter_any elapsed: " << tt << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}