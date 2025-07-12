#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
    ll value;
    ll lazy_set; 
    ll lazy_inc;
    node() {
        value = 0;
        lazy_set = 0;
        lazy_inc = 0;
    }
};

const int N = 2e5 + 1;
node seg[4 * N];
ll arr[N];

node merge(node a, node b) {
    node nd;
    nd.value = a.value + b.value;
    return nd;
}

void build(int ind, int s, int e) {
    if (s == e) {
        seg[ind].value = arr[s];
        seg[ind].lazy_set = 0;
        seg[ind].lazy_inc = 0;
        return;
    }
    int mid = (s + e) / 2;
    build(2 * ind, s, mid);
    build(2 * ind + 1, mid + 1, e);
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}

void push(int ind, int l, int r) {
    if (seg[ind].lazy_set != 0) {
        // Apply the set
        seg[ind].value = (r - l + 1) * seg[ind].lazy_set;
        if (l != r) {
            // Propagate set to children
            seg[2 * ind].lazy_set = seg[ind].lazy_set;
            seg[2 * ind + 1].lazy_set = seg[ind].lazy_set;
            // Reset children's increment because set overwrites
            seg[2 * ind].lazy_inc = 0;
            seg[2 * ind + 1].lazy_inc = 0;
        }
        seg[ind].lazy_set = 0;
    }
    if (seg[ind].lazy_inc != 0) {
        // Apply increment
        seg[ind].value += (r - l + 1) * seg[ind].lazy_inc;
        if (l != r) {
            // Propagate increment to children
            seg[2 * ind].lazy_inc += seg[ind].lazy_inc;
            seg[2 * ind + 1].lazy_inc += seg[ind].lazy_inc;
        }
        seg[ind].lazy_inc = 0;
    }
}

void updaterange_set(int ind, int s, int e, int l, int r, ll val) {
    push(ind, s, e);
    if (r < s || l > e) return;
    if (l <= s && e <= r) {
        seg[ind].lazy_set = val;
        seg[ind].lazy_inc = 0; 
        push(ind, s, e);
        return;
    }
    int mid = (s + e) / 2;
    updaterange_set(2 * ind, s, mid, l, r, val);
    updaterange_set(2 * ind + 1, mid + 1, e, l, r, val);
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}

void updaterange_inc(int ind, int s, int e, int l, int r, ll val) {
    push(ind, s, e);
    if (r < s || l > e) return;
    if (l <= s && e <= r) {
        seg[ind].lazy_inc += val;
        push(ind, s, e);
        return;
    }
    int mid = (s + e) / 2;
    updaterange_inc(2 * ind, s, mid, l, r, val);
    updaterange_inc(2 * ind + 1, mid + 1, e, l, r, val);
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}

node kpos(int ind, int s, int e, int pos) {
    push(ind, s, e);
    if (s == e) {
        return seg[ind];
    }
    int mid = (s + e) / 2;
    if (pos <= mid) {
        return kpos(2 * ind, s, mid, pos);
    } else {
        return kpos(2 * ind + 1, mid + 1, e, pos);
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build(1, 1, n);

    while (q--) {
        int typ;
        cin >> typ;
        if (typ == 1) {
            int a, b, u;
            cin >> a >> b >> u;
            updaterange_inc(1, 1, n, a, b, u);
        } else if (typ == 2) {
            int a, b, u;
            cin >> a >> b >> u;
            updaterange_set(1, 1, n, a, b, u);
        } else if (typ == 3) {
            int k;
            cin >> k;
            cout << kpos(1, 1, n, k).value << '\n';
        }
    }
}

int main() {
    solve();
}