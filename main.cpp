#include <vector>
#include <list>

#include "print_ip.hpp"

int main (int, char**)
{
    std::vector<int> vec{192, 168, 1, 1};
    std::list<int> lis{122,255,255,0};

    print_ip((char)-1);
    std::cout << std::endl;

    print_ip((short)0);
    std::cout << std::endl;

    print_ip(2130706433);
    std::cout << std::endl;

    print_ip(8875824491850138409l);
    std::cout << std::endl;

    print_ip(std::string{"213.123.0.3"});
    std::cout << std::endl;

    print_ip(vec);
    std::cout << std::endl;

    print_ip(lis);
    std::cout << std::endl;

    print_ip(std::make_tuple("222","33","44","55"));
    std::cout << std::endl;

    print_ip(std::make_tuple(22, 0xFA, 144, 55));
    std::cout << std::endl;

    //Случайно получилось сделать print_ip с
    //переменным количеством аргументов
    print_ip('1', 2l, "34", 047, 0xF2, 2);
    std::cout << std::endl;

    print_ip(77, 28);
    std::cout << std::endl;

    return 0;
}
