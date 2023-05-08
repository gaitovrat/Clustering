#include "Point.hpp"

#include <cmath>
#include <limits>

Point::Point() : Point(0.0, 0.0) {}

Point::Point(const double x, const double y)
    : m_x(x), m_y(y), m_cluster(-1),
      m_minDistance(std::numeric_limits<double>::max()), m_visited(false) {}
double Point::X() const { return m_x; }

void Point::SetX(double x) { m_x = x; }

double Point::Y() const { return m_y; }

void Point::SetY(double y) { m_y = y; }

int Point::Cluster() const { return m_cluster; }

void Point::SetCluster(int cluster) { m_cluster = cluster; }

double Point::MinDistance() const { return m_minDistance; }

void Point::SetMinDistance(double minDistance) { m_minDistance = minDistance; }

double Point::Distance(Point point) const {
  return std::pow(point.X() - X(), 2) + std::pow(point.Y() - Y(), 2);
}

std::ostream &operator<<(std::ostream &os, const Point &obj) {
  os << "Point(" << obj.m_x << ", " << obj.m_y << ", " << obj.m_cluster << ", "
     << obj.m_minDistance << ")";

  return os;
}

bool Point::Visited() const { return m_visited; }

void Point::SetVisited(bool visited) { m_visited = visited; }
