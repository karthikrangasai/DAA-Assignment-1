#include "src/utils.hpp"

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        cout << "Invalid inputs" << endl;
    }

    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    int n;
    vector<rect_t> R;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        if (x2 < x1) swap(x1, x2);
        if (y2 < y1) swap(y1, y2);
        R.push_back(rect_t(interval_t(x1, x2), interval_t(y1, y2), i));
    }
    auto start = chrono::steady_clock::now();
    vector<stripe_t> S = Rectangle_DAC(R);
    long long ans = 0;
    for (auto s : S) {
        ans += 1LL * (s.y_interval.hi - s.y_interval.lo) * (s.measure);
        // cout<<s.y_interval.lo<<' '<<s.y_interval.hi<<' '<<s.measure<<'\n';
    }
    // cout << ans << '\n';
    // cout<<"S: \n";
    for (auto &s : S) {
        // s.print();
        // cout<<" "<<(s.tre == nullptr)<<'\n';
        dfs(s);
    }
    // cout<<'\n';
    // contour
    vector<pair<int, pair<int, edgeType> > > Ht, Hb;
    for (auto r : R) {
        edge_t e(r.x_interval, r.y_interval.lo, r.idx, BOTTOM);
        edge_t ep(r.x_interval, r.y_interval.hi, r.idx, TOP);
        Hb.push_back(make_pair(e.coord, make_pair(e.interval.lo, LEFT)));
        Hb.push_back(make_pair(e.coord, make_pair(e.interval.hi, RIGHT)));
        Ht.push_back(make_pair(ep.coord, make_pair(ep.interval.lo, LEFT)));
        Ht.push_back(make_pair(ep.coord, make_pair(ep.interval.hi, RIGHT)));
    }
    sort(Ht.begin(), Ht.end());
    sort(Hb.begin(), Hb.end());

    int k = 0;
    // for(auto it:Hb){
    //   cout<<it.first<<'\n';
    // }
    for (int i = 0; i < Hb.size();) {
        int j = i;
        while (j < Hb.size() and Hb[i].first == Hb[j].first) ++j;
        int l = i, r = 0;
        while (k < S.size() and S[k].y_interval.hi != Hb[i].first) ++k;
        int EP = 0, XUP = 0;
        vector<int> JJ;
        // cout<<l<<' '<<j<<' '<<r<<' '<<S[k].J.size()<<'\n';
        while (l < j and r < S[k].J.size()) {
            if (Hb[l].second.first < S[k].J[r].first) {
                if (Hb[l].second.second == LEFT) {
                    if (!EP and !XUP)
                        JJ.push_back(Hb[l].second.first);
                    ++EP;
                } else {
                    if (EP == 1 and !XUP)
                        JJ.push_back(Hb[l].second.first);
                    --EP;
                }
                ++l;
            } else if (Hb[l].second.first > S[k].J[r].first) {
                if (S[k].J[r].second == LEFT) {
                    if (!XUP and EP)
                        JJ.push_back(S[k].J[r].first);
                    ++XUP;
                } else {
                    if (XUP == 1 and EP)
                        JJ.push_back(S[k].J[r].first);
                    --XUP;
                }
                ++r;
            } else {
                if (S[k].J[r].second == LEFT) {
                    if (!XUP and EP)
                        JJ.push_back(S[k].J[r].first);
                    ++XUP;
                    ++r;
                } else {
                    if (Hb[l].second.second == LEFT) {
                        if (!EP and !XUP)
                            JJ.push_back(Hb[l].second.first);
                        ++EP;
                    } else {
                        if (EP == 1 and !XUP)
                            JJ.push_back(Hb[l].second.first);
                        --EP;
                    }
                    ++l;
                }
            }  //<-- fi
        }      //<-- while closes
        while (l < j) {
            if (Hb[l].second.second == LEFT) {
                if (!EP and !XUP)
                    JJ.push_back(Hb[l].second.first);
                ++EP;
            } else {
                if (EP == 1 and !XUP)
                    JJ.push_back(Hb[l].second.first);
                --EP;
            }
            ++l;
        }
        // cout<<" HOR "<<k<<' '<<Hb[i].first<<'\n';

        // for (int ii = 0; ii < JJ.size(); ii += 2) {
        //     cout << JJ[ii] << ' ' << JJ[ii + 1] << ' ' << Hb[i].first << '\n';
        //     // cout<<"{"<<JJ[ii]<<"<=x<="<<JJ[ii+1]<<"}y="<<Hb[i].first<<"\n";
        // }

        i = j;
    }  //<-- for ends

    k = 0;
    for (int i = 0; i < Ht.size();) {
        int j = i;
        while (j < Ht.size() and Ht[i].first == Ht[j].first) ++j;
        int l = i, r = 0;
        while (k < S.size() and S[k].y_interval.lo != Ht[i].first) ++k;
        int EP = 0, XUP = 0;
        vector<int> JJ;
        while (l < j and r < S[k].J.size()) {
            if (Ht[l].second.first < S[k].J[r].first) {
                if (Ht[l].second.second == LEFT) {
                    if (!EP and !XUP)
                        JJ.push_back(Ht[l].second.first);
                    ++EP;
                } else {
                    if (EP == 1 and !XUP)
                        JJ.push_back(Ht[l].second.first);
                    --EP;
                }
                ++l;
            } else if (Ht[l].second.first > S[k].J[r].first) {
                if (S[k].J[r].second == LEFT) {
                    if (!XUP and EP)
                        JJ.push_back(S[k].J[r].first);
                    ++XUP;
                } else {
                    if (XUP == 1 and EP)
                        JJ.push_back(S[k].J[r].first);
                    --XUP;
                }
                ++r;
            } else {
                if (S[k].J[r].second == LEFT) {
                    if (!XUP and EP)
                        JJ.push_back(S[k].J[r].first);
                    ++XUP;
                    ++r;
                } else {
                    if (Ht[l].second.second == LEFT) {
                        if (!EP and !XUP)
                            JJ.push_back(Ht[l].second.first);
                        ++EP;
                    } else {
                        if (EP == 1 and !XUP)
                            JJ.push_back(Ht[l].second.first);
                        --EP;
                    }
                    ++l;
                }
            }
            //<-- fi
        }  //<-- while closes
        while (l < j) {
            if (Ht[l].second.second == LEFT) {
                if (!EP and !XUP)
                    JJ.push_back(Ht[l].second.first);
                ++EP;
            } else {
                if (EP == 1 and !XUP)
                    JJ.push_back(Ht[l].second.first);
                --EP;
            }
            ++l;
        }
        // cout<<" HOR "<<k<<' '<<Ht[i].first<<'\n';

        // for (int ii = 0; ii < JJ.size(); ii += 2) {
        //     cout << JJ[ii] << ' ' << JJ[ii + 1] << ' ' << Ht[i].first << '\n';
        //     // cout<<"{"<<JJ[ii]<<"<=x<="<<JJ[ii+1]<<"}y="<<Ht[i].first<<"\n";
        // }

        i = j;
    }  //<-- for end

    // cout << "@\n";
    // for (const auto &s : S) {
    //     for (int i = 0; i < (int)s.J.size(); ++i) {
    //         cout << s.y_interval.lo << ' ' << s.y_interval.hi << ' ' << s.J[i].first << '\n';
    //     }
    // }
    auto end = chrono::steady_clock::now();
    // cout<<chrono::duration_cast<chrono::seconds>(end-start).count()<<"s\n";
    cout << n << " " << ans << " " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
    return 0;
}