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

int mx, my;

struct crd
{
  double alpha; int x, y;
};
struct pcrd {crd *x;};

bool operator < (const pcrd &a, const pcrd &b) {return a.x->alpha < b.x->alpha;}

const int maxn = 110000;

set<pcrd> S;
typedef set<pcrd>::iterator ptr;
crd p[maxn];

int64 turn (crd *o, crd* a, crd *b) {return (int64)(a->x - o->x) * (b->y - o->y) - (int64)(a->y - o->y) * (b->x - o->x);}
ptr pred (ptr x) {return x == S.begin () ? --S.end () : --x; }
ptr next (ptr x) {return ++x == S.end () ? S.begin () :   x; }

bool query (pcrd x)
{
  ptr R = *--S.end () < x ? S.begin () : lower_bound (S.begin (), S.end (), x), L = pred (R);
  return turn (L->x, x.x, R->x) <= 0;
}

void insert (pcrd x)
{
  ptr R = *--S.end () < x ? S.begin () : lower_bound (S.begin (), S.end (), x), L = pred (R), t;
  if (turn (L->x, x.x, R->x) <= 0) return ;
  for ( ; t = pred (L), turn (t->x, x.x, L->x) > 0; L = t)
    S.erase (L);
  for ( ; t = next (R), turn (t->x, x.x, R->x) < 0; R = t)
    S.erase (R);
  S.insert (x);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("70D.in" , "r", stdin);
  freopen ("70D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int q, cmd, x, y;
  // cin >> q;
  scanf ("%d", &q);
  for (int i = 1; i <= 3; ++i)
    {
      // cin >> cmd >> p[i].x >> p[i].y;
      scanf ("%d%d%d", &cmd, &p[i].x, &p[i].y);
      mx += p[i].x, my += p[i].y;
    }
  for (int i = 1; i <= 3; ++i)
    p[i].alpha = atan2 (p[i].y * 3 - my, p[i].x * 3 - mx), S.insert ((pcrd){p + i});
  
  for (int i = 4; i <= q; ++i)
    {
      // cin >> cmd >> x >> y;
      scanf ("%d%d%d", &cmd, &x, &y);
      p[i] = (crd){atan2 (y * 3 - my, x * 3 - mx), x, y};
      if (cmd == 1) insert ((pcrd){p + i});
      else // cout << (query (p) ? "YES" : "NO") << endl;
        printf ("%s\n", (query ((pcrd){p + i}) ? "YES" : "NO"));
    }
  return 0; 
}
