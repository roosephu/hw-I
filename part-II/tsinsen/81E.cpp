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
  void add (int s, edge e) {adj[s].push_back (e);}
  void del (int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
  int deg (int v) {return adj[v].size (); }
  vector<edge>& operator [](int t) {return adj[t];}
};

const int maxn = 110000;

typedef pair<PII, int> PIII;
typedef int arr32[maxn];

Graph<int> G;
PIII f[maxn], g[maxn], ans;
arr32 sex, dfn, next, pack, low, loop, fth;
int tms, cut;

PIII operator + (PIII a, PIII b)
{
  return MKP (MKP (a.Px.Px + b.Px.Px, a.Px.Py + b.Px.Py), 0);
}

void dfs (int v, int F)
{
  PIII w = MKP (MKP (-oo, -oo), 0);

  f[v] = g[v] = f[0];
  if (!fth[v]) fth[v] = F;
  low[v] = dfn[v] = dfn[F] + 1;
  // if (dfn[v] > 300000) exit (0);
  foreach (e, G[v])
    if (*e != F && (!dfn[*e] || fth[*e] == v))
      {
        dfs (*e, v);
        g[v] = g[v] + f[*e];
        low[v] = min (low[v], low[*e]);
        chkmax (w, MKP (MKP (g[*e].Px.Px - f[*e].Px.Px + 1, g[*e].Px.Py - f[*e].Px.Py + (sex[v] != sex[*e])), *e));
        
        if (low[*e] == dfn[v])
          {
            int u = cut; PIII z = f[*e]; evar (v); loop[v] = u;
            // if (fth[u] == v) exit (0);
            G.del (fth[u], u);
            dfs (*e, v);
            G.add (fth[u], u);
            chkmax (w, MKP (MKP (g[u].Px.Px + f[*e].Px.Px - z.Px.Px + 1, g[u].Px.Py + f[*e].Px.Py - z.Px.Py + (sex[v] != sex[u])), v));
          }
      }
    else if (*e != F && dfn[*e] < dfn[v])
      cut = v, evar (cut), low[v] = dfn[*e];
  
  f[v] = g[v] + w, f[v].Py = w.Py, g[v].Py = 0;
  chkmax (f[v], g[v]);
  if (!F) ans = ans + f[v];
}

void out (int v, int F, bool b)
{
  // cvar (v), cvar (F), evar (b);
  if (loop[F]) dfs (v, F);
  PIII &r = b ? f[v] : g[v];
  if (r.Py == 0) // oops, cann't match it
    {
      foreach (e, G[v])
        if (fth[*e] == v)
          out (*e, v, 1);        // maximize it
    }
  else if (r.Py == v)           // match v <-> next[v]
    {
      int u = loop[v];
      pack[v] = u, pack[u] = v;
      G.del (fth[u], u);       // delete next[u] -> u
      G.del (u, fth[u]);       // delete u -> next[u]
      out (u, v, 0);
      foreach (e, G[v])
        if (fth[*e] == v)
          out (*e, v, 1);
    }
  else                          // match v <-> one of v's child (r.Py)
    {
      pack[v] = r.Py, pack[r.Py] = v;
      foreach (e, G[v])
        if (fth[*e] == v)
          out (*e, v, *e != r.Py);
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("81E.in" , "r", stdin);
  freopen ("81E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> n, G.resize (n);
  for (int i = 1; i <= n; ++i)
    cin >> next[i] >> sex[i], G.add (next[i], i), G.add (i, next[i]);
  for (int i = 1; i <= n; ++i)
    sort (iter (G[i])), G[i].resize (unique (iter (G[i])) - G[i].begin ());

  VI vec;
  for (int i = 1; i <= n; ++i)
    if (!dfn[i])
      dfs (i, 0), vec.push_back (i);
  // if (next[1] == 41895) return 0;
  foreach (it, vec)
    out (*it, 0, 1);
  // for (int i = 1; i <= n; ++i)
  //   cerr << i << ": "
  //        << "<" << f[i].Px.Px << " " << f[i].Px.Py << " " << f[i].Py << ">"
  //        << "<" << g[i].Px.Px << " " << g[i].Px.Py << " " << g[i].Py << ">" << endl;

  cout << ans.Px.Px << " " << ans.Px.Py << endl;
  for (int i = 1; i <= n; ++i)
    if (pack[i] < i && pack[i])
      cout << pack[i] << " " << i << endl;
  return 0; 
}
