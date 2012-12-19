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

const int maxn = 110000, maxv = maxn * 4, maxlog = 20, maxq = 110000;

struct node {int len, suf; unordered_map<int, node *> c; node *f;};
struct subq {int t, beg, end; };
typedef int arr32[maxv];

node buf[maxv], *pbuf = buf, *root, *prefix[maxv];
Graph<int> G;
Graph<subq> queries;
vector<int> suffixes;
arr32 enter, leave, dep, x, bit;
int fa[maxv][maxlog];
int n;
int ans[maxq];

node *newnode (int len) {return *(++pbuf) = (node){len}, pbuf;}

void extend (node *p, int c)
{
  node *b = p, *q, *w; p = newnode (p->len + 1); // evar (c);
  for (; b && !b->c.count (c); b = b->f)
    b->c[c] = p;
  if (!b) p->f = root;
  else if ((w = b->c[c])->len == b->len + 1)
    p->f = w;
  else
    {
      q = newnode (0), q->f = w->f, q->c = w->c;
      q->len = b->len + 1, w->f = p->f = q;
      for (; b && b->c.count (c) && b->c[c] == w; b = b->f)
        b->c[c] = q;
    }
}

void dfs_suffix_tree (int v)
{
  for (int i = 0; fa[v][i]; ++i)
    fa[v][i + 1] = fa[fa[v][i]][i];
  dep[v] = buf[v].len;
  
  enter[v] = SZ (suffixes);
  if (buf[v].suf) suffixes.push_back (buf[v].suf);
  for (auto &x : G[v])
    dfs_suffix_tree (x);
  leave[v] = SZ (suffixes);
}

int get_pos (int L, int R)
{
  int v = prefix[R - 1] - buf, len = R - L; // evar (dep[v]);
  for (int t = maxlog - 1; t >= 0; --t)
    if (dep[fa[v][t]] >= len)
      v = fa[v][t];
  return v;
}

void bit_modify (int t, int v)
{
  for (; t <= n; t += t & -t)
    bit[t] += v;
}

int bit_query (int t)
{
  int x = bit[t];
  for (; t &= t - 1; x += bit[t]);
  return x;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("232D.in" , "r", stdin);
  freopen ("232D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> x[i];
  root = pbuf;

  --n;
  node *ptr = root;
  for (int i = 1, c; c = x[i + 1] - x[i], i <= n; ++i)
    extend (ptr, c), ptr = ptr->c[c];
  for (int i = 1, c; c = x[i] - x[i + 1], i <= n; ++i)
    extend (ptr, c), ptr = ptr->c[c];
  
  ptr = root;
  for (int i = 1, c; c = x[i + 1] - x[i], i <= n; ++i)
    ptr = ptr->c[c], ptr->suf = i;
  for (int i = 1, c; c = x[i] - x[i + 1], i <= n; ++i)
    ptr = ptr->c[c], prefix[i] = ptr;

  G.resize (n * 4);
  for (int i = 1; i <= pbuf - root; ++i)
    fa[i][0] = buf[i].f - buf, G.add (fa[i][0], i);
  dfs_suffix_tree (0);

  // for (auto &x : suffixes)
  //   cerr << x << " ";
  // cerr << endl;

  // evar (dep[0]);
  int Q, L, R;
  cin >> Q; queries.resize (n);
  // cerr << 1.0 * clock () / CLOCKS_PER_SEC << endl;
  for (int i = 1; i <= Q; ++i)
    {
      cin >> L >> R;
      if (L >= R) {ans[i] = n; continue;}
      int pos = get_pos (L, R);
      R = min (n, R + R - L - 1), L = max (0, L - 2);
      // cerr << enter[pos] << " " << leave[pos] << " # " << L << " " << R << endl;
      queries.add (enter[pos], (subq){i, L, R});
      queries.add (leave[pos], (subq){i, L, R});
    }

  for (int i = 1; i <= n; ++i)
    {
      bit_modify (suffixes[i - 1], 1);
      for (auto &Q : queries[i])
        ans[Q.t] = i - bit_query (Q.end) + bit_query (Q.beg) - ans[Q.t];
    }
  for (int i = 1; i <= Q; ++i)
    cout << ans[i] << endl;
  return 0; 
}
