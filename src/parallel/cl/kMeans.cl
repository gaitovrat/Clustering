struct Point {
  double x;
  double y;
  int cluster;
  double minDistance;
  bool visited;
};

kernel void calculateDistance(global struct Point* points, global const struct Point* centroids, global int *centroidsSize) {
    int pointSize = get_global_size(0);
    int globalId = get_global_id(0);

    for (int i = 0; i < centroidsSize[0]; i++) {
        double distance = sqrt(pow(points[globalId].x - centroids[i].x, 2) + pow(points[globalId].y - centroids[i].y, 2));
        if (distance < points[globalId].minDistance) {
            points[globalId].minDistance = distance;
            points[globalId].cluster = i;
        }
    }
}

kernel void updateCentroids(global const struct Point* points, global struct Point* centroids, global const int *pointsSize) {
    int centroidsSize = get_global_size(0);
    int globalId = get_global_id(0);

    double sumX = 0.0;
    double sumY = 0.0;
    int count = 0;

    for (int i = 0; i < pointsSize[0]; i++) {
        if (points[i].cluster == globalId) {
            sumX += points[i].x;
            sumY += points[i].y;
            count++;
        }
    }

    if (count > 0) {
        centroids[globalId].x = sumX / count;
        centroids[globalId].y = sumY / count;
        }
}
