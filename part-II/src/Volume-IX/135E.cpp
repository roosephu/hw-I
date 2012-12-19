#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

#define oo 0x3F3F3F3F
#ifdef DEBUG
#define cvar(x) cerr << "<" << #x << ": " << x << ">"
#define evar(x) cvar (x) << endl
template<class T> void DISP (const char *s, T x, int n) {cerr << "[" << s << ": "; for (int i = 0; i < n; ++i) cerr << x[i] << " "; cerr << "]" << endl;}
#define disp(x,n) DISP (#x " to " #n, x, n)
#else
#define cvar(...) ({})
#define evar(...) ({})
#define disp(...) ({})
#endif
#define MKP make_pair
#define Px first
#define Py second
#define PB push_back
#define SZ(x) (int)((x).size ())
#define ALL(x) (x).begin (), (x).end ()

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef long double real;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef unordered_map<int, int> UMII;
typedef unordered_set<int> USI;
typedef set<int> SI;
typedef pair<int, int> PII;

int64 fpm (int64 b, int64 e, int64 m) { int64 t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }
template<class T> inline bool chkmin (T &a, T b) {return a > b ? a = b, true : false;}
template<class T> inline bool chkmax (T &a, T b) {return a < b ? a = b, true : false;}
template<class T> inline T sqr (T x) {return x * x;}

template<class edge> struct Graph
{
  vector<vector<edge> > adj;
  Graph (int n) {adj.clear (); adj.resize (n + 5);}
  Graph () {adj.clear (); }
  void resize (int n) {adj.resize (n + 5); }
  void add (int s, edge e){adj[s].push_back (e);}
  void del (int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
  int deg (int v) {return adj[v].size (); }
  vector<edge>& operator [](int t) {return adj[t];}
};

const int maxk = 1100000, mod = 1000000007;

int64 fac[maxk], ifac[maxk];

int64 perm (int n, int m) {return m >= 0 ? fac[n] * ifac[m] % mod : 0; }

int64 calc (int w, int k, int upto)
{
  int64 ret = 0, tot = fpm (k, w, mod), sub = tot, invK = fpm (k, mod - 2, mod);
  for (int a = 1; a <= upto; ++a)
    {
      tot = tot * k % mod;
      if (a <= w) sub = sub * invK % mod;
      ret += tot - perm (k, k - a) * perm (min (k, k - a + w), k - a) % mod * sub % mod;
      cvar (a), cvar (ret), evar (ifac[k - a]);
    }
  // cvar (w), cvar (k), evar (ret);
  return (ret % mod + mod) % mod;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("135E.in" , "r", stdin);
  freopen ("135E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int k, w;
  
  cin >> k >> w;
  fac[0] = 1;
  for (int i = 1; i <= k; ++i)
    fac[i] = fac[i - 1] * i % mod;
  ifac[k] = fpm (fac[k], mod - 2, mod);
  for (int i = k; i; --i)
    ifac[i - 1] = ifac[i] * i % mod;

  // for (int i = 0; i <= k; ++i)
  //   cerr << fac[i] << " " << ifac[i] << " " << fac[i] * ifac[i] % mod << endl;
  
  cout << (calc (w - 1, k, k + 1) + mod - calc (w, k, k)) % mod << endl;
  return 0; 
}
