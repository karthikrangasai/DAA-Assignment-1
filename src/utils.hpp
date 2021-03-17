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

vector<interval_t> partition(vector<int> P);
void blacken(vector<stripe_t> &S, vector<pair<interval_t, int> > &J);
vector<stripe_t> copy(vector<stripe_t> &S, vector<interval_t> &p, interval_t x_int);

vector<stripe_t> concat(vector<stripe_t> &S1, vector<stripe_t> &S2, vector<interval_t> &p, interval_t x_int);
result_t combine(const result_t &fh, const result_t &sh, interval_t x_ext, int xm);
result_t STRIPES(vector<edge_t> &V, interval_t x_ext, int lo, int hi);

vector<stripe_t> Rectangle_DAC(vector<rect_t> &RECT);
vector<interval_t> query(tree_t *node, interval_t x_int);
void dfs(stripe_t &s);
#ifdef __cplusplus
}
#endif
#endif