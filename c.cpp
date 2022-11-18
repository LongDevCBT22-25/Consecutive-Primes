#include <bits/stdc++.h>
#define FastIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define uint unsigned long long
#define pb push_back
using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;
mt19937 rnd((uint)chrono::system_clock::now().time_since_epoch().count());
const int maxN = 4e6;
int p[maxN];
vector<int> primes;
map<uint, int> M;
void input(){
    FastIO;
    freopen("c.inp","r", stdin);
    freopen("c.out","w", stdout);
}
u64 binpower(u64 base, u64 e, u64 mod) {
    u64 ans = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            ans = (u128)ans * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return ans;
}
bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};
bool MillerRabin(u64 n) { 
    if (n < 2)
        return false;
    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}) {
        if (n % a == 0) return false;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}) {
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
void gen() {
    for (int i = 2; i < maxN; i++) {
        if (!p[i]) {
            for (int j = i + i; j < maxN; j += i) p[j] = i;
            primes.pb(i);
        }
    }
    uint limits = 1000000000;
    limits *= limits * 10;
    for (int i = 0; i < (int)primes.size(); i++) {
        uint tich = 1;
        for (int j = i; j < (int)primes.size(); j++) {
            if (tich <= limits / primes[j]) {
                tich *= primes[j];
                M[tich] = 1;
            } else {
                break;
            }
        }
    }
}
bool special_case(uint n) {
    if (MillerRabin(n)) return true;
    if (n <= 1e12) return false;
    uint x = sqrt(n);
    while (x * x > n) x--;
    while ((x + 1) * (x + 1) <= n) x++;
    uint larger = 0;
    uint weaker = 0;
    for (int i = 1;; i++) {
        uint y = x + i;
        if (MillerRabin(y)) {
            larger = y;
            break;
        }
    }
    for (int i = 0;; i--) {
        uint y = x + i;
        if (MillerRabin(y)) {
            weaker = y;
            break;
        }
    }
    return n == larger * weaker;
}
void solve() {
    uint n;
    cin >> n;
    cout << ((M[n] || special_case(n)) ? "NICE\n" : "UGLY\n");
}
int32_t main() {
    input();
    gen();
    int t = 1;
    cin >> t;
    while (t--) solve();
}