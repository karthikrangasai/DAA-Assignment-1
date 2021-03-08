#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <set>

#include "types.hpp"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

set<Point> _union(set<Rectangle> R);
set<Coord> y_set(set<Rectangle> R);
set<Interval> partition(set<Coord> Y);

set<Coord> x_proj(set<Point> P);
set<Interval> intervals(set<Coord> C);
set<Stripe> stripes(set<Rectangle> R, Rectangle f);

real measure(set<Stripe> S);
set<LineSegment> contour_pieces(Edge h, set<Stripe> S);
set<LineSegment> contour(set<Edge> H, set<Stripe> S);

#ifdef __cplusplus
}
#endif
#endif /