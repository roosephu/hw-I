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

const int maxm = 55000, maxn = 220;

struct edge {int x, y, g, s; };

edge E[maxm];
int f[maxn], g[maxn];

void mkrt (int x)
{
  int y = f[x], t, w = g[x]; f[x] = x, g[x] = oo;
  for (; x != y; )
    t = g[y], g[y] = w, w = t, t = f[y], f[y] = x, x = y, y = t;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("76A.in" , "r", stdin);
  freopen ("76A.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m; int64 ans = (int64)2e18, G, S;
  
  cin >> n >> m >> G >> S;
  for (int i = 1, x, y, g, s; i <= m; ++i)
    cin >> x >> y >> g >> s, E[i] = (edge){x, y, g, s};
  sort (E + 1, E + m + 1, [](edge a, edge b)->bool {return a.s < b.s;});

  multiset<int> eg;
  for (int i = 1; i <= n; ++i)
    f[i] = i, g[i] = oo;
  for (int i = 1; i <= m; ++i)
    {
      edge &e = E[i];
      if (e.x == e.y) continue;
      mkrt (e.x), mkrt (e.y);
      if (f[e.x] == e.x)        // merge
        {
          f[e.x] = e.y;
          g[e.x] = e.g;
          eg.insert (e.g);
        }
      else                      // replace? 
        {
          PII w = MKP (0, 0);
          for (int x = e.x; x != e.y; x = f[x])
            chkmax (w, MKP (g[x], x));
          if (w.Px > e.g && w.Py)
            {
              f[w.Py] = w.Py, g[w.Py] = oo, eg.erase (eg.find (w.Px));
              mkrt (e.x), f[e.x] = e.y, g[e.x] = e.g;
              eg.insert (e.g);
            }
        }
      
      if (sz_m (eg) == n - 1)
        ans = min (ans, *--eg.end () * G + e.s * S);
    }

  if (sz_m (eg) != n - 1) return cout << -1 << endl, 0;
  cout << ans << endl;
  return 0; 
}
