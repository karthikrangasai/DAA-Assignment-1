/** @file utils.cpp
 * @brief Implementation of all the necessary functions of the paper
 * @see https://link.springer.com/article/10.1007/BF00264251
*/
#include "utils.hpp"

#include "types.hpp"

/**
 * @brief Given a P for a frame, partition outputs a list of intervals needed to partition the frame into stripes.
 * 
 * @param P Set of Points
 * @return List of Intervals defined pair-wise over the points.
 */
vector<interval_t> partition(const vector<int> &P) {
    vector<interval_t> prtn;
    for (int i = 0; i + 1 < (int)P.size(); ++i) {
        prtn.push_back(interval_t(P[i], P[i + 1]));
    }
    return prtn;
}

/**
 * @brief Given a list of stripes, S, belonging to one half of the frame-divide, F1, and a list of pair of interval and index of vertical edges, J, belonging to the other half the frame-divide, F2. For each vertical edge 'e' in J, blacken chooses all stripes, s, whose y intervals completely intersect with the interval of 'e' and updates their measure to be F1's width along x-axis, and marks their tree to be empty as there are no edges which can be a part of the y-contour pieces from 's' as it's fully intersected by a rectangle starting in the frame F2.
 * 
 * @param S Set of stripes
 * @param J Set of Intervals (Represented as pair of interval mapped to its reactangle).
 */
void blacken(vector<stripe_t> &S, const vector<pair<interval_t, int> > &J) {
    vector<int> disjointRange;
    int hi = -INF;
    for (const auto &i : J) {
        if (i.first.lo <= hi) {
            hi = max(i.first.hi, hi);
        } else {
            if (hi != -INF) disjointRange.push_back(hi);
            disjointRange.push_back(i.first.lo);
            hi = i.first.hi;
        }
    }
    if (!disjointRange.empty())
        disjointRange.push_back(hi);
    size_t cur = 0;
    for (auto &s : S) {
        while (cur < disjointRange.size() and disjointRange[cur + 1] < s.y_interval.lo) cur += 2;
        if (cur >= disjointRange.size()) break;
        if (s.y_interval.lo >= disjointRange[cur] and s.y_interval.hi <= disjointRange[cur + 1]) {
            s.measure = s.x_interval.hi - s.x_interval.lo;
            s.tre = nullptr;
        }
    }
    return;
}

/**
 * @brief For a frame F. Given a list of stripes, S, partition p and the x-interval, x_int, of F. Copy outputs a new list of stripes, S', from a finer partition p for F, without loss of data with respect to S. For each stripe, s in S, copy chooses all stripes, s' in S' such that it fully intersects s and copies tre and measure data of s into s'.
 * 
 * @param S Set of stripes
 * @param p Set of Points
 * @param x_int Set of Points
 * @return Set of stripes
 */
vector<stripe_t> copy(const vector<stripe_t> &S, const vector<interval_t> &p, const interval_t &x_int) {
    vector<stripe_t> _S;
    for (const auto &i : p) {
        stripe_t _s(x_int, i);
        _S.push_back(_s);
    }
    size_t cur = 0;
    for (auto &_s : _S) {
        while (cur < S.size() and S[cur].y_interval.hi <= _s.y_interval.lo) ++cur;
        if (cur >= S.size()) break;
        if (_s.y_interval.lo >= S[cur].y_interval.lo and _s.y_interval.hi <= S[cur].y_interval.hi) {
            _s.measure = S[cur].measure;
            _s.tre = S[cur].tre;
        }
    }
    return _S;
}

/**
 * @brief Given list of stripes S1 from left-half of frame-divide, F1, and list of stripes S2 from right-half of frame-divide, F2, a finer partition p of frame F and a x-interval of combined frame F of the two frames F1 and F2. Concat outputs a new list of stripes S, such that for each stripe in s in S it chooses a stripe s1 in S1, and a stripe s2 in S2 which have the same y interval of s and updates measure of s to be the summation of measures of s1 and s2, and creates a root node for tree in s and updates it's left and right children to tree of s1 and s2 respectively.
 * 
 * @param S1 Set of stripes
 * @param S2 Set of stripes
 * @param p Set of intervals
 * @param x_int An X-Interval
 * @return Set of stripes
 */
