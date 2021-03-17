#ifndef TYPES_H
#define TYPES_H

#include <bits/stdc++.h>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

const int INF = 1e9;

typedef long double Coord;

// typedef struct Point {
//     Coord x;
//     Coord y;
//     Point(Coord _x, Coord _y) {
//         x = _x;
//         y = _y;
//     }
// } Point;

// int dum;

typedef struct interval_t {
    int lo, hi;
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

typedef struct LineSegment {
    interval_t interval;
    Coord coord;
} LineSegment;

typedef struct rect_t {
    interval_t x_interval, y_interval;
    int idx;
    rect_t(interval_t x_interval, interval_t y_interval, int idx) {
        this->x_interval = x_interval;
        this->y_interval = y_interval;
        this->idx = idx;
    }
} rect_t;

typedef enum edgeType {
    UNDEF = -1,
    LEFT,
    RIGHT,
    BOTTOM,
    TOP
} edgeType;

typedef struct edge_t {
    interval_t interval;
    int coord, idx;
    edgeType typ;
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

typedef struct tree_t {
    int val;
    edgeType typ;
    tree_t *lt, *rt;
    tree_t(int val = 0, tree_t *lt = nullptr, tree_t *rt = nullptr, edgeType typ = UNDEF) {
        this->val = val;
        this->lt = lt;
        this->rt = rt;
        this->typ = typ;
    }
} tree_t;

typedef struct stripe_t {
    interval_t x_interval, y_interval;
    tree_t *tre;
    int measure;
    vector<pair<int, edgeType> > J;
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

typedef struct result_t {
    vector<stripe_t> S;
    vector<pair<interval_t, int> > L, R;
    vector<int> P;
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