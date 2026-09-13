#pragma once
#include <vector>
#include <tuple>
#include <string>
#include <cstdint>


using IpAddress = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;
using IpPool = std::vector<IpAddress>;

IpPool filter(const IpPool& pool, bool (*condition)(const IpAddress&));
void print_pool(const IpPool& pool);
IpAddress parse_ip(const std::string& line);