vector<stripe_t> concat(const vector<stripe_t> &S1, const vector<stripe_t> &S2, const vector<interval_t> &p, const interval_t &x_int) {
    vector<stripe_t> S;
    for (const auto &i : p) {
        stripe_t s(x_int, i);
        S.push_back(s);
    }
    int cur = 0;
    for (auto &s : S) {
        s.measure = S1[cur].measure + S2[cur].measure;
        if (S1[cur].tre and S2[cur].tre) {
            s.tre = new tree_t(S1[cur].x_interval.hi, S1[cur].tre, S2[cur].tre, UNDEF);
        } else if (S1[cur].tre) {
            s.tre = S1[cur].tre;
        } else if (S2[cur].tre) {
            s.tre = S2[cur].tre;
        }
        ++cur;
    }
    return S;
}

/**
 * @brief Let F1 and F2 be the left and right half frames respectively wrt the vertical frame-divide line at coordinate, xm, of frame F. Given result of left-half frame F1, fh, result of right-half frame F2, sh, a frame-divide coordinate xm, and x-interval of F. Combine outputs, res of data-type result_t, a tuple of list of pair of intervals and index of left-side vertical edges, L, list of pair of intervals and index of right-side vertical edges, R, list of integers to store coordinates for partition, P and, list of stripes S.
 * 
 * @param fh 
 * @param sh 
 * @param x_ext An X-Interval
 * @param xm An X-Interval
 * @return 
 */
result_t combine(const result_t &fh, const result_t &sh, const interval_t &x_ext, const int xm) {
    vector<stripe_t> S1 = fh.S, S2 = sh.S;
    vector<pair<interval_t, int> > L1 = fh.L, R1 = fh.R, L2 = sh.L, R2 = sh.R;
    vector<int> P1 = fh.P, P2 = sh.P;

    result_t res;  // this is our new result

    vector<pair<interval_t, int> > &L = res.L;
    vector<pair<interval_t, int> > &R = res.R;
    vector<stripe_t> &S = res.S;
    vector<int> &P = res.P;

    //P1 U P2
    int l = 0, r = 0;
    while (l < (int)P1.size() and r < (int)P2.size()) {
        if (P1[l] < P2[r]) {
            P.push_back(P1[l++]);
        } else {
            P.push_back(P2[r++]);
        }
    }
    while (l < (int)P1.size()) P.push_back(P1[l++]);
    while (r < (int)P2.size()) P.push_back(P2[r++]);
    P.resize(distance(P.begin(), unique(P.begin(), P.end())));

    // get L1\LR and R2\LR in one go
    vector<pair<interval_t, int> > Ls, Rs;
    l = 0, r = 0;
    while (l < (int)L1.size() and r < (int)R2.size()) {
        if (L1[l] < R2[r]) {
            Ls.push_back(L1[l++]);
        } else if (L1[l] > R2[r]) {
            Rs.push_back(R2[r++]);
        } else {
            ++r, ++l;
        }
    }
    while (l < (int)L1.size()) {
        Ls.push_back(L1[l++]);
    }
    while (r < (int)R2.size()) {
        Rs.push_back(R2[r++]);
    }

    //get R = R1 U (R2\LR)
    l = 0, r = 0;
    while (l < (int)Rs.size() and r < (int)R1.size()) {
        if (Rs[l] < R1[r]) {
            R.push_back(Rs[l++]);
        } else {
            R.push_back(R1[r++]);
        }
    }
    while (l < (int)Rs.size()) {
        R.push_back(Rs[l++]);
    }
    while (r < (int)R1.size()) {
        R.push_back(R1[r++]);
    }

    //get L = L2 U (L1\LR)
    l = 0, r = 0;
    while (l < (int)Ls.size() and r < (int)L2.size()) {
        if (Ls[l] < L2[r]) {
            L.push_back(Ls[l++]);
        } else {
            L.push_back(L2[r++]);
        }
    }
    while (l < (int)Ls.size()) {
        L.push_back(Ls[l++]);
    }
    while (r < (int)L2.size()) {
        L.push_back(L2[r++]);
    }

    //get copy of S1 and S2 into Sl and Sr
    vector<stripe_t> Sl, Sr;
    vector<interval_t> p = partition(P);
    Sl = copy(S1, p, interval_t(x_ext.lo, xm));
    Sr = copy(S2, p, interval_t(xm, x_ext.hi));

    //perform blacken on Sl and Sr
    blacken(Sl, Rs);
    blacken(Sr, Ls);
    //Concatenate Sl and Sr into S
    S = concat(Sl, Sr, p, x_ext);

    return res;
}

