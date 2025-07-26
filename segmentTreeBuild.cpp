#include <bits/stdc++.h>
using namespace std;

// Array to store input values
int a[100005];
// Segment tree array (4*n size is enough for n elements)
int seg[4 * 100005];

/**
 * Build the segment tree.
 * @param ind  Current index in segment tree array
 * @param low  Start index of the current segment
 * @param high End index of the current segment
 */
void build(int ind, int low, int high) {
    if (low == high) {
        seg[ind] = a[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid);         // Build left child
    build(2 * ind + 2, mid + 1, high);    // Build right child
    seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]); // Merge
}

/**
 * Query the maximum value in range [l, r].
 * @param ind  Current index in segment tree array
 * @param low  Start index of the current segment
 * @param high End index of the current segment
 * @param l    Query left bound
 * @param r    Query right bound
 * @return     Maximum value in [l, r]
 */
int query(int ind, int low, int high, int l, int r) {
    // Complete overlap
    if (low >= l && high <= r) {
        return seg[ind];
    }
    // No overlap
    if (high < l || low > r) return INT_MIN;
    // Partial overlap
    int mid = (low + high) / 2;
    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);
    return max(left, right);
}

/**
 * Update the value at position pos to val.
 * @param ind  Current index in segment tree array
 * @param low  Start index of the current segment
 * @param high End index of the current segment
 * @param pos  Position to update
 * @param val  New value
 */
void update(int ind, int low, int high, int pos, int val) {
    if (low == high) {
        seg[ind] = val;
        a[pos] = val;
        return;
    }
    int mid = (low + high) / 2;
    if (pos <= mid)
        update(2 * ind + 1, low, mid, pos, val);
    else
        update(2 * ind + 2, mid + 1, high, pos, val);
    seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(0, 0, n - 1);

    int q;
    cin >> q;
    /*
     * For each query:
     * Type 1 l r : Print max in range [l, r] (0-based indexing)
     * Type 2 pos val : Update a[pos] = val
     */
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n - 1, l, r) << '\n';
        } else if (type == 2) {
            int pos, val;
            cin >> pos >> val;
            update(0, 0, n - 1, pos, val);
        }
    }
    return 0;
}