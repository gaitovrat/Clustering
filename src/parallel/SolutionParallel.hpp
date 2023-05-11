#ifndef _SOLUTION_HPP_
#define _SOLUTION_HPP_
#include <vector>

#ifndef CL_TYPE
#define CL_TYPE
#endif // !CL_TYPE

#include "Point.hpp"

namespace Solution {
void kMeans(std::vector<Point> &points, int k, int iter);
void kMeansOMP(std::vector<Point> &points, const int k, const int iter);
} // namespace Solution
#endif //_SOLUTION_HPP_
