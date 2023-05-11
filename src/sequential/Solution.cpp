#include "Solution.hpp"

void Solution::kMeans(std::vector<Point> &points, const int k, const int iter) {
  srand(time(nullptr));

  std::vector<Point> centroids(k);

  for (int i = 0; i < k; i++) {
    centroids[i] = points[rand() % points.size()];
  }

  for (int i = 0; i < iter; ++i) {
    for (int j = 0; j < k; j++) {
      for (auto &point : points) {
        const auto distance = centroids[j].Distance(point);
        if (distance < point.MinDistance()) {
          point.SetMinDistance(distance);
          point.SetCluster(j);
        }
      }
    }

    for (int j = 0; j < k; j++) {
      double sumX = 0.0;
      double sumY = 0.0;
      int count = 0;

      for (const auto &point : points) {
        if (point.Cluster() == j) {
          sumX += point.X();
          sumY += point.Y();
          count++;
        }
      }

      if (count > 0) {
        centroids[j].SetX(sumX / count);
        centroids[j].SetY(sumY / count);
      }
    }
  }
}

