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

struct node
{
  node *c[2];
  int min;
};

const int maxn = 110000, maxbuf = maxn * 31, maxbit = 31;

node buf[maxbuf], *stptr = buf, *root;
int64 len[maxn], dest[maxn];
int n, Q, nr; int64 G, R, P;

void insert (node *&t, int key, int &val, int d = maxbit - 1)
{
  if (!t) t = ++stptr; t->min = val;
  if (d >= 0) insert (t->c[key >> d & 1], key, val, d - 1);
}

void query (node *t, int L, int R, int x = 0, int d = maxbit)
{
  if (!t || L >= R || x < (L >> d) || (R >> d) < x) return ;
  if (!d || ((L >> d) != x && (R >> d) != x)) return (void)(nr = min (nr, t->min));
  query (t->c[0], L, R, x << 1    , d - 1);
  query (t->c[1], L, R, x << 1 | 1, d - 1);
}

int64 next_red (int x, int t)     // time t at pos x
{
  nr = oo; int w = (len[x] + P - t % P) % P;
  if ((w + G) % P <= w) query (root, (w + G) % P, w);
  else query (root, (w + G) % P, P), query (root, -1, w);
  // cerr << nr << endl;
  if (nr >= n) return len[n] - len[x];
  return dest[nr] + len[nr] - len[x] + (P + w - len[nr] % P) % P;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("187D.in" , "r", stdin);
  freopen ("187D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  cin >> n >> G >> R; ++n, P = G + R;
  for (int i = 1; i <= n; ++i)
    cin >> len[i], len[i] += len[i - 1];
  for (int i = n - 1; i >= 0; --i)
    {
      dest[i] = next_red (i, 0);
      if (i) insert (root, len[i] % P, i);
    }
  cin >> Q;
  for (int t; Q--; )
    cin >> t, cout << t + next_red (0, t) << endl;
  return 0; 
}
