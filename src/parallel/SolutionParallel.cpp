#include "SolutionParallel.hpp"

#include <omp.h>
#include <vcruntime.h>

#include "OpenCLContext.hpp"

void Solution::kMeans(std::vector<Point> &points, const int k, const int iter) {
  srand(time(nullptr));

  std::vector<Point> centroids(k);
  OpenCLContext clContext("kMeans.cl");

  clContext.AddKernel("calculateDistance");
  clContext.AddKernel("updateCentroids");

#pragma omp parallel for
  for (int i = 0; i < k; i++) {
    centroids[i] = points[rand() % points.size()];
  }

  const int centroidsSize = centroids.size();
  const int pointsSize = points.size();

  cl::Buffer pointsBuffer(clContext.GetContext(), CL_MEM_READ_WRITE,
                          sizeof(Point) * points.size());
  cl::Buffer centroidsBuffer(clContext.GetContext(), CL_MEM_READ_WRITE,
                             sizeof(Point) * centroids.size());
  cl::Buffer centroidsSizeBuffer(clContext.GetContext(), CL_MEM_READ_ONLY,
                                 sizeof(int));
  cl::Buffer pointsSizeBuffer(clContext.GetContext(), CL_MEM_READ_ONLY,
                              sizeof(int));
  clContext.GetQueue().enqueueWriteBuffer(
      pointsBuffer, CL_TRUE, 0, sizeof(Point) * points.size(), &points[0]);
  clContext.GetQueue().enqueueWriteBuffer(centroidsBuffer, CL_TRUE, 0,
                                          sizeof(Point) * centroids.size(),
                                          &centroids[0]);
  clContext.GetQueue().enqueueWriteBuffer(centroidsSizeBuffer, CL_TRUE, 0,
                                          sizeof(int), &centroidsSize);
  clContext.GetQueue().enqueueWriteBuffer(pointsSizeBuffer, CL_TRUE, 0,
                                          sizeof(int), &pointsSize);

  for (int i = 0; i < iter; ++i) {
    clContext.GetKernel("calculateDistance").setArg(0, pointsBuffer);
    clContext.GetKernel("calculateDistance").setArg(1, centroidsBuffer);
    clContext.GetKernel("calculateDistance").setArg(2, centroidsSizeBuffer);
    clContext.GetQueue().enqueueNDRangeKernel(
        clContext.GetKernel("calculateDistance"), cl::NullRange,
        cl::NDRange(points.size()));

    clContext.GetKernel("updateCentroids").setArg(0, pointsBuffer);
    clContext.GetKernel("updateCentroids").setArg(1, centroidsBuffer);
    clContext.GetKernel("updateCentroids").setArg(2, pointsSizeBuffer);
    clContext.GetQueue().enqueueNDRangeKernel(
        clContext.GetKernel("updateCentroids"), cl::NullRange,
        cl::NDRange(centroids.size()));
  }
  clContext.GetQueue().enqueueReadBuffer(
      pointsBuffer, CL_TRUE, 0, sizeof(Point) * points.size(), &points[0]);
}

void Solution::kMeansOMP(std::vector<Point> &points, const int k,
                         const int iter) {
  srand(time(nullptr));

  std::vector<Point> centroids(k);

#pragma omp parallel for
  for (int i = 0; i < k; i++) {
    centroids[i] = points[rand() % points.size()];
  }

  for (int i = 0; i < iter; ++i) {
#pragma omp parallel for
    for (int j = 0; j < k; j++) {
      for (auto &point : points) {
        const auto distance = centroids[j].Distance(point);
        if (distance < point.MinDistance()) {
          point.SetMinDistance(distance);
          point.SetCluster(j);
        }
      }
    }
#pragma omp parallel for
    for (int j = 0; j < k; j++) {
      double sumX = 0.0;
      double sumY = 0.0;
      int count = 0;

#pragma omp parallel for reduction(+ : sumX, sumY, count)
      for (int idx = 0; idx < points.size(); ++idx) {
        if (points[idx].Cluster() == j) {
          sumX += points[idx].X();
          sumY += points[idx].Y();
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

