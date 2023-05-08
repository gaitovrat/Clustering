#ifndef _POINT_HPP_
#define _POINT_HPP_
#include <iostream>

class Point {
public:
  Point();

  Point(double x, double y);

  double X() const;

  void SetX(double x);

  double Y() const;

  void SetY(double y);

  int Cluster() const;

  void SetCluster(int cluster);

  double MinDistance() const;

  void SetMinDistance(double minDistance);

  double Distance(Point point) const;

  friend std::ostream &operator<<(std::ostream &os, const Point &obj);

private:
  double m_x;
  double m_y;
  int m_cluster;
  double m_minDistance;
};
#endif //_POINT_HPP_
