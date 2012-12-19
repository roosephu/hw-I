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
#ifdef WIN32
#define fmt64 "%I64d"
#else
#define fmt64 "%lld"
#endif
#define foreach(i, x) for (__typeof__((x).begin ()) i = (x).begin (); i != (x).end (); ++i)
#define MKP make_pair
#define Px first
#define Py second
#define PB push_back
#define sz_m(x) (int)((x).size ())
#define iter(x) (x).begin (), (x).end ()

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef long double real;
typedef vector<int> VI;
typedef map<int, int> MII;
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

const int mod5 = 1220703125, mod2 = 8192, mapsize = 1953125;
const int64 modperiod = (int64)mod5 * mod2 * 3 / 8;

vector<int64> pos2, pos5;
map<int64, uint> f;

int64 fmm (int64 b, int64 e, int64 m)
{
  int64 t = 0;
  for (; e; e >>= 1, b = (b << 1) % m)
    e & 1 ? (t = (t + b) % m), 0 : 0;
  return t;
}

int64 solve (int64 x, int64 y)      // mod 5^13 * 4 = x, mod 2^12 * 3 = y
{
  if (x % 4 != y % 4) return (int64)1e18;
  int k = x % 4; x /= 4, y /= 4;
  int64 w = (fmm (81787109376ll, x, modperiod) + fmm (3668212890625ll, y, modperiod)) % (modperiod);
  return w * 4 + k;
}

uint fib (int64 t)
{
  if (f.count (t)) return f[t];
  int64 a = fib (t >> 1), b = fib ((t >> 1) + 1);
  if (t & 1)
    f[t] = (sqr (a) + sqr (b)) % mod5;
  else
    f[t] = a * (2 * b + mod5 - a) % mod5;
  return f[t];
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("193E.in" , "r", stdin);
  freopen ("193E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  
  int64 T, period5 = 4ll * mod5;
  cin >> T;

  f[0] = 0, f[1] = 1, f[2] = 1;
  // cerr << fib (7) << endl;
  for (uint i = 0, x = 0, y = 1, z, w = T % mapsize; ; ++i)
    {
      if (x == w)
        for (int64 z = 0; z < period5 / mapsize; ++z)
          if (fib (z * mapsize + i) == T % mod5)
            pos5.push_back (z * mapsize + i);
      z = (x + y) % mapsize;
      x = y, y = z;
      if (x == 0 && y == 1) break;
    }
  for (int i = 0, x = 0, y = 1, z, w = T % mod2; ; ++i)
    {
      if (x == w) pos2.push_back (i);
      z = (x + y) % mod2;
      x = y, y = z;
      if (x == 0 && y == 1) break;
    }

  int64 ans = 1e18;
  for (auto &x : pos5)
    for (auto &y : pos2)
      ans = min (ans, solve (x, y));

  if (ans == 1e18) cout << -1 << endl;
  else cout << ans << endl;
  return 0; 
}

