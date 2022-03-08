#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

ll merge(vector<int>& nums, vector<int>& helper, int l, int r) {
    int m = l + (r - l) / 2;
    for (int i = l; i <= r; i++) {
        helper[i] = nums[i];
    }

    ll res = 0;
    int idx = l;
    int l_idx = l, r_idx = m + 1;
    while (l_idx <= m) {
        if (r_idx > r || helper[l_idx] <= helper[r_idx]) {
            nums[idx++] = helper[l_idx++];
            res += r_idx - m - 1;
        } else {
            nums[idx++] = helper[r_idx++];
        }
    }

    return res;
}

ll merge_sort(vector<int>& nums, vector<int>& helper, int l, int r) {
    if (l >= r) {
        return 0;
    }

    int m = l + (r - l) / 2;
    ll res = 0;
    res += merge_sort(nums, helper, l, m);
    res += merge_sort(nums, helper, m + 1, r);

    res += merge(nums, helper, l, r);

    return res;
}

ll count_reverse(vector<int>& nums) {
    vector<int> helper(nums.size());
    return merge_sort(nums, helper, 0, nums.size() - 1);
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << count_reverse(nums) << endl;
}