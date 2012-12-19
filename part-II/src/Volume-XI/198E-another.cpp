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

struct gripper {int x, y, m, p; int64 r; } ;

struct node
{
  node *lc, *rc;
  int64 lx, rx, ly, ry;
  pair<int, gripper *> min;
};

const int maxn = 260000;

gripper g[maxn];
node buf[maxn], *pbuf = buf, *root;
bool cmp_key;
int ans;
pair<int, gripper *> aux;

bool cmp (const gripper &a, const gripper &b) {return cmp_key ? (a.x < b.x) : (a.y < b.y); }

node *kd_build (int L, int R, int key)
{
  cmp_key = key, sort (g + L, g + R, cmp);
  int m = (L + R + 1) >> 1; node *ret = ++pbuf;
  if (L + 1 == R) return *ret = (node){0, 0, g[L].x, g[L].x, g[L].y, g[L].y, MKP (g[L].m, g + L)}, ret;
  ret->lc = kd_build (L, m, !key);
  ret->rc = kd_build (m, R, !key);
  ret->lx = min (ret->lc->lx, ret->rc->lx);
  ret->rx = max (ret->lc->rx, ret->rc->rx);
  ret->ly = min (ret->lc->ly, ret->rc->ly);
  ret->ry = max (ret->lc->ry, ret->rc->ry);
  ret->min = min (ret->lc->min, ret->rc->min);
  return ret;
}

void erase (node *t, gripper &x)
{
  if (!t->lc && !t->rc) return (void)(t->min.Px = oo);
  if (t->lc && t->lc->lx <= x.x && x.x <= t->lc->rx && t->lc->ly <= x.y && x.y <= t->lc->ry)
    erase (t->lc, x);
  else
    erase (t->rc, x);
  t->min = MKP (oo, nullptr);
  if (t->lc) chkmin (t->min, t->lc->min);
  if (t->rc) chkmin (t->min, t->rc->min);
}

bool in (node *t, gripper &P)
{
  return sqr (max (abs (t->lx - P.x), abs (t->rx - P.x))) + sqr (max (abs (t->ly - P.y), abs (t->ry - P.y))) <= P.r;
}

bool intersect (node *t, gripper &P)
{ 
  return sqr (min (abs (t->lx - P.x), abs (t->rx - P.x))) + sqr (min (abs (t->ly - P.y), abs (t->ry - P.y))) <= P.r;
}

void query (node *t, gripper &x)
{
  if (in (t, x)) return (void)(chkmin (aux, t->min));
  if (t->lc && intersect (t->lc, x))
    query (t->lc, x);
  if (t->rc && intersect (t->rc, x))
    query (t->rc, x);
}

void dfs (gripper *x)
{
  cerr << "dfs: " << x - g << endl;
  ++ans; erase (root, *x), aux = MKP (oo, nullptr);
  for (; query (root, *x), aux.Px <= x->p; )
    dfs (aux.Py);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("198E.in" , "r", stdin);
  freopen ("198E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  
  int n;
  cin >> g[0].x >> g[0].y >> g[0].p >> g[0].r >> n;
  for (int i = 1; i <= n; ++i)
    cin >> g[i].x >> g[i].y >> g[i].m >> g[i].p >> g[i].r;
  for (int i = 0; i <= n; ++i)
    g[i].r = sqr (g[i].r);

  root = kd_build (0, n + 1, 0);
  dfs (g);

  cout << ans - 1 << endl;
  return 0; 
}
