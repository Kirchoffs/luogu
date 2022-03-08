#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(vector<vector<int>>& graph, vector<int>& index, vector<int>& lowlink, int cur, 
         stack<int>& stk, vector<bool>& on_stk, int& time, vector<int>& super_nodes, int& super_node_id) {
    index[cur] = lowlink[cur] = time++;
    stk.push(cur);
    on_stk[cur] = true;

    for (int nxt: graph[cur]) {
        if (index[nxt] == -1) {
            dfs(graph, index, lowlink, nxt, stk, on_stk, time, super_nodes, super_node_id);
            lowlink[cur] = min(lowlink[cur], lowlink[nxt]);
        } else if (on_stk[nxt]) {
            lowlink[cur] = min(lowlink[cur], index[nxt]);   
        }
    }

    if (index[cur] == lowlink[cur]) {
        while (stk.top() != cur) {
            on_stk[stk.top()] = false;
            super_nodes[stk.top()] = super_node_id;
            stk.pop();
        }
        on_stk[cur] = false;
        super_nodes[cur] = super_node_id;
        stk.pop();
        super_node_id++;
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
    vector<int> super_nodes(n + 1, -1);

    int time = 0;
    int super_node_id = 0;
    
    for (int i = 1; i <= n; i++) {
        if (index[i] == -1) {
            dfs(graph, index, lowlink, i, stk, on_stk, time, super_nodes, super_node_id);
        }
    }

    vector<int> out_degree(super_node_id, 0);
    for (int cur = 1; cur <= n; cur++) {
        for (int nxt: graph[cur]) {
            int super_node_cur = super_nodes[cur];
            int super_node_nxt = super_nodes[nxt];
            if (super_node_cur != super_node_nxt) {
                out_degree[super_node_cur]++;
            }
        }
    }

    int super_node_zero_out_degree = -1;
    for (int i = 0; i < super_node_id; i++) {
        if (out_degree[i] == 0) {
            if (super_node_zero_out_degree != -1) {
                cout << 0 << endl;
                return 0;
            } else {
                super_node_zero_out_degree = i;
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (super_nodes[i] == super_node_zero_out_degree) {
            cnt++;
        }
    }
    cout << cnt << endl;
}