#include "utils.hpp"

#include "types.hpp"

set<Point> _union(set<Rectangle> R) {
    set<Point> unionOfPoints;
    for (const Rectangle& r : R) {
        if (r.isInterval) {
            unionOfPoints.insert(Point(r.x_interval.bottom, r.y_interval.bottom));
            unionOfPoints.insert(Point(r.x_interval.top, r.y_interval.top));
        } else {
            unionOfPoints.insert(Point(r.x_left, r.y_bottom));
            unionOfPoints.insert(Point(r.x_right, r.y_top));
        }
    }
    return unionOfPoints;
}

set<Coord> y_set(set<Rectangle> R) {
    set<Coord> y_values;
    for (const Rectangle& r : R) {
        if (r.isInterval) {
            y_values.insert(r.y_interval.top);
            y_values.insert(r.y_interval.bottom);
        } else {
            y_values.insert(r.y_bottom);
            y_values.insert(r.y_top);
        }
    }
    return y_values;
}

set<Interval> partition(set<Coord> Y) {
    // 1,2,3,4,5,6,7,8,9
    // Answers: (1,2), (8,9)
    // for all y <= y1 and y1 < y
    // but ys also belongs to Y then y = y2

    // Let us assume all possible pairs such that y1<y2
    set<Interval> intervals;
    for (auto it = Y.begin(); it != Y.end(); ++it) {
        auto it2 = Y.begin();
        ++it2;
        if (it2 != Y.end()) {
            for (; it2 != Y.end(); ++it2) {
                intervals.insert(Interval(*it, *it2));
            }
        }
    }
    return intervals;
}

set<Coord> x_proj(set<Point> P);
set<Interval> intervals(set<Coord> C);
set<Stripe> stripes(set<Rectangle> R, Rectangle f);

real measure(set<Stripe> S);
set<LineSegment> contour_pieces(Edge h, set<Stripe> S);
set<LineSegment> contour(set<Edge> H, set<Stripe> S);