/**
 * @brief For a frame F which encloses all the rectangles. Given a list of vertical edges, V, x-interval of frame F, x_ext and current working space of list V, with lo and hi as lowerbound and upperbound respectively. STRIPES outputs a tuple of list of pair of intervals and index of left-side vertical edges, L, list of pair of intervals and index of right-side vertical edges, R, list of integers to store coordinates for partition, P and, list of stripes S. Where S is the final configuration of list of stripes for F.
 * 
 * @param V
 * @param x_ext
 * @param lo
 * @param hi
 * @return 
 */
result_t STRIPES(const vector<edge_t> &V, interval_t x_ext, int lo, int hi) {
    vector<stripe_t> S;
    vector<pair<interval_t, int> > L, R;
    vector<int> P;
    if (lo == hi) {
        edge_t v = V[lo];
        if (v.typ == LEFT) {
            L.push_back(make_pair(v.interval, v.idx));
        } else {
            R.push_back(make_pair(v.interval, v.idx));
        }
        P = {-INF, v.interval.lo, v.interval.hi, INF};
        vector<interval_t> p = partition(P);
        for (auto i : p) {
            stripe_t s(x_ext, i);
            S.push_back(s);
        }
        auto it = S.begin();
        while (it->y_interval != v.interval) ++it;
        if (v.typ == LEFT) {
            it->measure = x_ext.hi - v.coord;
            it->tre = new tree_t(v.coord, nullptr, nullptr, LEFT);
        } else {
            it->measure = v.coord - x_ext.lo;
            it->tre = new tree_t(v.coord, nullptr, nullptr, RIGHT);
        }
        return result_t(L, R, P, S);
    }
    int mid = (lo + hi) >> 1;
    int xm = V[mid].coord;
    result_t fh = STRIPES(V, interval_t(x_ext.lo, xm), lo, mid);
    result_t sh = STRIPES(V, interval_t(xm, x_ext.hi), mid + 1, hi);
    return combine(fh, sh, x_ext, xm);
}

/**
 * @brief Given a list of rectangles, RECT. For a frame F enclosing RECT. Rectangle_DAC initializes a sorted list of vertical edges, VRX and acts as a driver function for the main divide and conquer function, STRIPES, and stores it's output in 'sol' as data-type, result_t. It finally outputs list of stripes, S, in sol.
 * 
 * @param RECT
 * @return Set of stripes
 */
vector<stripe_t> Rectangle_DAC(const vector<rect_t> &RECT) {
    vector<edge_t> VRX;
    for (const auto &r : RECT) {
        edge_t e(r.y_interval, r.x_interval.lo, r.idx, LEFT);
        edge_t ep(r.y_interval, r.x_interval.hi, r.idx, RIGHT);
        VRX.push_back(e);
        VRX.push_back(ep);
    }
    sort(VRX.begin(), VRX.end());
    interval_t x_ext(VRX.front().coord, VRX.back().coord);
    result_t sol = STRIPES(VRX, x_ext, 0, (int)VRX.size() - 1);
    return sol.S;
}

/**
 * @brief Given a stripe, s. dfs populates the container J of s with leaf nodes of tree tre in s, with an iterative stack based depth-first-search.
 * 
 * @param s
 */
void dfs(stripe_t &s) {
    tree_t *node = s.tre;
    if (!node) return;
    stack<tree_t *> Stack;
    Stack.push(node);
    while (!Stack.empty()) {
        node = Stack.top();
        Stack.pop();
        if (!node->rt and !node->lt) {
            // cout<<node->val<<' '<<node->typ<<'\n';
            s.J.push_back(make_pair(node->val, node->typ));
            continue;
        }
        if (node->rt)
            Stack.push(node->rt);
        if (node->lt)
            Stack.push(node->lt);
    }
    return;
}