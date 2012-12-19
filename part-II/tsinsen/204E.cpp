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

const int maxalpha = 26, maxlen = 110000, maxn = 110000;

struct node {int len, dep, size, cnt, max; node *c[maxalpha], *f, *aux, *root; vector<node*> adj; vector<int> belong; };

node buf[maxlen << 1], *pbuf = buf, *root;
vector<node *> ord;
node *lv[maxn];
string S[maxn];
int K;

node *get_new (int len)
{
  return ++pbuf, pbuf->len = len, pbuf;
}

void extend (node *p, int c)
{
  node *b = p, *q, *w; p = get_new (p->len + 1);
  for (; b && !b->c[c]; b = b->f)
    b->c[c] = p;
  if (!b) p->f = root;
  else if ((w = b->c[c])->len == b->len + 1)
    p->f = w;
  else
    {
      q = get_new (b->len + 1), memcpy (q->c, w->c, sizeof (w->c));
      q->f = w->f, p->f = w->f = q;
      for (; b && b->c[c] == w; b = b->f)
        b->c[c] = q;
    }
}

node *LCA (node *u, node *v)
{
  for (; u->root != v->root; u = u->root->f)
    if (u->root->dep < v->root->dep)
      swap (u, v);
  return u->dep < v->dep ? u : v;
}

void dfs_init (node *v)
{
  v->size = 1; ord.push_back (v);
  for (auto &u : v->adj)
    {
      u->dep = v->dep + 1;
      dfs_init (u);
      v->size += u->size;
      if (!v->aux || v->aux->size < u->size)
        v->aux = u;
    }
}

void dfs (node *v)
{
  for (auto &x : v->belong)
    {
      ++v->cnt;
      --LCA (v, lv[x])->cnt;
      lv[x] = v;
    }
  
  for (auto &u : v->adj)
    dfs (u), v->cnt += u->cnt;
}

void dfs_work (node *v)
{
  if (v->cnt >= K) v->max = v->len;
  for (auto &u : v->adj)
    u->max = v->max, dfs_work (u);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("204E.in" , "r", stdin);
  freopen ("204E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> n >> K;
  root = get_new (0);
  for (int i = 1; i <= n; ++i)
    {
      cin >> S[i]; node *ptr = root;
      for (int x = 0; x < SZ (S[i]); ++x)
        {
          int c = S[i][x] - 'a';
          if (!ptr->c[c] || ptr->c[c]->len != x)
            extend (ptr, c);
          ptr = ptr->c[c];
        }
      lv[i] = root;
    }

  for (int i = 1; i <= n; ++i)
    {
      node *ptr = root;
      for (int x = 0; x < SZ (S[i]); ++x)
        {
          int c = S[i][x] - 'a';
          ptr = ptr->c[c];
          ptr->belong.push_back (i);
        }
    }
  for (auto p = pbuf; p > root; --p)
    p->f->adj.push_back (p);

  dfs_init (root);
  for (auto &x : ord)
    if (!x->root)
      for (auto y = x; y; y = y->aux)
        y->root = x;
  dfs (root);
  dfs_work (root);
  
  for (int i = 1; i <= n; ++i)
    {
      node *ptr = root; int64 ans = 0;
      for (int x = 0; x < SZ (S[i]); ++x)
        {
          int c = S[i][x] - 'a';
          ptr = ptr->c[c];
          ans += ptr->max;
          ptr->belong.push_back (i);
        }
      cout << ans << " ";
    }
  return 0; 
}
