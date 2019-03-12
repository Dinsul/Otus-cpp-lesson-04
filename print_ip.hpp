#pragma once

#include <iostream>
#include <type_traits>
#include <tuple>

/** @file */

/**
 * @addtogroup PRINT_TAMPLATES
 * @brief Набор шаблонных функций для вывода ip-адресов
 *
 * @{
 */


template <size_t pos, class ... Args>
struct print_tuple
{
    static void print(std::tuple<Args ...> ip)
    {
        print_tuple<pos - 1, Args ...>::print(ip);
        std::cout << std::get<pos>(ip)
                  << (std::tuple_size<decltype(ip)>::value - 1 == pos ? "" : ".");
    }
};

template <class ... Args>
struct print_tuple <0, Args ...>
{
    static void print(std::tuple<Args ...> ip)
    {
        std::cout << std::get<0>(ip)
                  << (std::tuple_size<decltype(ip)>::value == 1 ? "" : ".");
    }
};

/**
 * @brief print_ip Перегрузка для вывода кортежей
 * @param ip Кортеж из одинаковых типов,
 * которые могут быть выведены с помощью std::cout
 * @return
 */
template <class ... Args>
auto print_ip(std::tuple<Args ...> ip)
{
    print_tuple<std::tuple_size<decltype(ip)>::value - 1, Args ...>::print(ip);

    return std::tuple_size<decltype(ip)>::value;
}

//template <class T>
//size_t print_ip(std::tuple<T, T, T, T> ip)
//{
//    std::cout << std::get<0>(ip) << '.'
//              << std::get<1>(ip) << '.'
//              << std::get<2>(ip) << '.'
//              << std::get<3>(ip);
//    return 4;
//}


/**
 * @brief print_ip Выводит ip-адрес на стандартный вывод
 * @param ip ip-адрес
 */
auto print_ip(std::string ip)
{
    std::cout << ip;

    return ip.find('.') + 1;
}


/**
 * @brief The print_ip_internal class
 * Выводит целочисленные типы
 */
template <bool B, class T>
class print_ip_internal
{
public:
    auto operator ()(T ip)
    {
        size_t i;
        auto length = sizeof(T);

        for (i = 0; i < length; ++i)
        {
            std::cout << (ip >> ((length - i - 1) * __CHAR_BIT__) & 0xFF);

            if (i < length - 1)
            {
                std::cout << ".";
            }
        }

        return i;
    }
};

/**
 * @brief The print_ip_internal<T> class
 * Выводит контейнеры
 */
template <typename T>
class print_ip_internal<false, T>
{
public:
    auto operator ()(T &ip)
    {
        size_t ret = 0;
        for (auto i = ip.begin(); i != ip.end(); ++i)
        {
            ++ret;
            if (i != ip.begin())
            {
                std::cout << ".";
            }

            std::cout << *i;
        }

        return ret;
    }
};

/**
 * @brief print_ip Выводит ip-адрес на стандартный вывод
 * @param ip Адрес в любом из следующих форматов: любое целочисленное число;
 * контейнер целочисленных значений std::vector; контейнер целочисленных значений std::list
 * @return Количество напечатанных узлов (чисел между точками)
 */
template <typename T>
auto print_ip(T ip)
{
    print_ip_internal<std::is_integral<T>::value, T> runner;

    return runner(ip);
}

/**
 * @brief print_ip_last Функция для вывода завершающего элемента
 * для перегрузки с переменным числом параметров
 * @param last завершающий элемент
 * @return
 */
template<typename T, typename ... Args>
size_t print_ip_last(T last, Args ... )
{
    std::cout << last;

    return 0;
}

/**
 * @brief print_ip Побная перегрузка с переменным числом параметров
 * @param args Любой тип который выводится с помощью std::cout
 * @return
 */
template<typename T, typename ... Args>
size_t print_ip(T first, Args ... args)
{
    // Если надо напечатать char как int можно сделать так
    //std::cout << (+first) << '.';
    std::cout << first << '.';

    if (sizeof ... (args) == 1)
    {
        return print_ip_last(args...);
    }

    return print_ip(args...);
}

/** @} */
