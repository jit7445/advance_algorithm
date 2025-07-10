#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

void partialsumAp(){
    ll n, q;
    cin >> n >> q;
    vector<ll>a(n,0);
    vector<ll>b(n);
    vector<ll>c(n);

    while(q--) {
        ll A,D,l, r;
        cin>>A>>D>>l>>r;
        l--; r--;   

        b[l]=(b[l]+(A - D * l % mod + mod)%mod)%mod;
        if(r+1<n){
            b[r+1]=(b[r+1] - (A - D * l % mod + mod)%mod + mod)%mod;
        }
        c[l]=(c[l]+D)%mod;
        if(r+1<n){
            c[r+1]=(c[r+1]-D+mod)%mod;
        }
    }

    for(int i=1;i<n;i++){
        b[i]=(b[i]+b[i-1])%mod;
        c[i]=(c[i]+c[i-1])%mod;
    }
    for(ll i=0;i<n;i++){
        a[i]=(b[i] + c[i]*i%mod)%mod;
    }

    for(auto it:a){
        cout<<it<<" ";
    }
    cout<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    partialsumAp();
    return 0;
}
