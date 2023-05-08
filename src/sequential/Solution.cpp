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

static std::vector<Point> regionQuery(std::vector<Point> points, Point p,
                                      double eps) {
  std::vector<Point> neighbors;
  for (auto &q : points) {
    if (p.Distance(q) <= eps) {
      neighbors.push_back(q);
    }
  }
  return neighbors;
}

static void expandCluster(std::vector<Point> &points, Point &p,
                          std::vector<Point> &neighbors, int cluster,
                          double eps, int minPts) {
  p.SetCluster(cluster);
  for (auto &q : neighbors) {
    if (!q.Visited()) {
      q.SetVisited(true);
      auto qNeighbors = regionQuery(points, q, eps);
      if (qNeighbors.size() >= minPts) {
        neighbors.insert(neighbors.end(), qNeighbors.begin(), qNeighbors.end());
      }
    }
    if (q.Cluster() == -1) {
      q.SetCluster(cluster);
    }
  }
}

void Solution::dbscan(std::vector<Point> &points, double eps, int minPts) {
  int cluster = 0;
  for (auto &p : points) {
    if (!p.Visited()) {
      p.SetVisited(true);
      auto neighbors = regionQuery(points, p, eps);
      if (neighbors.size() < minPts) {
        p.SetCluster(-1);
      } else {
        expandCluster(points, p, neighbors, cluster, eps, minPts);
        cluster++;
      }
    }
  }
}
