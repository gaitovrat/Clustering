#include <iostream>

#include "Point.hpp"

int main(int argc, const char **argv) {
  Point p1;
  Point p2(3.0, 4.0);

  std::cout << "p1: " << p1 << "\np2: " << p2 << '\n';

  std::cout << "Distance p1 -> p2: " << p1.Distance(p2) << '\n';

  return 0;
}
