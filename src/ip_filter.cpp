#include "ip_filter.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>

// Парсинг строки: извлекаем только text1 (IP) и игнорируем остальное
IpAddress parse_ip(const std::string& line) {
    std::stringstream ss(line);
    std::string ip_part;
    std::getline(ss, ip_part, '\t'); // Читаем до табуляции

    std::stringstream ip_stream(ip_part);
    std::string byte_str;
    uint8_t b1, b2, b3, b4;

    std::getline(ip_stream, byte_str, '.'); b1 = static_cast<uint8_t>(std::stoi(byte_str));
    std::getline(ip_stream, byte_str, '.'); b2 = static_cast<uint8_t>(std::stoi(byte_str));
    std::getline(ip_stream, byte_str, '.'); b3 = static_cast<uint8_t>(std::stoi(byte_str));
    std::getline(ip_stream, byte_str, '.'); b4 = static_cast<uint8_t>(std::stoi(byte_str));

    return std::make_tuple(b1, b2, b3, b4);
}

// Печать пула IP-адресов
void print_pool(const IpPool& pool) {
    for (const auto& ip : pool) {
        std::cout << static_cast<int>(std::get<0>(ip)) << "."
                  << static_cast<int>(std::get<1>(ip)) << "."
                  << static_cast<int>(std::get<2>(ip)) << "."
                  << static_cast<int>(std::get<3>(ip)) << std::endl;
    }
}