#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <map>
#include <string>
#include <vector>

namespace Utils {
std::map<std::string, std::vector<std::string>> readCSV(const char *filename);
}
#endif //_UTILS_HPP_
