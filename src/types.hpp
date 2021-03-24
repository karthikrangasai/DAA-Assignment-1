/** @file types.hpp
 * @brief File containing all the data structures required to implement the paper.
 * @see https://link.springer.com/article/10.1007/BF00264251
*/
#ifndef TYPES_H
#define TYPES_H

#include <bits/stdc++.h>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

const int INF = 1e9;  /// Denotes the mathematical value of Infinity.

typedef long double Coord;

/**!
 * @brief Interval Type that denotes the mathematical Interval over a single axis, X or Y.
 */
typedef struct interval_t {
    int lo; /** Lower bound of the Interval. */
    int hi; /** Upper bound of the Interval. */
    interval_t(int lo = INF, int hi = -INF) {
        this->lo = lo;
        this->hi = hi;
    }
    bool operator==(const interval_t &other) const {
        return tie(lo, hi) == tie(other.lo, other.hi);
    }
    bool operator!=(const interval_t &other) const {
        return tie(lo, hi) != tie(other.lo, other.hi);
    }
    bool operator<(const interval_t &other) const {
        return tie(lo, hi) < tie(other.lo, other.hi);
    }
    bool operator>(const interval_t &other) const {
        return tie(lo, hi) > tie(other.lo, other.hi);
    }
    bool operator<=(const interval_t &other) const {
        return tie(lo, hi) <= tie(other.lo, other.hi);
    }
    bool operator>=(const interval_t &other) const {
        return tie(lo, hi) >= tie(other.lo, other.hi);
    }
    void print() {
        cout << "(" << lo << "," << hi << ")\n";
    }
} interval_t;

/**!
 * @brief Rectangle Type that is defined over two Intervals, one for X-axis and other for Y-axis.
 */
typedef struct rect_t {
    interval_t x_interval; /** The X-Interval spanned by the rectangle. */
    interval_t y_interval; /** The Y-Interval spanned by the rectangle. */
    int idx;               /** Integer used to uniquely identify the rectangle. */
    rect_t(interval_t x_interval, interval_t y_interval, int idx) {
        this->x_interval = x_interval;
        this->y_interval = y_interval;
        this->idx = idx;
    }
} rect_t;

/**!
 * @brief Denotes the side of a rectangle.
 */
typedef enum edgeType {
    UNDEF = -1, /** Used to denote an undetermined type. */
    LEFT,       /** Left edge of the rectangle. */
    RIGHT,      /** Right edge of the rectangle. */
    BOTTOM,     /** Bottom edge of the rectangle. */
    TOP         /** Top edge of the rectangle. */
} edgeType;

/**!
 * @brief Describes the edge of a rectangle using Interval, position, and edgeType.
 */
typedef struct edge_t {
    interval_t interval; /** the 1 dimensional range along x or y axis */
    int coord;           /** the position with respect to y or x axis. */
    int idx;             /** the index of the rectangle. */
    edgeType typ;        /** Edge type */
    edge_t(interval_t interval, int coord = -INF, int idx = -1, edgeType typ = UNDEF) {
        this->interval = interval;
        this->coord = coord;
        this->idx = idx;
        this->typ = typ;
    }
    bool operator==(const edge_t &other) const {
        return tie(coord, typ) == tie(other.coord, other.typ);
    }
    bool operator!=(const edge_t &other) const {
        return tie(coord, typ) != tie(other.coord, other.typ);
    }
    bool operator<=(const edge_t &other) const {
        return tie(coord, typ) <= tie(other.coord, other.typ);
    }
    bool operator>=(const edge_t &other) const {
        return tie(coord, typ) >= tie(other.coord, other.typ);
    }
    bool operator<(const edge_t &other) const {
        return tie(coord, typ) < tie(other.coord, other.typ);
    }
    bool operator>(const edge_t &other) const {
        return tie(coord, typ) > tie(other.coord, other.typ);
    }
} edge_t;

/**!
 * @brief Data structure to hold the edges for defining the Y-contour for a single stripe.
 */
typedef struct tree_t {
    int val;      /** */
    edgeType typ; /** */
    tree_t *lt;   /** */
    tree_t *rt;   /** */
    tree_t(int val = 0, tree_t *lt = nullptr, tree_t *rt = nullptr, edgeType typ = UNDEF) {
        this->val = val;
        this->lt = lt;
        this->rt = rt;
        this->typ = typ;
    }
} tree_t;

/**!
 * @brief Defines data-type to represent a two dimensional data-structure stripe, confined within two intervals parallel to x and y axes. It holds details of the area and contour of the union of rectangles intersecting with it.
 */
typedef struct stripe_t {
    interval_t x_interval;          /** interval parallel to x axis */
    interval_t y_interval;          /** interval parallel to y axis */
    tree_t *tre;                    /** binary-search-tree data-structure which holds the y contour pieces in its leaves */
    int measure;                    /** the value of total width of the union of rectangles intersecting with the stripe */
    vector<pair<int, edgeType> > J; /** the values of leaf nodes of the tre which are the y contour pieces in the form of its x coordinate and type (left side edge or right side edge) */
    stripe_t(interval_t x_int, interval_t y_int) {
        x_interval = x_int;
        y_interval = y_int;
        tre = nullptr;
        measure = 0;
    }
    void print() {
        cout << "{((" << x_interval.lo << "," << x_interval.hi << "),(" << y_interval.lo << "," << y_interval.hi << ")," << measure << "}\n";
    }
} stripe_t;

/**!
 * Defines a data-type to represent a tuple of list of pair of intervals and index, L, 
 * list of pair of intervals and index, R, 
 * list of integers to store coordinates for partition, P 
 * and, list of stripes S. We call for a given edge it's opposite sided edge belonging to the same rectangle as it's 'partner'. 
 * 
 * Let there be a rectangular frame F defined within a x and y interval. 
 * For all left-sided vertical edges in F, it's value pair of interval and index is stored in L if it's partner is not in F. 
 * For the same frame F, for all right-sided vertical edges in F, it's value pair of interval and index is stored in R if it's partner is not in F. 
 * P stores the list y-coordinates needed to partition F into stripes. 
 * S stores the list of stripes belonging to F.
 */
typedef struct result_t {
    vector<stripe_t> S;
    vector<pair<interval_t, int> > L;
    vector<pair<interval_t, int> > R;
    vector<int> P;
    result_t() {}
    result_t(vector<pair<interval_t, int> > L, vector<pair<interval_t, int> > R, vector<int> P, vector<stripe_t> S) {
        this->L = L;
        this->R = R;
        this->P = P;
        this->S = S;
    }
} result_t;

#ifdef __cplusplus
}
#endif
#endif