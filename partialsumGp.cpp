#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

void partialsumGp(){
    ll n, q,r;
    cin >> n >> q>>r;
    vector<ll>a(n,0);
    vector<ll>b(n);
    vector<ll>c(n);
    vector<ll>powr(n+1);
    powr[0]=1;
    for(ll i=1;i<=n;i++){
        powr[i]=powr[i-1]*r%mod;
    }
    while(q--) {
        ll A,l, r;
        cin>>A>>l>>r;
        l--; r--;   

        b[l]=(b[l]+(A+ mod)%mod)%mod;
        if(r+1<n){
            b[r+1]=(b[r+1] - (A*powr[r-l+1] % mod + mod)%mod + mod)%mod;
        }
        
    }

    for(int i=1;i<n;i++){
        b[i]+=(b[i-1]*r%mod)%mod;
       
    }
    

    for(auto it:b){
        cout<<it%mod<<" ";
    }
    cout<<endl;
}
// 3 14 26 52 81 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    partialsumGp();
    return 0;
}
