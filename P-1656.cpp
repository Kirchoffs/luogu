#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(vector<vector<int>>& graph, vector<int>& index, vector<int>& low_link, 
         int& time, int cur, int pre, vector<pair<int, int>>& res) {
    index[cur] = low_link[cur] = time++;
    for (int nxt: graph[cur]) {
        if (nxt == pre) {
            continue;
        }

        if (index[nxt] == -1) {
            dfs(graph, index, low_link, time, nxt, cur, res);
            low_link[cur] = min(low_link[cur], low_link[nxt]);
            if (low_link[nxt] > index[cur]) {
                res.push_back({cur, nxt});
            }
        } else {
            low_link[cur] = min(low_link[cur], index[nxt]);
        }
    }
}

void tarjan(vector<vector<int>>& graph, int n) {
    vector<pair<int, int>> res;
    vector<int> index(n + 1, -1);
    vector<int> low_link(n + 1, -1);
    int time = 0;
    for (int i = 1; i <= n; i++) {
        if (index[i] == -1) {
            dfs(graph, index, low_link, time, i, 0, res);
        }
    }
    sort(res.begin(), res.end());
    for (auto& re: res) {
        cout << re.first << " " << re.second << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    tarjan(graph, n);
}