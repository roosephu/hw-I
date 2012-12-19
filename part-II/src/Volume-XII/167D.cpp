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

const int maxn = 110000, mod = 1000000009;

struct node {node *lc, *rc; pair<int, int> dp; int key, weight;} ;

node buf[maxn], *pbuf = buf, *null = buf, *root;
pair<int, int> P[maxn];

pair<int, int> operator + (const pair<int, int> &lc, const pair<int, int> &rc)
{
  pair<int, int> ret = MKP (lc.Py + rc.Py, max (lc.Px + rc.Py, lc.Py + rc.Px) + 1);
  return chkmax (ret.Py, ret.Px), ret;
}

void update (node *t)
{
  if (t == null) return ;
  t->dp = t->lc->dp + t->rc->dp;
}

node *merge (node *p, node *q)
{
  if (p == null) return q; if (q == null) return p;
  if (p->weight > q->weight)
    return p->rc = merge (p->rc, q), update (p), p;
  return q->lc = merge (p, q->lc), update (q), q;
}

void split (node *p, int key, node *&l, node *&r)
{
  if (p == null) return (void)(l = r = null);
  if (p->key <= key) l = p, split (p->rc, key, p->rc, r);
  else               r = p, split (p->lc, key, l, p->lc);
  update (p);
}

void insert (node *t)
{
  node *L, *R;
  split (root, t->key, L, R);
  root = merge (merge (L, t), R);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("167D.in" , "r", stdin);
  freopen ("167D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, K, m; int64 a, b, c, d;
  
  cin >> n >> K;
  null->lc = null->rc = null, null->dp.Px = -1, root = null;
  for (int i = 1; i <= K; ++i)
    cin >> P[i].Px >> P[i].Py;
  cin >> a >> b >> c >> d;
  for (int i = K + 1; i <= n; ++i)
    P[i] = MKP ((a * P[i - 1].Px + b) % mod, (c * P[i - 1].Py + d) % mod);

  for (int i = 1; i <= n; ++i)
    buf[i] = (node){null, null, MKP (0, 0), P[i].Px, P[i].Py}, insert (buf + i);

  cin >> m;
  for (int i = 1, lx, rx; i <= m; ++i)
    {
      cin >> lx >> rx;
      node *L, *M, *R;
      split (root, lx - 1, L, M);
      split (M, rx, M, R);
      cout << M->dp.Py << endl;
      root = merge (merge (L, M), R);
    }

  return 0; 
}
