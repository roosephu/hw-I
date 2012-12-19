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
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

const int maxn = 1100;

typedef int arr32[maxn];

arr32 col, row, xcol, xrow, vcol, vrow;
int v[maxn][maxn], noans, mod;

void setval (int x, int y, int c)
{
  if (v[x][y] != -1)
    {
      if (v[x][y] != c)
        noans = true;
      return ;
    }
  int vx, vy, xr, xc; bool tx, ty;
  tx = --row[x] == 1, xr = xrow[x] ^= y, vx = vrow[x] ^= c;
  ty = --col[y] == 1, xc = xcol[y] ^= x, vy = vcol[y] ^= c;
  v[x][y] = c;
  if (tx) setval (x, xr, vx);
  if (ty) setval (xc, y, vy);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("40E.in" , "r", stdin);
  freopen ("40E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, K;
  
  cin >> n >> m >> K;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      xrow[i] ^= j, xcol[j] ^= i;
  for (int i = 1; i <= n; ++i)
    vrow[i] = 1, row[i] = m;
  for (int j = 1; j <= m; ++j)
    vcol[j] = 1, col[j] = n;

  memset (v, -1, sizeof (v));
  for (int i = 1, a, b, c; i <= K; ++i)
    cin >> a >> b >> c, setval (a, b, !~c);

  int equ = 0, unx = 0;
  for (int i = 1; i <= n; ++i)
    if (row[i])
      ++equ;
  for (int j = 1; j <= m; ++j)
    if (col[j])
      ++equ;
  // for (int i = 1; i <= n; ++i)
  //   for (int j = 1; j <= m; ++j)
  //     if (v[i][j] == -1)
  //       ++unx;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (v[i][j] == -1)
        setval (i, j, 0), ++unx;

  cin >> mod;
  if (noans) cout << 0 << endl;
  else cout << fpm (2, unx, mod) << endl;
  return 0; 
}
