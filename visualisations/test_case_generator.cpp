#include <bits/stdc++.h>

using namespace std;

#define rn dist(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<long> dist(-100, 100);

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        return 1;
    }

    uniform_int_distribution<long> dist(-atoi(argv[3]), atoi(argv[3]));

    int n = atoi(argv[1]);
    // cout << "Number of rectangles generating: " << n << '\n';
    freopen(argv[2], "w", stdout);
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        unordered_set<int> s;
        while (s.size() < 4) s.insert(rn);
        set<int> x_points;  // to store x values
        auto it = s.begin();
        x_points.insert(*it);
        it++;
        x_points.insert(*it);
        set<int> y_points;  // to store y values
        it++;
        y_points.insert(*it);
        it++;
        y_points.insert(*it);
        for (auto pt : x_points) cout << pt << " ";
        for (auto pt : y_points) cout << pt << " ";
        cout << '\n';
    }
    return 0;
}