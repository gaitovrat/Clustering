#include <fstream>

#include "Point.hpp"
#include "Solution.hpp"
#include "Utils.hpp"

int main(int argc, const char **argv) {
  if (argc < 4) {
    std::cout << "Usage: pds-sequential filepath xline yline k [iter]\n";
    return EXIT_FAILURE;
  }

  auto csv = Utils::readCSV(argv[1]);
  const auto xline = argv[2];
  const auto yline = argv[3];
  const int k = std::atoi(argv[4]);
  int iter = 10;
  if (argc >= 6) {
    iter = std::atoi(argv[5]);
  }

  std::vector<Point> points;
  const auto &x = csv[xline];
  const auto &y = csv[yline];

  for (int i = 0; i < x.size(); ++i) {
    points.emplace_back(std::stod(x[i]), std::stod(y[i]));
  }

  Solution::kMeans(points, k, iter);

  std::ofstream fout("out.csv");
  fout << "x,y,c\n";
  for (const auto &point : points) {
    fout << point.X() << ',' << point.Y() << ',' << point.Cluster() << '\n';
  }

  return 0;
}
