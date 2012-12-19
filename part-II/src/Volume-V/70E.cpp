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
#define cvar(x) cerr << "[" << #x << ": " << x << "]"
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
  void adde (int s, edge e){adj[s].push_back (e);}
  int deg (int v) {return adj[v].size (); }
  vector<edge>& operator [](int t) {return adj[t];}
};

const int maxn = 182;

Graph<int> G;
PII f[maxn][maxn][maxn];
PII g[maxn][maxn][maxn];
int build, cost[maxn], ans[maxn];
VI center;
int n, tot;

void dp (int v, int F)
{
  foreach (e, G[v])
    if (*e != F)
      dp (*e, v);

  for (int j = 1; j <= n; ++j) // informed by outside
    {
      for (int k = n; k >= 1; --k) // informed by inside
        {
          // if (k == n && j == n) {continue;
          int D = min (j, k), val = cost[D], d = min (D + 1, n); PII chs = MKP (k == n ? 0 : oo, 0);
          foreach (e, G[v])
            if (*e != F)
              {
                val = min (oo, val + g[*e][d][k - 1].Px);
                chkmin (chs, MKP (f[*e][min (j + 1, n)][k - 1].Px - g[*e][d][k - 1].Px, *e));
              }
          f[v][j][k] = MKP (min (oo, val + chs.Px), chs.Py);
        }
      f[v][j][0].Px += build;
      foreach (e, G[v])
        if (*e != F)
          f[v][j][0].Px += g[*e][1][0].Px;

      g[v][j][n] = MKP (f[v][j][n].Px, n);
      for (int k = n - 1; k >= 0; --k)
        g[v][j][k] = min (g[v][j][k + 1], MKP (f[v][j][k].Px, k));
    }
}

void dfs (int v, int F, int j, int k, bool s)
{
  if (s) k = g[v][j][k].Py;
  if (v == 1) tot = f[v][j][k].Px;
  if (!k)
    {
      center.push_back (v), ans[v] = v;
      foreach (e, G[v])
        if (*e != F)
          dfs (*e, v, 1, 0, 1);
      return ;
    }
  // int D = min (j + 1, k - 1), K = k - (k != n);
  foreach (e, G[v])
    if (*e != F && (*e != f[v][j][k].Py || k == n))
      dfs (*e, v, min (min (j, k) + 1, n), k - 1, 1);
    else if (*e != F)
      dfs (*e, v, min (j + 1, n), k - 1, 0);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("70E.in" , "r", stdin);
  freopen ("70E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n >> build;
  for (int i = 1; i < n; ++i)
    cin >> cost[i];
  cost[n] = oo;
  G.resize (n);
  for (int i = 1, s, t; i < n; ++i)
    cin >> s >> t, G.adde (s, t), G.adde (t, s);

  dp (1, 0);
  dfs (1, 0, n, 0, 1);

  cout << tot << endl;
  queue<int> Q;
  foreach (x, center)
    Q.push (*x);
  for (; !Q.empty (); Q.pop ())
    {
      int v = Q.front ();
      foreach (e, G[v])
        if (!ans[*e])
          ans[*e] = ans[v], Q.push (*e);
    }

  for (int i = 1; i <= n; ++i)
    cout << ans[i] << " ";
  return 0; 
}
