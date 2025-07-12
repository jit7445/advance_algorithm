#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
    ll value;
    node() {
        value =0;
    }
};

const int N = 2e5 + 1;
node seg[4 * N];
ll arr[N];

node merge(node a, node b) {
    node nd;
    nd.value = max(a.value,b.value);
    return nd;
}

void build(int ind, int s, int e) {
    if (s == e) {
        seg[ind].value = arr[s];
        return;
    }
    int mid = (s + e) / 2;
    build(2 * ind, s, mid);
    build(2 * ind + 1, mid + 1, e);
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}

node query(int ind, int s, int e, int l, int r) {
    if (r < s || l > e) return node(); 
    if (l <= s && e <= r) return seg[ind]; 
    int mid = (s + e) / 2;
    node left = query(2 * ind, s, mid, l, r);
    node right = query(2 * ind + 1, mid + 1, e, l, r);
    return merge(left, right);
}
void  updatepos(int ind, int s, int e, int pos, int val) {
   if (s == e) {
        seg[ind].value =val;
        return;
    }
    
    int mid = (s + e) / 2;
    if(pos<=mid){
    updatepos(2 * ind, s, mid,pos,val);
    }
    else{
    updatepos(2 * ind + 1, mid + 1, e,pos,val);
    }
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}
int room(int ind,int s,int e,int val){
    if(s==e){
        if(arr[s]>=val){
            seg[ind].value-=val;
            arr[s]-=val;
            return s;
        }
        else{
            return 0;
        }
    }
    int mid=(s+e)/2;
    int left=0,right=0;
    if(seg[2*ind].value>=val){
        left=room(2*ind,s,mid,val);
    }
    else if(seg[2*ind+1].value>=val){
        right=room(2*ind+1,mid+1,e,val);
    }
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
    return max(left,right);
}
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <=n; i++) {
        cin >> arr[i];
    }
    build(1, 1, n); 
    while (q--) {
        int val;
        cin>>val;
        cout<<room(1,1,n,val)<<" ";
        
    }
    cout<<endl;
}
// 3 5 0 1 1

int main() {
    solve();
}
