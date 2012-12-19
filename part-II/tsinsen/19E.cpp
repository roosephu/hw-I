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
#define sz_m(x) (int)((x).size ())
#define it_m(x) (x).begin (), (x).end ()

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

const int maxn = 11000, maxm = maxn;

struct edge {int t, z, f, g; edge *n;};

edge graph[maxm << 1], *eptr = graph, *adj[maxn];
int dep[maxn], f[maxn], g[maxn], loops;

void dfs (int v, int fth)
{
  dep[v] = dep[fth] + 1;
  for (edge *e = adj[v]; e; e = e->n)
    if (!dep[e->t])
      dfs (e->t, v), e->f = f[e->t], f[v] += f[e->t], e->g = g[e->t], g[v] += g[e->t];
    else if (dep[e->t] < dep[v] && e->t != fth)
      if ((dep[e->t] + dep[v]) % 2 == 0)
        e->g = 1, ++g[v], --g[e->t], ++loops;
      else
        e->f = 1, ++f[v], --f[e->t];
}

void adde (int s, int t, int z)
{
  *(++eptr) = (edge){t, z, 0, 0, adj[s]}, adj[s] = eptr;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("19E.in" , "r", stdin);
  freopen ("19E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m; VI ans;
  
  cin >> n >> m;
  for (int i = 1, s, t; i <= m; ++i)
    cin >> s >> t, adde (s, t, i), adde (t, s, i);
  for (int i = 1; i <= n; ++i)
    if (!dep[i])
      dfs (i, 0);
  for (int v = 1; v <= n; ++v)
    for (edge *e = adj[v]; e; e = e->n)
      if (e->g == loops && !e->f)
        ans.push_back (e->z);
  sort (it_m (ans));
  ans.resize (unique (it_m (ans)) - ans.begin ());
  
  cout << sz_m (ans) << endl;
  foreach (it, ans)
    cout << *it << " ";
  cout << endl;

  return 0; 
}
