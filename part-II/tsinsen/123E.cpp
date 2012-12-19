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
#define m_sz(x) (int)((x).size ())
#define m_it(x) (x).begin (), (x).end ()

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef set<int> SI;
typedef pair<int, int> PII;

int64 fpm (int64 b, int64 e, int64 m) { int64 t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }
template<class T> inline bool chkmin (T &a, T b) {return a < b ? a = b, true : false;}
template<class T> inline bool chkmax (T &a, T b) {return a > b ? a = b, true : false;}
template<class T> inline T sqr (T x) {return x * x;}

template<class edge> struct Graph
{
  vector<vector<edge> > adj;
  Graph (int n) {adj.clear (); adj.resize (n + 5);}
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

const int maxn = 110000;

typedef int64 arr64[maxn];
struct edge {int t; edge *n;};

arr64 sx, sy, sdx, sdy, x, y, sz;
edge graph[maxn << 1], *eptr = graph, *adj[maxn];
int64 tx, ty, ans, n, pa, pb;

void dfs (int v, int f)
{
  edge *e;
  sx[v] = x[v], sy[v] = y[v], sz[v] = 1;
  for (e = adj[v]; e; e = e->n)
    if (e->t != f)
      {
        dfs (e->t, v);
        // pa += sx[e->t] * sdy[v] + sy[e->t] * sdx[v];
        pb += sx[e->t] * sz[e->t] * y[v];
        sx[v] += sx[e->t];
        // sy[v] += sy[e->t];
        // sdx[v] += sdx[e->t] + sx[e->t];
        // sdy[v] += sdy[e->t] + sy[e->t];
        sz[v] += sz[e->t];
      }
  // cvar (sx[v]), cvar (sy[v]), cvar (sdx[v]), cvar (sdy[v]), evar (sz[v]);
  // pa += sdx[v] * y[v] + x[v] * sdy[v];
  pb += (tx - sx[v]) * (n - sz[v]) * y[v];
  // pb -= x[v] * y[v];
}

void adde (int s, int t)
{
  *(++eptr) = (edge){t, adj[s]}, adj[s] = eptr;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("123E.in" , "r", stdin);
  freopen ("123E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  cin >> n;
  for (int i = 1, s, t; i < n; ++i)
    cin >> s >> t, adde (s, t), adde (t, s);
  for (int i = 1; i <= n; ++i)
    cin >> x[i] >> y[i], tx += x[i], ty += y[i];
  dfs (1, 0);
  cvar (pa), evar (pb);

  ans = pb;
  cout << setprecision (15) << 1.0 * ans / tx / ty << endl;
  return 0; 
}
