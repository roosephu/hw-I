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

const int maxn = 2200, maxbit = maxn * 2;

struct bit
{
  int v[maxn], maxval, minval;
  
  void modify (int t)
  {
    for (; t < maxn; t += t & -t)
      ++v[t];
  }

  int query (int &T, bool b)
  {
    T = min (maxval, max (T, minval)) - b;
    int x = v[T], t = T;
    for (; t &= t - 1; x += v[t]);
    return x;
  }

  int empty (int L, int R)
  {
    int count = query (R, 0) - query (L, 1);
    return count != R - L;
  }

  void update (int val)
  {
    chkmax (maxval, val);
    chkmin (minval, val);
  }

  bit () {minval = oo; }
};

bit add[maxbit], sub[maxbit];
bool occupied[maxn][maxn];
int n, m;

bool occupy (int x, int y)
{
  if (x <= 0 || x > n || y <= 0 || y > m || occupied[x][y]) return false;
  occupied[x][y] = true;
  add[x + y].modify (x);
  sub[x + m - y].modify (x);
  cout << x << " " << y << endl;
  // cerr << x << " " << y << endl;
  return true;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("200A.in" , "r", stdin);
  freopen ("200A.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int K, x, y;
  cin >> n >> m >> K;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      add[i + j].update (i), sub[i + m - j].update (i);
  
  for (; K--; )
    {
      cin >> x >> y;
      int r, b;
      for (r = b = 0; ; ++r)
        {
          if (!b && x + y - r >= 1 + 1) b += add[x + y - r].empty (x - r, x);
          if (!b && x + y + r <= n + m) b += add[x + y + r].empty (x, x + r);
          if (!b && x + m - y - r >= 1 + 0) b += sub[x + m - y - r].empty (x - r, x);
          if (!b && x + m - y + r <= n + m - 1) b += sub[x + m - y + r].empty (x, x + r);
          if (b) break;
        }

      for (int dx = -r, dy; dx <= r; ++dx)
        if (dy = r - abs (dx), occupy (x + dx, y - dy) || occupy (x + dx, y + dy))
          break;
    }

  return 0; 
}
