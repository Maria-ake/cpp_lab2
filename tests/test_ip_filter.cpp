#include <gtest/gtest.h>
#include "ip_filter.h"

#include <algorithm>
#include <iterator>
#include <tuple>
#include <vector>
#include <string>

// Тест 1: Проверка парсинга IP-адреса
TEST(IpFilterTest, ParseIp) {
    std::string line = "1.2.3.4\tignore\tignore";
    IpAddress ip = parse_ip(line);
    EXPECT_EQ(std::get<0>(ip), 1);
    EXPECT_EQ(std::get<1>(ip), 2);
    EXPECT_EQ(std::get<2>(ip), 3);
    EXPECT_EQ(std::get<3>(ip), 4);
}

// Тест 2: Проверка сортировки (лексикографическая)
TEST(IpFilterTest, SortOrder) {
    IpPool pool = {
        std::make_tuple(1, 2, 1, 1),
        std::make_tuple(1, 10, 1, 1),
        std::make_tuple(1, 1, 1, 1)
    };
    std::sort(pool.begin(), pool.end(), [](const auto& a, const auto& b) {
        return a > b;
    });
    EXPECT_EQ(std::get<1>(pool[0]), 10);
    EXPECT_EQ(std::get<1>(pool[1]), 2);
    EXPECT_EQ(std::get<1>(pool[2]), 1);
}

// Тест 3: Проверка фильтрации (первый байт == 1)
TEST(IpFilterTest, FilterFirstByte) {
    IpPool pool = {
        std::make_tuple(1, 2, 3, 4),
        std::make_tuple(46, 70, 1, 1),
        std::make_tuple(5, 6, 7, 8)
    };
    auto filter = [](const IpAddress& ip) { return std::get<0>(ip) == 1; };
    IpPool result;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(result), filter);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(std::get<0>(result[0]), 1);
}