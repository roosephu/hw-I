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

int cnt = 0;

struct disjoint_set
{
  vector<int> f;

  // int find (int t) {return ++cnt, f[t] != -1 ? f[t] = find (f[t]) : t; }
  int find (int t)
  {
    if (f[t] == -1) return t;
    if (f[f[t]] == -1) return f[t];
    int r;
    for (r = t; f[r] != -1; r = f[r]);
    for (int x; t != r; x = f[t], f[t] = r, t = x);
    return r;
  }
  
  void unite (int s, int t)
  {
    int x = find (s), y = find (t);
    if (x != y) f[x] = y;
  }
};

int n, m;
disjoint_set U[maxn], D[maxn];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("200A.in" , "r", stdin);
  freopen ("200A.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int K, x, y; bool swaped = false;
  cin >> n >> m >> K;
  if (n > m) swap (n, m), swaped = true;

  for (int i = 1; i <= n; ++i)
    {
      U[i].f.resize (m + 2), fill (ALL (U[i].f), -1);
      D[i].f.resize (m + 2), fill (ALL (D[i].f), -1);
    }
  
  for (int Z = 1; Z <= K; ++Z)
    {
      cin >> x >> y; if (swaped) swap (x, y);
      pair<int, pair<int, int>> ans = MKP (oo, MKP (0, 0));

      auto update = [&x, &y, &ans, &swaped](int wx, int wy)
        {
          if (wy < 1 || wy > m) return ;
          if (swaped)
            chkmin (ans, MKP (abs (wx - x) + abs (wy - y), MKP (wy, wx)));
          else
            chkmin (ans, MKP (abs (wx - x) + abs (wy - y), MKP (wx, wy)));
        };

      int i = 0;
      for (i = 0; i <= ans.Px; ++i)
        {
          bool b = true;
          if (x + i <= n) update (x + i, U[x + i].find (y)), update (x + i, D[x + i].find (y)), b = false;
          if (x - i >= 1) update (x - i, U[x - i].find (y)), update (x - i, D[x - i].find (y)), b = false;
          if (b) break;
        }

      // cerr << Z << " " << i << endl;
      
      x = ans.Py.Px, y = ans.Py.Py;
      cout << x << " " << y << endl;
      if (swaped) swap (x, y);
      U[x].unite (y, y + 1), D[x].unite (y, y - 1);

      // cerr << Z << " " << i << " " << cnt << endl;
    }

  return 0; 
}
