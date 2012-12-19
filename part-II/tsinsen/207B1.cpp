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
typedef unordered_map<int, int> UMII;
typedef unordered_set<int> USI;

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

const int maxn = 524288, maxlevel = 20;

struct seg_tree
{
  int f[maxn << 1];

  int query (int L, int R)
  {
    int ret = oo;
    for (L += maxn - 1, R += maxn + 1; L ^ R ^ 1; L >>= 1, R >>= 1)
      {
        if (~L & 1) chkmin (ret, f[L ^ 1]);
        if ( R & 1) chkmin (ret, f[R ^ 1]);
      }
    return ret;
  }

  void build (seg_tree &g)
  {
    for (int i = 1; i < maxn; ++i)
      f[maxn + i] = g.query (g.f[maxn + i], i);
    for (int i = maxn - 1; i; --i)
      f[i] = min (f[i * 2], f[i * 2 + 1]);
  }
};

seg_tree f[maxlevel];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("207B1.in" , "r", stdin);
  freopen ("207B1.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, level = 0;
  
  cin >> n;
  for (int i = 1, x; i <= n; ++i)
    cin >> x, f[0].f[maxn + i] = max (i - x, 1), f[0].f[maxn + i + n] = max (i - x + n, 1);
  for (int i = maxn - 1; i; --i)
    f[0].f[i] = min (f[0].f[i * 2], f[0].f[i * 2 + 1]);
  for (int i = 1; 1 << i <= n * 2; ++i)
    f[i].build (f[i - 1]), level = i;

  int64 ans = 0;
  for (int i = 1; i <= n; ++i)
    {
      int L = i + n - 1, ret = oo, now = 0;
      for (int b = level, t; b >= 0; --b)
        if ((t = f[b].query (L, i + n - 1)) <= i)
          ret = now | 1 << b;
        else
          L = t, now += 1 << b;
      ans += ret;
    }
  cout << ans << endl;
  return 0; 
}
