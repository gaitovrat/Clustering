#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "SolutionParallel.hpp"
#include "Utils.hpp"

int main(int argc, const char **argv) {
  if (argc < 6) {
    std::cout << "Usage:\n\tpds-parallel kmeans filepath xline yline k iter\n";
    std::cout << "\n\tpds-parallel kmeans-omp filepath xline yline k iter\n";
    std::cout << "\tpds-parallel dbscan filepath xline yline eps "
                 "minPts\n";
    return EXIT_FAILURE;
  }
  auto csv = Utils::readCSV(argv[2]);
  const auto xline = argv[3];
  const auto yline = argv[4];
  std::vector<Point> points;
  const auto &x = csv[xline];
  const auto &y = csv[yline];

  for (int i = 0; i < x.size(); ++i) {
    points.emplace_back(std::stod(x[i]), std::stod(y[i]));
  }

  auto start = std::chrono::high_resolution_clock::now();
  std::string type(argv[1]);
  if (type == "kmeans") {
    const int k = std::atoi(argv[5]);
    const int iter = std::atoi(argv[6]);

    Solution::kMeans(points, k, iter);
  } else if (type == "kmeans-omp") {
    const int k = std::atoi(argv[5]);
    const int iter = std::atoi(argv[6]);

    Solution::kMeansOMP(points, k, iter);
  } else if (type == "dbscan") {
    const double eps = std::stod(argv[5]);
    const int minPts = std::atoi(argv[6]);

    Solution::dbscan(points, eps, minPts);
  } else {
    std::cerr << "Invalid type.\n";
    return EXIT_FAILURE;
  }
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
