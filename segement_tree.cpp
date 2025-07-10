#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
typedef long long ll;
struct node{
    ll sum;
    node(){
        sum=0;
    }
};
vector<int>tree[N];
int in[N], out[N], flat[N], timer = 0;
node seg[4 * N];
int n, q;
node merge(node a,node b){
    node nd;
    nd.sum=a.sum+b.sum;
    return nd;
}
void dfs(int u, int p, vector<int>& val) {
    in[u] = ++timer;
    flat[timer] = val[u]; 
    for (int v : tree[u]) {
        if (v != p) dfs(v, u, val);
    }
    out[u] = timer;
}

void build(int id, int l, int r) {
    if (l == r) {
        seg[id].sum= flat[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    seg[id] = merge(seg[2 * id],seg[2 * id + 1]);
}
void update(int id, int l, int r, int pos, ll val) {
    if (l == r) {
        seg[id].sum= val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(2 * id, l, mid, pos, val);
    else
        update(2 * id + 1, mid + 1, r, pos, val);
    seg[id] = merge(seg[2 * id] , seg[2 * id + 1]);
}

node query(int id, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return node();
    if (ql <= l && r <= qr) return seg[id];
    int mid = (l + r) / 2;
    return merge(query(2 * id, l, mid, ql, qr) , query(2 * id + 1, mid + 1, r, ql, qr));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    vector<int> val(n + 1);
    for (int i = 1; i <= n; ++i) cin >> val[i];

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0, val);
    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s;
            ll x;
            cin >> s >> x;
            update(1, 1, n, in[s], x);
        } else {
            int s;
            cin >> s;
            cout << query(1, 1, n, in[s], out[s]).sum <<endl;
        }
    }

    return 0;
}
