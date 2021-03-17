#include "utils.hpp"

#include "types.hpp"

vector<interval_t> partition(vector<int> P) {
    vector<interval_t> prtn;
    for (int i = 0; i + 1 < (int)P.size(); ++i) {
        prtn.push_back(interval_t(P[i], P[i + 1]));
    }
    return prtn;
}

void blacken(vector<stripe_t> &S, vector<pair<interval_t, int> > &J) {
    int r = 0;
    vector<int> disjointRange;
    int hi = -INF;
    for (auto i : J) {
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
    int cur = 0;
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

vector<stripe_t> copy(vector<stripe_t> &S, vector<interval_t> &p, interval_t x_int) {
    // vector<interval_t> p = partition(P);
    vector<stripe_t> _S;
    for (auto i : p) {
        stripe_t _s(x_int, i);
        _S.push_back(_s);
    }
    int cur = 0;
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

vector<stripe_t> concat(vector<stripe_t> &S1, vector<stripe_t> &S2, vector<interval_t> &p, interval_t x_int) {
    // vector<interval_t> p = partition(P);
    vector<stripe_t> S;
    for (auto i : p) {
        stripe_t s(x_int, i);
        S.push_back(s);
    }
    int cur = 0;
    for (auto &s : S) {
        s.measure = S1[cur].measure + S2[cur].measure;
        if (S1[cur].tre and S2[cur].tre) {
            // if(tie(S1[cur].tre->val, S1[cur].tre->typ) == tie(S2[cur].tre->val, S2[cur].tre->typ)){
            //   s.tre = S1[cur].tre;
            // }
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

result_t combine(const result_t &fh, const result_t &sh, interval_t x_ext, int xm) {
    vector<stripe_t> S1 = fh.S, S2 = sh.S;
    vector<pair<interval_t, int> > L1 = fh.L, R1 = fh.R, L2 = sh.L, R2 = sh.R;
    vector<int> P1 = fh.P, P2 = sh.P;

    // cout<<" P1 : ";
    // for(auto it:P1){
    //   cout<<it<<' ';
    // }
    // cout<<'\n';
    // cout<<" P2 : ";
    // for(auto it:P2){
    //   cout<<it<<' ';
    // }
    // cout<<'\n';
    // cout<<" L1 : ";
    // for(auto it:L1){
    //   cout<<"(("<<it.first.lo<<','<<it.first.hi<<"), "<<it.second<<") \n";
    // }
    // cout<<'\n';
    // cout<<" L2 : ";
    // for(auto it:L2){
    //   cout<<"(("<<it.first.lo<<','<<it.first.hi<<"), "<<it.second<<") \n";
    // }
    // cout<<'\n';
    // cout<<" R1 : ";
    // for(auto it:R1){
    //   cout<<"(("<<it.first.lo<<','<<it.first.hi<<"), "<<it.second<<") \n";
    // }
    // cout<<'\n';
    // cout<<" R2 : ";
    // for(auto it:R2){
    //   cout<<"(("<<it.first.lo<<','<<it.first.hi<<"), "<<it.second<<") \n";
    // }

    vector<pair<interval_t, int> > L, R;
    vector<stripe_t> S;
    vector<int> P;

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

    // cout<<" P : ";
    // for(auto it:P){
    //   cout<<it<<' ';
    // }
    // cout<<'\n';

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

    // cout<<" Ls : ";
    // for(auto it:Ls){
    //   cout<<"(("<<it.first.lo<<','<<it.first.hi<<"), "<<it.second<<") \n";
    // }
    // cout<<'\n';
    // cout<<" Rs : ";
    // for(auto it:Rs){
    //   cout<<"(("<<it.first.lo<<','<<it.first.hi<<"), "<<it.second<<") \n";
    // }
    // cout<<'\n';
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

    // cout<<" L : ";
    // for(auto it:L){
    //   cout<<"(("<<it.first.lo<<','<<it.first.hi<<"), "<<it.second<<") \n";
    // }
    // cout<<'\n';
    // cout<<" R : ";
    // for(auto it:R){
    //   cout<<"(("<<it.first.lo<<','<<it.first.hi<<"), "<<it.second<<") \n";
    // }
    // cout<<'\n';

    // cout<<"S1 : \n";
    // for(auto it:S1){
    //   it.print();
    //   cout<<'\n';
    // }
    // cout<<"S2 : \n";
    // for(auto it:S2){
    //   it.print();
    //   cout<<'\n';
    // }
    // cout<<'\n';
    //get copy of S1 and S2 into Sl and Sr
    vector<stripe_t> Sl, Sr;
    vector<interval_t> p = partition(P);
    Sl = copy(S1, p, interval_t(x_ext.lo, xm));
    Sr = copy(S2, p, interval_t(xm, x_ext.hi));

    // cout<<"Sl : \n";
    // for(auto it:Sl){
    //   it.print();
    //   cout<<'\n';
    // }
    // cout<<"Sr : \n";
    // for(auto it:Sr){
    //   it.print();
    //   cout<<'\n';
    // }
    // cout<<'\n';
    //perform blacken on Sl and Sr
    blacken(Sl, Rs);
    blacken(Sr, Ls);
    // cout<<"After Blacken :\n";
    // cout<<"Sl : \n";
    // for(auto it:Sl){
    //   it.print();
    //   cout<<" "<<(it.tre == nullptr)<<'\n';
    // }
    // cout<<"Sr : \n";
    // for(auto it:Sr){
    //   it.print();
    //   cout<<" "<<(it.tre == nullptr)<<'\n';
    // }
    // cout<<'\n';
    //Concatenate Sl and Sr into S
    S = concat(Sl, Sr, p, x_ext);

    return result_t(L, R, P, S);
}

result_t STRIPES(vector<edge_t> &V, interval_t x_ext, int lo, int hi) {
    // cout<<x_ext.lo<<' '<<x_ext.hi<<' '<<lo<<' '<<hi<<'\n';
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
            // i.print();
            // cout<<'\n';
            // s.print();
            // cout<<'\n';
            S.push_back(s);
        }
        auto it = S.begin();
        while (it->y_interval != v.interval) ++it;
        if (v.typ == LEFT) {
            it->measure = x_ext.hi - v.coord;
            it->tre = new tree_t(v.coord, nullptr, nullptr, LEFT);
        } else {
            // it->print();
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

vector<stripe_t> Rectangle_DAC(vector<rect_t> &RECT) {
    vector<edge_t> VRX;
    for (auto r : RECT) {
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

// vector<interval_t> query(tree_t *node, interval_t x_int) {
//     x_int.print();
//     cin >> dum;
//     stack<tree_t *> Stack;
//     Stack.push(node);
//     if (node == nullptr) {
//         cout << "WTF";
//     }
//     cin >> dum;
//     vector<pair<int, edgeType> > Q;
//     while (!Stack.empty()) {
//         node = Stack.top();
//         Stack.pop();
//         if (!node->rt and node->lt and node->val >= x_int.lo and node->val <= x_int.hi) {
//             Q.push_back(make_pair(node->val, node->typ));
//             continue;
//         }
//         if (x_int.hi < node->val and node->lt)
//             Stack.push(node->lt);
//         else if (x_int.lo > node->val and node->rt)
//             Stack.push(node->rt);
//         else {
//             if (node->rt)
//                 Stack.push(node->rt);
//             if (node->lt)
//                 Stack.push(node->lt);
//         }
//     }
//     vector<interval_t> J;
//     for (int i = 0; i + 1 < Q.size(); ++i) {
//         if (Q[i].second == RIGHT and Q[i + 1].second == LEFT) {
//             J.push_back(interval_t(Q[i].first, Q[i + 1].first));
//         }
//     }
//     return J;
// }

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
    // if(!node->lt and !node->rt){
    //   cout<<node->val<<' '<<node->typ<<'\n';
    //   return;
    // }
    // if(node->lt){
    //   dfs(node->lt);
    // }
    // if(node->rt){
    //   dfs(node->rt);
    // }
    return;
}