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

const int maxn = 1100;

int deg[maxn];
bool now[maxn];
list<int> tab;
list<int>::iterator pos[maxn];
int cnt, n, K;
Graph<int> G;
int x[maxn], y[maxn], o[maxn];

void erase (int x) {tab.erase (pos[x]);}
void insert (int x) {tab.push_front (x); pos[x] = tab.begin (); }

void take (int v)
{
  erase (v), now[v] = true;
  for (auto &u : G[v])
    if (!o[u])
      {
        --deg[u], --deg[v], --cnt;
        if (!deg[u]) erase (u);
      }
}

void discard (int v, int V)
{
  for (auto &u : G[v])
    if (!o[u])
      {
        if (!deg[u]) insert (u);
        ++deg[u], ++deg[v], ++cnt;
      }
  insert (v), now[v] = false;
}

bool dfs (int K)
{
  if (K < 0) return false;
  if (K == 0) return cnt == 0;
  if (cnt <= 1)
    {
      for (int i = 1; i <= n; ++i)
        if (deg[i] == 1)
          {now[i] = true; break;}
      return true;
    }
  int v = *tab.begin ();
  if (deg[v] != 1)              // choose v
    {
      take (v); o[v] = v;
      if (dfs (K - 1)) return true;
      o[v] = 0; discard (v, v);
    }

  if (deg[v] <= K) // we'll choose it's neighbor
    {
      for (auto &u : G[v])
        if (!o[u])
          take (u), --K, o[u] = v;
      o[v] = v;
      if (dfs (K)) return true;
      o[v] = 0;
      for (auto &u : G[v])
        if (o[u] == v)
          discard (u, v), o[u] = 0;
    }

  o[v] = 0;
  return false;
}

bool check (int dis)
{
  G.adj.clear (), G.resize (n), cnt = 0, memset (deg, 0, sizeof (deg));
  for (int i = 1; i <= n; ++i)
    for (int j = i; j <= n; ++j)
      if (sqr (x[i] - x[j]) + sqr (y[i] - y[j]) > dis)
        G.add (i, j), G.add (j, i), ++cnt, ++deg[i], ++deg[j];
  tab.clear ();
  for (int i = 1; i <= n; ++i)
    if (deg[i])
      insert (i);

  memset (now, 0, sizeof (now));
  memset (o, 0, sizeof (o));
  return dfs (K);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("101D.in" , "r", stdin);
  freopen ("101D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n >> K;
  for (int i = 1; i <= n; ++i)
    cin >> x[i] >> y[i];
  int L = 0, R = ~0u >> 1, m;
  for (; m = (L + R) >> 1, L < R; )
    check (m) ? (R = m) : (L = m + 1);

  check (m), cerr << m << endl;
  for (int i = n; i; --i)
    if (now[i] || K == i)
      cout << i << " ", --K;
  return 0; 
}
