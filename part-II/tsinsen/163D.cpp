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

const int maxn = 30;

pair<int64, pair<int64, int64>> ans;
map<int64, pair<int64, pair<int64, int64>>> f;
map<int64, int64> g;
int n;
int64 a[maxn], p[maxn], V, A, B, wB;
int lmtA, lmtB;
int cnt = 0, cnt2;

void dfs2 (int B, int d)
{
  // if (d == 1) cerr << V << " " << A << " " << B << endl;
  if (B > wB) wB = B;
  if (d > n) return ;
  int bak = a[d];
  for (; a[d] >= 0; --a[d])
    {
      dfs2 (B, d + 1);
      int64 x = B * p[d];
      if (lmtB < x) break;
      B = x;
    }
  a[d] = bak;
}

void dfs2_pre ()
{
  if (!g.count (V))
    wB = 0, dfs2 (1, 1), g[V] = wB;
  wB = g[V];
  
  int64 val = V + (wB + V / wB) * A;
  if (val < ans.Px) ans = MKP (val, MKP (A, wB));
}

void dfs (int A, int d)
{
  // cerr << "dfs: " << A << " " << d << " " << V / A + A * 2 * (int64)sqrt (V / A) << " " << ans.Px << endl;
  // if (A == 768) cerr << d << endl;
  if (d > n)
    {
      // evar (A), ++cnt2;
      V /= A;
      lmtB = sqrt (V);
      if (V + A * (lmtB + V / lmtB) > ans.Px) return (void)(V *= A);
      return (void)(::A = A, dfs2_pre (), V *= A);
    }
  int bak = a[d];
  for (; a[d] >= 0; --a[d])
    {
      dfs (A, d + 1);
      int64 x = A * p[d];
      if (x > lmtA) break;
      A = x;
    }
  a[d] = bak;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("163D.in" , "r", stdin);
  freopen ("163D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int T;
  
  for (cin >> T; T--; )
    {
      cin >> n;
      V = 1;
      for (int i = 1; i <= n; ++i)
        {
          cin >> p[i] >> a[i];
          for (int j = 1; j <= a[i]; ++j)
            V *= p[i];
        }

      // evar (V);
      lmtA = cbrt (V); // , evar (lmtA);
      ans = MKP (4e18, MKP (0, 0));
      if (!f.count (V))
        dfs (1, 1), f[V] = ans;
      else
        ans = f[V];
      // if (ans.Px * 2 == 3702784)
      //   for (int i = 1; i <= n; ++i)
      //     cerr << a[i] << " " << p[i] << endl;
      
      cout << ans.Px * 2 << " " << ans.Py.Px << " " << ans.Py.Py << " " << V / ans.Py.Px / ans.Py.Py << endl;
    }

  // cvar (cnt), cvar (cnt2);
  // cerr << 1.0 * clock () / CLOCKS_PER_SEC << endl;
  return 0; 
}
