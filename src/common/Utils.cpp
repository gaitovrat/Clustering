#include "Utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

std::map<std::string, std::vector<std::string>>
Utils::readCSV(const char *filename) {
  std::ifstream fin(filename);
  std::map<std::string, std::vector<std::string>> out;

  if (fin.is_open() == false) {
    std::cerr << "Unable to open " << filename << ".\n";
    return std::map<std::string, std::vector<std::string>>();
  }

  std::string line;
  std::string token;
  std::vector<std::string> keys;

  while (std::getline(fin, line)) {
    std::stringstream ss(line);
    if (out.size() == 0) {
      // Header
      while (std::getline(ss, token, ',')) {
        out[token] = std::vector<std::string>();
        keys.push_back(token);
      }
    } else {
      // Body
      for (int i = 0; std::getline(ss, token, ','); ++i) {
        out[keys[i]].push_back(token);
      }
    }
  }
  return out;
}

std::string Utils::readFile(const char *filename) {
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << filename << " not found.\n";
    return "";
  }
  std::stringstream buffer;
  buffer << fin.rdbuf();

  return buffer.str();
}
