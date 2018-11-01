#define BOOST_TEST_MODULE test_ip_filter

#include "print_ip.hpp"

#include <boost/test/unit_test.hpp>

#include <vector>
#include <list>

BOOST_AUTO_TEST_SUITE(test_suite_print_ip)

BOOST_AUTO_TEST_CASE(test_vector)
{
    std::vector<int> vec{192, 168, 1};

    BOOST_CHECK(print_ip(vec) == 3);
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(test_list)
{
    std::list<int> lis{122,255,255,0,5};

    BOOST_CHECK(print_ip(lis) == 5);
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(test_char)
{
    BOOST_CHECK(print_ip((char)-1) == 1);
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(test_short)
{
    BOOST_CHECK(print_ip((short)0) == 2);
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(test_int)
{
    BOOST_CHECK(print_ip(2130706433) == 4);
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(test_long)
{
    BOOST_CHECK(print_ip(8875824491850138409l) == 8);
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(test_string)
{
    BOOST_CHECK(print_ip(std::string{"213.123.0.3"}) == 4);
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE(test_tuple)
{
    BOOST_CHECK(print_ip(std::make_tuple("222","33","44","55")) == 4);
    std::cout << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
