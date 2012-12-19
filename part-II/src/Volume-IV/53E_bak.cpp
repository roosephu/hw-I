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
#define cvar(x) cerr << "[" << #x << ": " << x << "]"
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

const int maxn = 11;

double M[maxn][maxn];
int G[maxn][maxn], label[maxn];
bool o[maxn];
int ans, n, m, k;

int gauss (int n)
{
  double ret = 1;
  for (int i = 1, j, k; i <= n; ++i)
    {
      for (j = i; j <= n; ++j)
        if (fabs (M[i][j]) > 1e-6)
          break;
      if (j > n) return 0;
      for (k = 1; k <= n; ++k)
        swap (M[i][k], M[j][k]);
      ret *= M[i][i];
      for (j = n; j > i; --j)
        for (k = n; k >= i; --k)
          M[j][k] -= M[j][i] * M[i][k] / M[i][i];
    }
  return (int)(fabs (ret) + 0.5);
}

void update ()
{
  int count = 1;
  for (int i = 1; i <= n; ++i)
    if (o[i])
      {
        int t = 0;
        for (int j = 1; j <= n; ++j)
          if (!o[j])
            t += G[i][j];
        count *= t;
      }
  for (int i = 1, j = 0; i <= n; ++i)
    if (!o[i])
      label[i] = ++j;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (!o[i] && !o[j])
        M[label[i]][label[j]] = G[i][j];
  for (int i = 1; i <= n - k; ++i)
    for (int j = 1; j <= n - k; ++j)
      if (i != j)
        M[i][i] -= M[i][j];
  ans += count * gauss (n - k - 1);
}

void dfs (int d, int x)
{
  if (d < x) return ;
  if (d == 0) return update ();
  dfs (d - 1, x    );
  o[d] = true;
  dfs (d - 1, x - 1);
  o[d] = false;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("53E.in" , "r", stdin);
  freopen ("53E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n >> m >> k;
  for (int i = 1, s, t; i <= m; ++i)
    cin >> s >> t, ++G[s][t], ++G[t][s];
  dfs (n, k);
  cout << ans << endl;
  return 0; 
}
  // for (int x = S & (S - 1), y; y = x ^ S, x; x = (x - 1) & S)
  //   if ((pop[x] != 1 || !((T & x) >> ctz[x] & 1)) && (pop[y] != 1 || !((T & y) >> ctz[y] & 1)))
  //     for (int _x = x, u, Tx = T & x; u = ctz[_x & -_x], _x; _x -= 1 << u)
  //       for (int _y = y, v, Ty = T & y; v = ctz[_y & -_y], _y; _y -= 1 << v)
  //         if (G[u][v])
  //           {
  //             ret += dp (x, Tx) * dp (y, Ty);
  //             if (Tx >> u & 1)
  //               ret += dp (x, Tx ^ (1 << u)) * dp (y, Ty);
  //             if (Ty >> v & 1)
  //               ret += dp (x, Tx) * dp (y, Ty ^ (1 << u));
  //             if ((Tx >> u & 1) && (Ty >> v & 1))
  //               ret += dp (x, Tx ^ (1 << u)) * dp (y, Ty ^ (1 << u));
  //           }
  // assert 
