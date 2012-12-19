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

typedef int arr32[maxn];

Graph<int> G, g;
stack<int> stk;
arr32 dfn, low, rep, deg, size, prop;
int tms, cnt;
bool o[maxn];

void dfs (int v, int f)
{
  stk.push (v), dfn[v] = low[v] = ++tms;
  for (int &u : G[v])
    if (!dfn[u])
      dfs (u, v), low[v] = min (low[u], low[v]);
    else if (u != f)
      low[v] = min (low[v], dfn[u]);

  if (low[v] == dfn[v])
    {
      for (; stk.top () != v; stk.pop ())
        rep[stk.top ()] = v;
      rep[stk.top ()] = v, stk.pop ();
    }
}

void find (int v)
{
  cnt += deg[v] == 1, dfn[v] = 1;
  for (auto &u : g[v])
    if (!dfn[u])
      find (u);
}

int dp (int v, int f)
{
  dfn[v] = 1; int now = -1, ret = 0;
  for (auto &u : g[v])
    if (u != f)
      {
        ret += dp (u, v);
        if (prop[u] == 0 && now == 0) ++ret, now = -1;
        else if (prop[u] == 1 && now == 1) --ret, now = -1;
        else if (now != -1) now = -1;
        else now = prop[u];
      }
  if (now == 0) ++ret, prop[v] = 1;
  else if (now == -1) prop[v] = 0;
  else if (now == 1) prop[v] = 1;
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("191D.in" , "r", stdin);
  freopen ("191D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m;
  
  cin >> n >> m, G.resize (n), g.resize (n);  
  for (int i = 1, s, t; i <= m; ++i)
    cin >> s >> t, G.add (s, t), G.add (t, s);
  
  for (int i = 1; i <= n; ++i)
    if (!dfn[i])
      dfs (i, 0);
  for (int i = 1; i <= n; ++i)
    ++size[rep[i]];
  
  // for (int i = 1; i <= n; ++i)
  //   cerr << rep[i] << endl;

  memset (dfn, 0, sizeof (dfn));
  for (int v = 1; v <= n; ++v)
    {
      bool b = false;
      for (auto &u : G[v])
        {
          if (rep[v] != rep[u] && u <= v)
            g.add (u, v), g.add (v, u), ++deg[v], ++deg[u];
          if (rep[v] != rep[u])
            b = true;
        }
      dfn[rep[v]] += b;
    }

  int ans = 0;
  for (int v = 1; v <= n; ++v)
    ans += size[v] > 1 && dfn[v] <= 1;
  
  memset (dfn, 0, sizeof (dfn));
  for (int v = 1; v <= n; ++v)
    if (!dfn[v] && rep[v] == v)
      {
        // cnt = 0;
        // find (v);
        // ans += (cnt + 1) >> 1;
        ans += dp (v, 0);
      }

  cout << ans << " " << m << endl;
  return 0; 
}
