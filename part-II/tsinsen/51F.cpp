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

const int maxn = 2200;

typedef int arr32[maxn];

arr32 dfn, low, rep, deg, ufs;
int tot, tms, dep, x;
Graph<int> G, g;
stack<int> stk;

void tarjan (int v, int f)
{
  stk.push (v), dfn[v] = low[v] = ++tms;
  foreach (e, G[v])
    if (!dfn[*e])
      tarjan (*e, v), chkmin (low[v], low[*e]);
    else if (*e != f)
      chkmin (low[v], dfn[*e]);
  if (low[v] == dfn[v])
    for (int u = 0; u != v; stk.pop ())
      rep[u = stk.top ()] = v;
}

void dfs (int v, int f, int d)
{
  if (d > dep) dep = d, x = v;
  dfn[v] = 1;
  foreach (e, g[v])
    if (*e != f)
      dfs (*e, v, d + 1);
}

int find (int t) {return ufs[t] != t ? ufs[t] = find(ufs[t]) : t;}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("51F.in" , "r", stdin);
  freopen ("51F.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, ans = -1;
  
  cin >> n >> m; G.resize (n);
  for (int i = 1, s, t; i <= m; ++i)
    cin >> s >> t, G.adde (s, t), G.adde (t, s);
  for (int i = 1; i <= n; ++i)
    if (!dfn[i])
      tarjan (i, 0);

  g.resize (n);
  for (int i = 1; i <= n; ++i)
    foreach (e, G[i])
      if (rep[i] != rep[*e])
        ++deg[rep[i]];
  for (int i = 1; i <= n; ++i)
    ufs[i] = i;
  
  for (int i = 1; i <= n; ++i)
    foreach (e, G[i])
      if (rep[i] != rep[*e])
        {
          int x = rep[i], y = rep[*e];
          if (deg[x] != 1 && deg[y] != 1)
            g.adde (x, y);
          if (find (x) != find (y))
            ufs[find (x)] = find (y), --ans;
        }
  for (int i = 1; i <= n; ++i)
    if (rep[i] == i && deg[i] != 1)
      ++ans;

  memset (dfn, 0, sizeof (dfn));
  ans += n;
  for (int i = 1; i <= n; ++i)
    if (rep[i] == i && deg[i] != 1 && dfn[i] != 1)
      {
        dep = 0, dfs (i, 0, 1);
        dep = 0, dfs (x, 0, 1);
        ans -= dep;
        // cerr << ans << endl;
      }

  cout << ans << endl;
  return 0; 
}
