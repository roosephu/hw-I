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

const int maxn = 262144, prime = 1000000007;

struct node { int size; uint64 hash; };

node st[maxn << 1];
uint64 P[maxn];
int pos[maxn];

void update (node *t, node *l, node *r)
{
  t->size = l->size + r->size;
  t->hash = l->hash + r->hash * P[l->size];
}

void modify (int t, node x)
{
  for (st[t += maxn] = x; t >>= 1; )
    update (st + t, st + (t << 1), st + (t << 1 | 1));
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("213E.in" , "r", stdin);
  freopen ("213E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, ans = 0; uint64 A = 0, delta = 0;
  
  cin >> n >> m;
  if (n > m) return cout << 0 << endl, 0;

  P[0] = 1;
  for (int i = 1; i < maxn; ++i)
    P[i] = P[i - 1] * prime;
  
  for (int i = 0, a; i < n; ++i)
    cin >> a, A += a * P[i], delta += P[i];
  
  for (int i = 1, b; i <= m; ++i)
    cin >> b, pos[b] = i;
  for (int i = 1; i <= n; ++i)
    modify (pos[i], (node){1, (uint64)i});
  for (int i = n + 1; i <= m + 1; ++i)
    {
      if (st[1].hash == A) ++ans;
      A += delta;
      modify (pos[i - n], (node){0, (uint64)0});
      modify (pos[i    ], (node){1, (uint64)i});
    }

  cout << ans << endl;
  return 0; 
}
