#include "ip_filter.h"
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    IpPool ip_pool;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        ip_pool.push_back(parse_ip(line));
    }

  
    std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& a, const auto& b) {
        return a > b;
    });

    print_pool(ip_pool);


    auto filter_1 = [](const IpAddress& ip) {
        return std::get<0>(ip) == 1;
    };
    IpPool pool_1;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(pool_1), filter_1);
    print_pool(pool_1);

    auto filter_2 = [](const IpAddress& ip) {
        return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;
    };
    IpPool pool_2;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(pool_2), filter_2);
    print_pool(pool_2);


    auto filter_3 = [](const IpAddress& ip) {
        return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || 
               std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
    };
    IpPool pool_3;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(pool_3), filter_3);
    print_pool(pool_3);

    return 0;
}