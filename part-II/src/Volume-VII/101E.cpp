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
typedef long double real;
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
  void add (int s, edge e){adj[s].push_back (e);}
  void del (int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
  int deg (int v) {return adj[v].size (); }
  vector<edge>& operator [](int t) {return adj[t];}
};

const int maxn = 22000;

int n, m, p;
int a[maxn], b[maxn];
int64 f[maxn], g[maxn];

int func (int x, int y)
{
  if (a[x] + b[y] < p) return a[x] + b[y];
  return a[x] + b[y] - p;
}

void solve (int lx, int ly, int rx, int ry)
{
  // cerr << "solve: " << lx << " " << ly << " " << rx << " " << ry << endl;
  if (lx == rx)
    {
      for (int i = ly; i < ry; ++i)
        cout << "S";
      return ;
    }
  
  int mx = (lx + rx) >> 1;
  for (int j = ly; j <= ry; ++j)
    f[j] = g[j] = 0;
  for (int i = lx; i <= mx; ++i)
    for (int j = ly; j <= ry; ++j)
      f[j] = max (f[j], j != ly ? f[j - 1] : 0) + func (i, j);
  for (int i = rx; i > mx; --i)
    for (int j = ry; j >= ly; --j)
      g[j] = max (g[j], j != ry ? g[j + 1] : 0) + func (i, j);

  int64 ans = -1; int split = 0;
  for (int j = ly; j <= ry; ++j)
    if (f[j] + g[j] > ans)
      ans = f[j] + g[j], split = j;
  // cvar (ans), evar (split);

  if (lx == 1 && rx == n && ly == 1 && ry == m) cout << ans << endl;
  solve (lx    , ly, mx, split);
  cout << "C";
  solve (mx + 1, split, rx, ry);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("101E.in" , "r", stdin);
  freopen ("101E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n >> m >> p;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], a[i] %= p;
  for (int i = 1; i <= m; ++i)
    cin >> b[i], b[i] %= p;
  if (n == 1)
    {
      int64 ans = 0;
      for (int j = 1; j <= m; ++j)
        ans += func (1, j);
      cout << ans << endl;
    }
  
  solve (1, 1, n, m);  
  return 0; 
}
