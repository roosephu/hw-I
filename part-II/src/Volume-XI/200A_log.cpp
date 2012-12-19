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

bool occupied[maxn][maxn];
int bit[maxbit][maxbit];
int n, m;

void modify (int x, int y, int v)
{
  for (int a = x; a < maxbit; a += a & -a)
    for (int b = y; b < maxbit; b += b & -b)
      bit[a][b] += v;
}

bool occupy (int x, int y)
{
  if (x <= 0 || x > n || y <= 0 || y > m || occupied[x][y]) return false;
  occupied[x][y] = true;
  modify (x + y - 1, x + m - y, -1);
  cout << x << " " << y << endl;
  // cerr << x << " " << y << endl;
  return true;
}

int bit_query (int x, int y)
{
  int ret = 0; x = max (0, min (x, maxbit - 1)), y = max (0, min (y, maxbit - 1));
  for (int a = x; a; a &= a - 1)
    for (int b = y; b; b &= b - 1)
      ret += bit[a][b];
  return ret;
}

int query (int x, int y, int r)
{
  int a = x + y - 1, b = x + m - y;
  return bit_query (a + r, b + r) + bit_query (a - r - 1, b - r - 1) - bit_query (a + r, b - r - 1) - bit_query (a - r - 1, b + r);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("200A_lyx.in" , "r", stdin);
  freopen ("200A.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int K, x, y;
  cin >> n >> m >> K;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      bit[i + j - 1][i + m - j] = 1;
  for (int i = 1; i < maxbit; ++i)
    for (int j = 1; j < maxbit; ++j)
      {
        int x = i + (i & -i), y = j + (j & -j);
        if (x < maxbit) bit[x][j] += bit[i][j];
        if (y < maxbit) bit[i][y] += bit[i][j];
        if (x < maxbit && y < maxbit) bit[x][y] -= bit[i][j];
      }
  
  for (int i = 1; i <= K; ++i)
    {
      cin >> x >> y;
      int r, L = 0, R = n + m;
      for (; r = (L + R) >> 1, L < R; )
        query (x, y, r) ? (R = r) : (L = r + 1);

      for (int dx = -r, dy; dx <= r; ++dx)
        if (dy = r - abs (dx), occupy (x + dx, y - dy) || occupy (x + dx, y + dy))
          break;
    }

  return 0; 
}
