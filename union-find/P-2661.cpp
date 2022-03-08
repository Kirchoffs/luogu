#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int find(vector<int>& parents, vector<int>& dists, int x) {
    if (parents[x] != x) {
        int p = parents[x];
        parents[x] = find(parents, dists, p);
        dists[x] += dists[p];
    }

    return parents[x];
}

int main() {
    int n;
    cin >> n;
    
    vector<int> parents(n + 1);
    for (int i = 1; i <= n; i++) {
        parents[i] = i;
    }

    vector<int> dists(n + 1);
    int res = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        int root = find(parents, dists, t);
        if (root == i) {
            res = min(res, dists[t] + 1);
        } else {
            parents[i] = root;
            dists[i] = dists[t] + 1;
        }
    }

    cout << res << endl;
}
