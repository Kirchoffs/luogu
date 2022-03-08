#include <vector>
#include <iostream>
using namespace std;

int main() {
    string target = "yizhong";
    vector<pair<int, int>> dirs = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    int n;
    cin >> n;
    
    vector<string> matrix(n);
    vector<vector<bool>> flag(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        cin >> matrix[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == target[0]) {
                for (auto& dir: dirs) { 
                    int x = i, y = j;
                    bool is_matched = true;
                    for (int k = 0; k < target.length(); k++) {
                        if (x < 0 || x >= n || y < 0 || y >= n || matrix[x][y] != target[k]) {
                            is_matched = false;
                            break;
                        }
                        x += dir.first;
                        y += dir.second;
                    }

                    if (is_matched) {
                        x = i, y = j;
                        for (int k = 0; k < target.length(); k++) {
                            flag[x][y] = true;
                            x += dir.first;
                            y += dir.second;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (flag[i][j]) {
                cout << matrix[i][j];
            } else {
                cout << "*";
            }
        }
        cout << endl;
    }
}