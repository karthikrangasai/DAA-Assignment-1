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

vector<interval_t> partition(const vector<int> &P);

void blacken(vector<stripe_t> &S, const vector<pair<interval_t, int> > &J);
vector<stripe_t> copy(const vector<stripe_t> &S, const vector<interval_t> &p, const interval_t &x_int);
vector<stripe_t> concat(const vector<stripe_t> &S1, const vector<stripe_t> &S2, const vector<interval_t> &p, const interval_t &x_int);

result_t combine(const result_t &fh, const result_t &sh, const interval_t &x_ext, const int xm);
result_t STRIPES(const vector<edge_t> &V, interval_t x_ext, int lo, int hi);

vector<stripe_t> Rectangle_DAC(const vector<rect_t> &RECT);

void dfs(stripe_t &s);

#ifdef __cplusplus
}
#endif
#endif