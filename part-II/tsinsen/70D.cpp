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

double mx, my;

struct crd
{
  double alpha; int x, y;
  crd () {}
  crd (int x, int y) : x (x), y (y) {}
};

bool operator < (const crd &a, const crd &b) {return a.alpha < b.alpha;}

set<crd> S;
typedef set<crd>::iterator ptr;

#define turn(o,a,b) ((int64)(a.x - o.x) * (b.y - o.y) - (int64)(a.y - o.y) * (b.x - o.x))
// ptr pred (crd& x) {return x == S.begin () ? x = S.end (), 0 : 0, --x; }
// ptr next (crd& x) {return ++x, x == S.end () ? x = S.begin (), 0 : 0, x; }

crd prev (crd &x)
{
  // if (S.count (x)) return x;
  ptr it = S.lower_bound (x);
  if (it == S.begin ()) return *--S.end ();
  return *--it;
}

crd next (crd &x)
{
  // if (S.count (x)) return x;
  ptr it = S.lower_bound (x);
  if (it == S.end ()) return *S.begin ();
  return *it;
}

bool query (crd x)
{
  crd L = prev (x), R = next (x);
  return turn (L, x, R) <= 0;
}

void insert (crd x)
{
  crd L = prev (x), R = next (x), t;
  if (turn (L, x, R) <= 0) return ;

  for (S.erase (L); t = prev (L), turn (t, x, L) >= 0; L = t)
    S.erase (L);
  S.insert (L);
  for (S.erase (R); t = next (R), turn (t, x, R) <= 0; R = t)
    S.erase (R);
  S.insert (R);
  
  S.insert (x);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("70D.in" , "r", stdin);
  freopen ("70D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int q, cmd, x, y; crd p[3];
  double w[3] = {0.6419802878555676, 0.050906107300324535, 0.30711360484410793}
    // { 0.4352341254, 0.8242147544, 0.3614575554 }
  , sum = 0;
  // cin >> q;
  scanf ("%d", &q);
  for (int i = 0; i < 3; ++i)
    {
      sum += w[i];
      // cin >> cmd >> p[i].x >> p[i].y;
      scanf ("%d%d%d", &cmd, &p[i].x, &p[i].y);
      mx += p[i].x * w[i], my += p[i].y * w[i];
    }
  mx /= sum, my /= sum;
  for (int i = 0; i < 3; ++i)
    p[i].alpha = atan2 (p[i].y - my, p[i].x - mx), S.insert (p[i]);
  
  for (q -= 3; q--; )
    {
      // cin >> cmd >> x >> y;
      scanf ("%d%d%d", &cmd, &x, &y);
      crd p (x, y); p.alpha = atan2 (y - my, x - mx);
      if (cmd == 1) insert (p);
      else // cout << (query (p) ? "YES" : "NO") << endl;
        printf ("%s\n", (query (p) ? "YES" : "NO"));
    }
  return 0; 
}
