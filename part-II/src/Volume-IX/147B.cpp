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

const int maxn = 302, maxlog = 10;

typedef double mat[maxn][maxn];

mat G[maxlog], U, V;
int n;

void matmul (mat A, mat B, mat C)
{
  mat t;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      {
        t[i][j] = max (A[i][j], B[i][j]);
        for (int k = 1; k <= n; ++k)
          t[i][j] = max (A[i][k] + B[k][j], t[i][j]);
      }
  memcpy (C, t, sizeof (mat));
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("147B.in" , "r", stdin);
  freopen ("147B.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int m;
  
  cin >> n >> m;
  memset (G[0], 0xCF, sizeof (mat));
  for (int i = 1; i <= n; ++i)
    G[0][i][i] = 0;
  for (int i = 1, s, t, wa, wb; i <= m; ++i)
    cin >> s >> t >> wa >> wb, G[0][s][t] = wa, G[0][t][s] = wb;

  int lmt;
  for (lmt = 0; 1 << lmt <= n; ++lmt)
    matmul (G[lmt], G[lmt], G[lmt + 1]);

  memset (U, 0xCF, sizeof (mat));
  for (int i = 1; i <= n; ++i)
    U[i][i] = 0;

  int ans = 0, now = 0;
  for (int i = lmt; i >= 0; --i)
    {
      matmul (U, G[i], V);

      bool ok = false;
      for (int x = 1; x <= n; ++x)
        if (V[x][x] > 0)
          ok = true;
      if (ok)
        ans = now | 1 << i;
      else
        now |= 1 << i, memcpy (U, V, sizeof (mat));
    }

  cout << ans << endl;
  return 0; 
}
