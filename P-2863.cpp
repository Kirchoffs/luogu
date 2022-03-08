#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;

void dfs(vector<vector<int>>& graph, vector<int>& index, vector<int>& lowlink, int cur, 
         stack<int>& stk, vector<bool>& on_stk, int& time, int& res) {
    index[cur] = lowlink[cur] = time++;
    stk.push(cur);
    on_stk[cur] = true;

    for (int nxt: graph[cur]) {
        if (index[nxt] == -1) {
            dfs(graph, index, lowlink, nxt, stk, on_stk, time, res);
            lowlink[cur] = min(lowlink[cur], lowlink[nxt]);
        } else if (on_stk[nxt]) {
            lowlink[cur] = min(lowlink[cur], index[nxt]);   
        }
    }

    if (index[cur] == lowlink[cur]) {
        int cnt = 1;
        while (stk.top() != cur) {
            cnt++;
            on_stk[stk.top()] = false;
            stk.pop();
        }
        on_stk[cur] = false;
        stk.pop();
        
        if (cnt > 1) {
            res++;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    vector<int> index(n + 1, -1);
    vector<int> lowlink(n + 1, -1);
    stack<int> stk;
    vector<bool> on_stk(n + 1);

    int time = 0;
    int res = 0;
    
    for (int i = 1; i <= n; i++) {
        if (index[i] == -1) {
            dfs(graph, index, lowlink, i, stk, on_stk, time, res);
        }
    }

    cout << res << endl;
}