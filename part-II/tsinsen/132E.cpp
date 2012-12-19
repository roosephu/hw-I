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
#define sz_m(x) (int)((x).size ())
#define iter(x) (x).begin (), (x).end ()

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

const int maxn = 300, maxv = maxn * 3, maxe = maxn * 6;

struct edge {int t, w, c; edge *n, *o; };

edge graph[maxe << 1], *eptr = graph, *adj[maxv];
int S, T, phi, mincost, tms;
int dist[maxv], succ[maxv], o[maxn], pred[maxv], x[maxn];

void adde (int s, int t, int w, int c)
{
  // cerr << "adde: " << s << " " << t << " " << w << " " << c << endl;
  *(++eptr) = (edge){t, +w, c, adj[s]}, adj[s] = eptr;
  *(++eptr) = (edge){s, -w, 0, adj[t]}, adj[t] = eptr;
  adj[s]->o = adj[t], adj[t]->o = adj[s];
}

bool modify_dist ()
{
  memset (dist, 0x3F, sizeof dist), dist[T] = 0;
  memset (succ, 0, sizeof succ);
  int head = T, tail = T, v, dtmp;
  for (; head; head = succ[v], succ[v] = 0)
    for (edge *e = adj[v = head]; e; e = e->n)
      if (e->o->c && (dtmp = dist[v] - e->w) < dist[e->t])
        {
          dist[e->t] = dtmp;
          if (e->t == tail || succ[e->t]) continue;
          if (head != tail && dist[succ[v]] > dtmp)
            succ[e->t] = succ[v], succ[v] = e->t;
          else
            succ[tail] = e->t, tail = e->t;
        }
  for (int v = 1; v <= T; ++v)
    for (edge *e = adj[v]; e; e = e->n)
      e->w -= dist[v] - dist[e->t];
  phi += dist[S]; evar (dist[S]);
  return dist[S] != oo;
}

int augment (int v, int f)
{
  if (v == T) return mincost += f * phi, f;
  int l = f; o[v] = tms;
  for (edge *e = adj[v]; e; e = e->n)
    if (o[e->t] != tms && e->c && !e->w)
      {
        int x = augment (e->t, min (e->c, f));
        e->c -= x, e->o->c += x, f -= x;
        if (!f) return l;
      }
  return l - f;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("132E.in" , "r", stdin);
  freopen ("132E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m; unordered_map<int, int> f;
  
  cin >> n >> m; 
  int tmp = 2 * n + 1; S = 3 * n + 2, T = S + 1;
  for (int i = 1; i <= n; ++i)
    {
      cin >> x[i];

      int cost = 0;
      for (int b = 0; b < 30; ++b)
        cost += x[i] >> b & 1;

      if (f[x[i]]) adde (f[x[i]] + n, i, 0, 1), pred[i] = f[x[i]];
      adde (tmp, i, cost, 1);
      adde (i, T, 0, 1);
      adde (S, i + n, 0, 1);
      adde (tmp, tmp + 1, 0, m);
      adde (i + n, ++tmp, 0, 1);
      // cerr << "--------------------" << endl;
      f[x[i]] = i;
    }
  adde (tmp, tmp - n, 0, m);

  // return 0;
  for (; modify_dist (); )
    for (; ++tms, augment (S, oo); );

  unordered_set<int> unused; vector<int> ans; ans.push_back (0); int tot = n;
  
  for (int i = 0; i < m; ++i)
    unused.insert (i);
  for (int i = 1; i <= n; ++i)
    {
      for (edge *e = adj[i]; e; e = e->n)
        if (e->c == 1)
          {
            if (e->t > n * 2) ++tot, ans.push_back (*unused.begin ()), unused.erase (ans[i]);
            else ans.push_back (ans[pred[i]]);
            break;
          }
      for (edge *e = adj[i + n]; e; e = e->n)
        if (e->c == 0 && e->t > n * 2)
          unused.insert (ans[i]);
    }

  cout << tot << " " << mincost << endl;
  f.clear ();
  for (int i = 1; i <= n; ++i)
    {
      char c = 'a' + ans[i];
      if (f[ans[i]] != x[i])
        f[ans[i]] = x[i], cout << c << "=" << x[i] << endl;
      cout << "print(" << c << ")" << endl;
    }
  return 0; 
}
