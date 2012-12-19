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

const int maxv = 1000, maxe = 100000;

struct edge {int t; int64 c; edge *n, *o; };
typedef int arr32[maxv];

edge graph[maxe << 1], *eptr = graph, *adj[maxv], *adm[maxv];
arr32 gap, pred, dist;
int S, T;

void rev_bfs ()
{
  memset (dist, 0x3F, sizeof (dist));
  memset (gap, 0, sizeof (gap));
  int v; queue<int> Q;
  Q.push (T), ++gap[dist[T] = 0];
  for (; !Q.empty (); Q.pop ())
    for (edge *e = adj[v = Q.front ()]; e; e = e->n)
      if (e->o->c && dist[e->t] > dist[v] + 1)
        Q.push (e->t), ++gap[dist[e->t] = dist[v] + 1];
}

int64 augment ()
{
  int v; int64 w = 1e18;
  for (edge *e = adm[v = S]; v != T; v = e->t, e = adm[v])
    w = min (w, e->c);
  for (edge *e = adm[v = S]; v != T; v = e->t, e = adm[v])
    e->c -= w, e->o->c += w;
  return w;
}

int64 SAP ()
{
  int64 flow = 0; int v, md; edge *e;

  rev_bfs ();
  // for (int i = 1; i <= T; ++i)
  //   cerr << dist[i] << endl;
  // return 0;

  memcpy (adm, adj, sizeof (adm));
  for (v = S; dist[v] < T; )
    {
      for (e = adm[v]; e; e = e->n)
        if (e->c && dist[e->t] == dist[v] - 1)
          break;
      if (e)
        {
          pred[e->t] = v, adm[v] = e, v = e->t;
          if (v == T)
            flow += augment (), v = S;
        }
      else
        {
          if (!--gap[dist[v]]) break;
          e = adm[v] = adj[v];
          for (md = T; e; e = e->n)
            if (e->c && dist[e->t] < md)
              md = dist[e->t];
          ++gap[dist[v] = md + 1];
          if (v != S) v = pred[v];
        }
    }
  return flow;
}

void adde (int s, int t, int64 c)
{
  *(++eptr) = (edge){t, c, adj[s]}, adj[s] = eptr;
  *(++eptr) = (edge){s, 0, adj[t]}, adj[t] = eptr;
  adj[s]->o = adj[t], adj[t]->o = adj[s];
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("103E.in" , "r", stdin);
  freopen ("103E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n; int64 total = 0;
  
  cin >> n;
  S = n * 2 + 1, T = S + 1; int64 U = 1e9;
  for (int i = 1, j, k; i <= n; ++i)
    {
      cin >> k;
      for (; k--; )
        cin >> j, adde (i, j + n, U * U);
      adde (i + n, T, U);
    }
  for (int i = 1, j; i <= n; ++i)
    cin >> j, adde (S, i, U - j), total += U - j;

  cout << SAP () - total << endl;
  return 0; 
}
