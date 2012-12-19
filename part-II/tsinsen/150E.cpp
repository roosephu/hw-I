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

const int maxn = 110000;

struct edge {int t, w;};
typedef pair<int, PII> PIII;
typedef int arr32[maxn];

Graph<edge> G;
PII aux, ans;
vector<PII> now, vec;
deque<PIII> Q;
arr32 height, size, del;
int total, L, R, lmt;

void dfs_init (int v, int F)
{
  size[v] = 1, height[v] = 0;
  for (auto &u : G[v])
    if (u.t != F && !del[u.t])
      dfs_init (u.t, v), size[v] += size[u.t], chkmax (height[v], height[u.t]);
  ++height[v];
}

void dfs_find (int v, int F)
{
  int w = total - size[v];
  for (auto &u : G[v])
    if (u.t != F && !del[u.t])
      dfs_find (u.t, v), chkmax (w, size[u.t]);
  aux = min (aux, MKP (w, v));
}

void dfs_sbtr (int v, int F, int d, int val)
{
  if (d > R) return ;
  chkmax (now[d], MKP (val, v));
  for (auto &u : G[v])
    if (u.t != F && !del[u.t])
      dfs_sbtr (u.t, v, d + 1, val + (u.w >= lmt ? 1 : -1));
}

void merge (int v, const edge &u)
{
  cvar (v), evar (u.t);
  now.resize (height[u.t] + 1);
  fill (iter (now), MKP (-oo, 0));
  dfs_sbtr (u.t, 0, 1, u.w >= lmt ? 1 : -1);

  Q.clear ();
  for (int i = min (height[u.t], R), j = 0; i; --i)
    {
      for (; j < sz_m (vec) && i + j <= R; ++j)
        {
          for (; !Q.empty () && Q.back ().Py.Px < vec[j].Px; Q.pop_back ());
          Q.push_back (MKP (j, vec[j]));
        }
      while (!Q.empty () && Q.front ().Px + i < L)
        Q.pop_front ();

      // match now[i] && Q.front ()
      if (!Q.empty () && now[i].Px + Q.front ().Py.Px >= 0)
        ans = MKP (now[i].Py, Q.front ().Py.Py); //, cerr << "upd: " << ans.Px << " " << ans.Py << endl;
    }

  for (int i = 1; i <= height[u.t]; ++i)
    if (sz_m (vec) <= i)
      vec.push_back (now[i]);
    else
      chkmax (vec[i], now[i]);
}

void dfs_div (int v)
{
  if (ans.Px) return ;
  dfs_init (v, 0);
  total = size[v], aux = MKP (oo, 0);
  dfs_find (v, 0);

  // cerr << aux.Py << endl;
  v = aux.Py, dfs_init (v, 0);
  sort (iter (G[v]), [](const edge &x, const edge &y){return height[x.t] < height[y.t]; });
  del[v] = true;

  vec.resize (1), vec[0] = MKP (0, v);
  for (auto &u : G[v])
    if (!del[u.t])
      merge (v, u);
  
  for (auto &u : G[v])
    if (!del[u.t])
      dfs_div (u.t);
}

bool check ()
{
  cvar (lmt), evar ("---");
  memset (del, 0, sizeof (del));
  ans = MKP (0, 0), dfs_div (1);
  return ans.Px;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("150E.in" , "r", stdin);
  freopen ("150E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n; VI ws;
  
  cin >> n >> L >> R; G.resize (n);

  for (int i = 1, s, t, w; i < n; ++i)
    {
      cin >> s >> t >> w;
      G.add (s, (edge){t, w});
      G.add (t, (edge){s, w});
      ws.push_back (w);
    }

  sort (iter (ws));
  ws.resize (unique (iter (ws)) - ws.begin ());
  int l = 0, r = ws.size () - 1, mid;
  for (; mid = (l + r + 1) >> 1, l < r; )
    lmt = ws[mid], check () ? (l = mid) : (r = mid - 1);

  lmt = ws[mid], check ();
  evar (lmt);
  cout << ans.Px << " " << ans.Py << endl;
  return 0; 
}
