#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void dfs(int cur, vector<int>& graph, vector<int>& flags, vector<int>& times, vector<int>& dists, int time, int& res_loop) {
    flags[cur] = 1;
    times[cur] = time;
    int nxt = graph[cur];

    if (nxt != -1) {
        if (flags[nxt] == 0) {
            dfs(nxt, graph, flags, times, dists, time + 1, res_loop);
        } else if (flags[nxt] == 1) {
            res_loop = min(res_loop, time - times[nxt] + 1);
        }
        dists[cur] = dists[nxt] + 1;
    }
    flags[cur] = 2;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> graph(n + 1);
    vector<int> indegree(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> graph[i];
        indegree[graph[i]]++;
    }

    int res_loop = INT_MAX;
    vector<int> flags(n + 1, 0);
    vector<int> times(n + 1, 0);
    vector<int> dists(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            dfs(i, graph, flags, times, dists, 0, res_loop);
        }
    }

    if (res_loop != INT_MAX) {
        cout << res_loop << endl;
    } else {
        int res_non_loop = 0;
        for (int dist : dists) {
            res_non_loop = max(res_non_loop, dist);
        }
        cout << res_non_loop << endl;
    }
}
