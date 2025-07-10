#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
void prefisumAp(){
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for(ll i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = (a[i]%mod + mod) % mod; 
    }

    vector<ll> b(n);
    for(ll i = 0; i < n; i++) {
        b[i] = a[i] * (i + 1) % mod;
    }

    vector<ll> pref1(n), pref2(n);
    pref1[0] = a[0];
    pref2[0] = b[0];
    for(ll i = 1; i < n; i++) {
        pref1[i] = (pref1[i - 1] + a[i]) % mod;
        pref2[i] = (pref2[i - 1] + b[i]) % mod;
    }

    while(q--) {
        ll l, r;
        cin >> l >> r;
        l--; r--;
        ll s1 = pref1[r];
        if(l > 0) s1 = (s1 - pref1[l - 1] + mod) % mod;

        ll s2 = pref2[r];
        if(l > 0) s2 = (s2 - pref2[l - 1] + mod) % mod;

        ll ans = (s2 - l * s1 % mod + mod) % mod;
        cout << ans << endl;
    }
}
ll modpow(ll a, ll b) {
    ll res = 1;
    a %= mod;
    while(b > 0) {
        if(b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void prefsumGP(){
    ll n, q, k;
    cin >> n >> q >> k;
    vector<ll> a(n);
    for(ll i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = (a[i]%mod + mod) % mod;
    }
    vector<ll> powk(n + 2);
    powk[0] = 1;
    for(ll i = 1; i <= n+1; i++) {
        powk[i] = powk[i-1] * k % mod;
    }
    vector<ll> b(n);
    for(ll i = 0; i < n; i++) {
        b[i] = a[i] * powk[i+1] % mod;
    }
    vector<ll> pref(n);
    pref[0] = b[0];
    for(ll i = 1; i < n; i++) {
        pref[i] = (pref[i-1] + b[i]) % mod;
    }
    while(q--) {
        ll l, r;
        cin >> l >> r;
        l--; r--;

        ll s2 = pref[r];
        if(l > 0) s2 = (s2 - pref[l-1] + mod) % mod;

        ll kinv = modpow(k, mod - 1 - l);
        ll ans = s2 * kinv % mod;
        cout << ans << '\n';
    }
}

// 644011223
// 645979052
// 534876628
// 999999984
// 44
// 725883751
// 503173837
// 859246404
// 845338365
// 605774687
int main() {
     ios::sync_with_stdio(false);
    cin.tie(NULL);
    prefisumAp();
    // prefsumGP();
    return 0;
}
