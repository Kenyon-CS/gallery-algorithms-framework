#pragma once

#include <string>

namespace gallery {

std::string trim(const std::string& s);
std::string stripQuotes(const std::string& s);
bool startsWith(const std::string& s, const std::string& prefix);

}  // namespace gallery
