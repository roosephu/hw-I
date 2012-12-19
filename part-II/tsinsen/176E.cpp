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

const int maxn = 110000;

struct edge {int t, w; };

typedef int arr32[maxn];

Graph<edge> G;
vector<int> ord;
arr32 depth, pos, fa, size, root, aux;
int64 ans, dist[maxn];
int low;

void dfs (int v, int f, int64 w)
{
  size[v] = 1, fa[v] = f, depth[v] = depth[f] + 1, dist[v] = w;
  ord.push_back (v), pos[v] = SZ (ord);
  for (auto &u : G[v])
    if (u.t != f)
      {
        dfs (u.t, v, w + u.w);
        size[v] += size[u.t];
        if (size[u.t] > size[aux[v]]) aux[v] = u.t;
      }
}

int LCA (int u, int v)
{
  for (; root[u] != root[v]; u = fa[root[u]])
    if (depth[root[u]] < depth[root[v]])
      swap (u, v);
  return depth[u] < depth[v] ? u : v;
}

struct cmp {bool operator () (const int &a, const int &b) {return pos[a] < pos[b];} };
set<int, cmp> S;

void update (int p, int x, int q, int d)
{
  if (p     ) ans += (dist[x] - dist[LCA (p, x)]) * d;
  if (q     ) ans += (dist[q] - dist[LCA (x, q)]) * d;
  if (p && q) ans -= (dist[q] - dist[LCA (p, q)]) * d;
  else if (!S.empty ()) low = LCA (*S.begin (), *--S.end ());
}

pair<int, int> get_neighbor (int x)
{
  auto it = S.lower_bound (x), a = it, b = it;
  int p = it == S.begin () ? 0 : *--a;
  int q = it == --S.end () ? 0 : *++b;
  return MKP (p, q);
}

void insert (int x)
{
  S.insert (x);
  pair<int, int> y = get_neighbor (x);
  update (y.Px, x, y.Py, +1);
}

void erase (int x)
{
  pair<int, int> y = get_neighbor (x);
  S.erase (x);
  update (y.Px, x, y.Py, -1);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("176E.in" , "r", stdin);
  freopen ("176E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int Q, n, x; char cmd;
  
  cin >> n, G.resize (n);
  for (int i = 1, a, b, c; i < n; ++i)
    cin >> a >> b >> c, G.add (a, (edge){b, c}), G.add (b, (edge){a, c});
  dfs (1, 0, 0);
  for (auto &v : ord)
    if (!root[v])
      for (int u = v; u; u = aux[u])
        root[u] = v;

  cin >> Q;
  for (; Q--; )
    {
      cin >> cmd;
      if (cmd == '?')
        cout << ans + (S.empty () ? 0 : dist[*S.begin ()] - dist[low]) << endl;
      else if (cmd == '+')
        cin >> x, insert (x);
      else if (cmd == '-')
        cin >> x, erase (x);
      // for (auto &x : S)
      //   cerr << x << " ";
      // cerr << ": " << ans << " " << low << endl;
    }
  return 0; 
}
