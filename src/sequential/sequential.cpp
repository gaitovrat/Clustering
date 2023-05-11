#include <chrono>
#include <fstream>
#include <stdlib.h>
#include <string>

#include "Point.hpp"
#include "Solution.hpp"
#include "Utils.hpp"

int main(int argc, const char **argv) {
  if (argc < 6) {
    std::cout << "Usage:\n\tpds-sequential filepath xline yline k iter\n";
    return EXIT_FAILURE;
  }

  auto csv = Utils::readCSV(argv[1]);
  const auto xline = argv[2];
  const auto yline = argv[3];
  std::vector<Point> points;
  const auto &x = csv[xline];
  const auto &y = csv[yline];

  for (int i = 0; i < x.size(); ++i) {
    points.emplace_back(std::stod(x[i]), std::stod(y[i]));
  }

  auto start = std::chrono::high_resolution_clock::now();
  const int k = std::atoi(argv[4]);
  const int iter = std::atoi(argv[5]);

  Solution::kMeans(points, k, iter);

  auto end = std::chrono::high_resolution_clock::now(); // get the current time
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << duration.count() << "ms\n";

  std::ofstream fout("out.csv");
  fout << "x,y,c\n";
  for (const auto &point : points) {
    fout << point.X() << ',' << point.Y() << ',' << point.Cluster() << '\n';
  }

  return 0;
}
