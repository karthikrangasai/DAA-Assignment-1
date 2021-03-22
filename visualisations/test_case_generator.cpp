#include <bits/stdc++.h>

using namespace std;

#define rn dist(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const vector<int> sign = {-1, 1};

vector<long> createPoints(long dimension, uniform_int_distribution<long> distribution, int bit) {
    long X1 = sign[bit & 1] * distribution(rng);
    long Y1 = sign[(bit & 2) == 2] * distribution(rng);
    long X_width = distribution(rng) / 2 + 1;
    long Y_width = distribution(rng) / 2 + 1;

    long frameRight = (bit & 1) * dimension;
    long frameTop = ((bit & 2) == 2) * dimension;

    // bit	frameTop	frameRight	quad
    // 0      0           0          3
    // 1      0           1          4
    // 2      1           0          2
    // 3      1           1          1

    long X2 = (X1 + X_width > frameRight) ? (X1 - X_width) : (X1 + X_width);
    long Y2 = (Y1 + Y_width > frameTop) ? (Y1 - Y_width) : (Y1 + Y_width);

    if (X1 > X2) swap(X1, X2);
    if (Y1 > Y2) swap(Y1, Y2);
    // return {X1, X2, Y1, Y2, X_width, Y_width, frameRight, frameTop};
    return {X1, X2, Y1, Y2};
}

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        return 1;
    }

    int n = atoi(argv[1]);

    long dimension = atoi(argv[3]);

    if (n > (dimension * (2 * dimension - 1))) {
        cout << "Entire area will be output. Not a good testcase. Please suck it and change the inputs.\n";
        exit(1);
    }

    freopen(argv[2], "w", stdout);
    uniform_int_distribution<long> distribution(0, dimension);

    cout << n << endl;
    for (int i = 0; i < n; i++) {
        int bit = i % 4;
        vector<long> points = createPoints(dimension, distribution, bit);
        cout << points[0] << " " << points[1] << " " << points[2] << " " << points[3] << "\n";
    }
    fclose(stdout);
    return 0;
}