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

const int maxn = 330000;

struct node {
  PII val[2];
  int add;
};

node st[maxn * 2];
int prev[maxn], a[maxn], b[maxn];
int n;

node operator+ (node a, node b)
{
  int i = 0, j = 0, k = 0; node ret;
  for (; k < 2; ++k)
    {
      int x = min (a.val[i].Px, b.val[j].Px), y = 0;
      for (; i < 2 && a.val[i].Px == x; y += a.val[i].Py, ++i);
      for (; j < 2 && b.val[j].Px == x; y += b.val[j].Py, ++j);
      ret.val[k] = MKP (x, y);
    }
  return ret.add = 0, ret;
}

#define stpos(l,r) (((l) + (r) - 1) | ((l) != (r) - 1))
void st_build (int t, int L, int R)
{
  if (L + 1 == R)
    {
      st[t].val[0] = MKP (prev[R], 1);
      st[t].val[1] = MKP (oo, 1);
      st[t].add = 0;
      return;
    }
  int m = (L + R + 1) >> 1, lc = stpos (L, m), rc = stpos (m, R);
  if (L < m) st_build (lc, L, m);
  if (m < R) st_build (rc, m, R);
  st[t] = st[lc] + st[rc];
}

void put (node *t, int add)
{
  t->val[0].Px += add;
  t->val[1].Px += add;
  t->add       += add;
}

void st_modify (int t, int L, int R, int l, int r, int add)
{
  if (L <= l && r <= R) return put (st + t, add);
  int m = (l + r + 1) >> 1, lc = stpos (l, m), rc = stpos (m, r);
  if (st[t].add) put (st + lc, st[t].add), put (st + rc, st[t].add), st[t].add = 0;
  if (L < m) st_modify (lc, L, R, l, m, add);
  if (m < R) st_modify (rc, L, R, m, r, add);
  st[t] = st[lc] + st[rc];
}

void st_modify (int L, int R, int add)
{
  // cerr << "st_modify: ", cvar (L), cvar (R), evar (add);
  st_modify (stpos (0, n), L - 1, R, 0, n, add);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("193D.in" , "r", stdin);
  freopen ("193D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], b[a[i]] = i;
  for (int i = 1; i <= n; ++i)
    {
      int x = b[i], v = 1;
      if (x > 1 && a[x - 1] < a[x]) --v;
      if (x < n && a[x] > a[x + 1]) --v;
      prev[i] = prev[i - 1] + v;
    }
  // disp (a + 1, n);
  // disp (prev + 1, n);

  int64 ans = 0; node *root = st + stpos (0, n);
  st_build (stpos (0, n), 0, n);
  // cvar (root->val[0].Px), cvar (root->val[1].Px), evar (ans);
  for (int i = 1; i <= n; ++i)
    {
      for (int k = 0; k < 2 && root->val[k].Px <= 2; ++k)
        ans += root->val[k].Py;

      int x = b[i];
      if (x > 1 && a[x - 1] > a[x]) st_modify (a[x - 1], n, 1);
      if (x < n && a[x] < a[x + 1]) st_modify (a[x + 1], n, 1);
      if (i < n) st_modify (i + 1, n, -1);
      st_modify (i, i, oo);
      // cvar (root->val[0].Px), cvar (root->val[1].Px), 
      //   evar (ans);
    }

  cout << ans - n << endl;
  return 0; 
}
