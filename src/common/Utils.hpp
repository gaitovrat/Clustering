#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <map>
#include <string>
#include <vector>

namespace Utils {
std::map<std::string, std::vector<std::string>> readCSV(const char *filename);

std::string readFile(const char *filename);
} // namespace Utils
#endif //_UTILS_HPP_
