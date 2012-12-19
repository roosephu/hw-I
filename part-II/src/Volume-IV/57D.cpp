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

const int maxn = 1100;

char S[maxn][maxn];
int col[maxn], row[maxn], lx[maxn];
double ans = 0;

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("57D.in" , "r", stdin);
  freopen ("57D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, tot; 
  
  cin >> n >> m, tot = n * m;
  for (int i = 1; i <= n; ++i)
    cin >> (S[i] + 1);
  for (int i = 1; i <= n; ++i)
    row[i] = m;
  for (int j = 1; j <= m; ++j)
    col[j] = n;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (S[i][j] == 'X')
        --row[i], --col[j], --tot;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      ans += row[i] * row[j] * abs (i - j);
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= m; ++j)
      ans += col[i] * col[j] * abs (i - j);

  memset (lx, 0, sizeof (lx));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (S[i][j] == 'X')
        ans += 2 * (n - i) * (lx[j] = lx[j - 1] + lx[j + 1] + i - 1);
  memset (lx, 0, sizeof (lx));
  for (int i = n; i; --i)
    for (int j = 1; j <= m; ++j)
      if (S[i][j] == 'X')
        ans += 2 * (i - 1) * (lx[j] = lx[j - 1] + lx[j + 1] + n - i);
  memset (lx, 0, sizeof (lx));
  for (int j = 1; j <= m; ++j)
    for (int i = 1; i <= n; ++i)
      if (S[i][j] == 'X')
        ans += 2 * (m - j) * (lx[i] = lx[i + 1] + lx[i - 1] + j - 1);
  memset (lx, 0, sizeof (lx));
  for (int j = m; j; --j)
    for (int i = 1; i <= n; ++i)
      if (S[i][j] == 'X')
        ans += 2 * (j - 1) * (lx[i] = lx[i + 1] + lx[i - 1] + m - j);
  
  cout << setprecision (15) << ans / tot / tot << endl;
  return 0; 
}
