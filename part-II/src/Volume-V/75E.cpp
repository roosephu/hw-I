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

const int maxn = 550;
typedef long double real;

struct edge {int t; real w; };
struct crd {real x, y, z; };

crd operator^ (crd a, crd b) { return (crd){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}; }

Graph<edge> G (500);
real dist[maxn];
crd poly[maxn];
int next[maxn], idx[maxn];

real in (real x, real L, real R)
{
  if (L > R) swap (L, R);
  return L - 1e-15 <= x && x <= R + 1e-15;
}

int cmp (int x, int y) {return MKP (poly[x].x, poly[x].y) < MKP (poly[y].x, poly[y].y);}

void adde (int s, int t, int m)
{
  real w = hypot (poly[s].x - poly[t].x, poly[s].y - poly[t].y) * m;
  G.adde (s, (edge){t, w});
  G.adde (t, (edge){s, w});
}

void SPFA (int S)
{
  fill (dist, dist + maxn, 1e300), dist[S] = 0;
  int head = S, tail = S, v; real dtmp;
  for (; (v = head); head = next[v], next[v] = 0)
    foreach (e, G[v])
      if ((dtmp = dist[v] + e->w) < dist[e->t])
        {
          dist[e->t] = dtmp;
          if (next[e->t] || e->t == tail) continue;
          if (head != tail && dist[next[v]] > dtmp)
            next[e->t] = next[v], next[v] = e->t;
          else
            next[tail] = e->t, tail = e->t;
        }
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("75E.in" , "r", stdin);
  freopen ("75E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  crd S, T; int n;
  
  cin >> S.x >> S.y >> T.x >> T.y >> n, S.z = T.z = 1;
  for (int i = 1; i <= n; ++i)
    cin >> poly[i].x >> poly[i].y, poly[i].z = 1;
  poly[0] = poly[n], poly[n + 1] = S, poly[n + 2] = T;

  S.x += 1e-6, S.y += 1e-6, T.x += 1e-8, T.y += 1e-9;
  crd Lst = S ^ T;
  int tot = n + 2;

  cout << setprecision (15);
  for (int i = 1; i <= n; ++i)
    {
      crd L = poly[i] ^ poly[i % n + 1], x = L ^ Lst; bool b = false;
      
      if (x.z)
        {
          x.x /= x.z, x.y /= x.z;
          if (in (x.x, poly[i].x, poly[i % n + 1].x) && in (x.x, S.x, T.x) && 
              in (x.y, poly[i].y, poly[i % n + 1].y) && in (x.y, S.y, T.y))
            b = true;
        }
      if (b)
        {
          ++tot;
          poly[tot] = x;
          adde (i, tot, 1);
          adde (tot, i % n + 1, 1);
          cerr << "intersect: ", cvar (x.x), evar (x.y);
        }
      else if (!x.x && !x.y && !x.z)
        return cout << hypot (S.x - T.x, S.y - T.y) << endl, 0;
      else
        adde (i, i % n + 1, 1);
    }
  for (int i = n + 1; i <= tot; ++i)
    idx[i - n] = i;
  sort (idx + 1, idx + tot - n + 1, cmp);
  evar (tot - n);
  for (int i = 1, j = 0; i < tot - n; ++i)
    adde (idx[i], idx[i + 1], j + 1), j ^= 1;

  SPFA (n + 1);
  cout << setprecision (15) << dist[n + 2] << endl;
  return 0; 
}
