#include "ip_filter.h"
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    IpPool ip_pool;
    std::string line;

    // 1. Чтение данных из stdin
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        ip_pool.push_back(parse_ip(line));
    }

    // 2. Сортировка в обратном лексикографическом порядке
    // Используем лямбду для компаратора
    std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& a, const auto& b) {
        return a > b; // Обратный порядок
    });

    // 3. Печать полного списка
    print_pool(ip_pool);

    // 4. Фильтрация: первый байт равен 1
    // Используем лямбду для условия
    auto filter_1 = [](const IpAddress& ip) {
        return std::get<0>(ip) == 1;
    };
    IpPool pool_1;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(pool_1), filter_1);
    print_pool(pool_1);

    // 5. Фильтрация: первый байт 46, второй 70
    auto filter_2 = [](const IpAddress& ip) {
        return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;
    };
    IpPool pool_2;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(pool_2), filter_2);
    print_pool(pool_2);

    // 6. Фильтрация: любой байт равен 46
    // Демонстрация использования decltype
    auto filter_3 = [](const IpAddress& ip) {
        // Проверяем каждый элемент кортежа
        return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || 
               std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
    };
    IpPool pool_3;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(pool_3), filter_3);
    print_pool(pool_3);

    return 0;
}