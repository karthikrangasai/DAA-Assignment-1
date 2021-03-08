#ifndef TYPES_H
#define TYPES_H

#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <set>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

typedef long double real;
#define INFINITY numeric_limits<long double>::infinity()

typedef long double Coord;

typedef struct Point {
    Coord x;
    Coord y;
    Point(Coord _x, Coord _y) {
        x = _x;
        y = _y;
    }
} Point;

typedef struct Interval {
    Coord bottom;
    Coord top;
    Interval(Coord _bottom, Coord _top) {
        bottom = _bottom;
        top = _top;
    }
} Interval;

typedef struct LineSegment {
    Interval interval;
    Coord coord;
} LineSegment;

// typedef struct PointRectangle {
//     Coord x_left;
//     Coord x_right;
//     Coord y_bottom;
//     Coord y_top;
// } PointRectangle;

// typedef struct IntervalRectangle {
//     Interval x_interval;
//     Interval y_interval;
// } IntervalRectangle;

typedef struct Rectangle {
    Coord x_left;
    Coord x_right;
    Coord y_bottom;
    Coord y_top;
    Interval x_interval;
    Interval y_interval;
    bool isInterval;
    // PointRectangle pointRectangle;
    // IntervalRectangle intervalRectangle;
    Rectangle(Interval x, Interval y) {
        x_interval = x;
        y_interval = y;
        isInterval = true;
    }
    Rectangle(Coord _x_left, Coord _x_right, Coord _y_bottom, Coord _y_top) {
        x_left = _x_left;
        x_right = _x_right;
        y_bottom = _y_bottom;
        y_top = _y_top;
        isInterval = false;
    }
} Rectangle;

enum EdgeType {
    LEFT,
    RIGHT,
    BOTTOM,
    TOP
};

typedef struct Edge {
    Interval interval;
    Coord coordinate;
    EdgeType side;
} Edge;

typedef struct Stripe {
    Interval x_interval;
    Interval y_interval;
    set<Interval> x_union;
} Stripe;

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
#endif