#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE IP_Filter_Test_Module

#include <boost/test/unit_test.hpp>
#include "lib.h"

#include <fstream>
#include <algorithm>

bool check_equal_hashes() {
    std::fstream fstream("ip_filter.tsv", std::fstream::in);
    ip_list ipListTest;
    input_ip_list(fstream, ipListTest);
    ipListTest.shrink_to_fit();
    fstream.close();

    fstream.open("test_file.tst", std::fstream::out);
    std::sort(ipListTest.begin(), ipListTest.end(), std::greater<ip_address>());
    fstream << ipListTest;
    filter_template_func(fstream, ipListTest, 1);
    filter_template_func(fstream, ipListTest, 46, 70);
    filter_any_ip_impl(fstream, ipListTest, 46);
    fstream.close();

    fstream.open("test_file.tst", std::fstream::in);
    std::string test_file; // container for test file
    for (std::string line; std::getline(fstream, line); ) {
        test_file += line;
    }
    fstream.close();

    fstream.open("ip_filter.tst", std::fstream::in);
    std::string ref_file; // container for reference file
    for (std::string line; std::getline(fstream, line); ) {
        ref_file += line;
    }
    fstream.close();

    std::hash<std::string> hash;

    return (hash(test_file) == hash(ref_file));
}

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)
    BOOST_AUTO_TEST_CASE(ip_filter_test_output)
    {
        BOOST_CHECK(check_equal_hashes());
    }

BOOST_AUTO_TEST_SUITE_END()