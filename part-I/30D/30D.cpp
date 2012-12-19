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

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef set<int> SI;
typedef pair<int, int> PII;

int64 fpm (int64 b, int64 e, int64 m) { int64 t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }
template<class T> inline bool chkmin (T &a, T b) {return a < b ? a = b, true : false;}
template<class T> inline bool chkmax (T &a, T b) {return a > b ? a = b, true : false;}
template<class T> inline T sqr (T x) {return x * x;}

template<class edge> struct Graph
{
  vector<vector<edge> > adj;
  Graph (int n) {adj.clear (); adj.resize (n + 5);}
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

const int maxn = 110000;

int x[maxn], y, n, k;

double dist (int L, int R)
{
  if (L > R) return 0;
  return min (hypot (y, x[1 + n] - x[L]), hypot (y, x[1 + n] - x[R])) + x[R] - x[L];
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("30D.in" , "r", stdin);
  freopen ("30D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  cin >> n >> k;
  for (int i = 1; i <= n + 1; ++i)
    cin >> x[i];
  cin >> y;
  cout << setprecision (15);

  int bak = x[k], xw = x[n + 1];
  sort (x + 1, x + 1 + n);

  if (k > n) return cout << dist (1, n) << endl, 0;
  
  k = lower_bound (x + 1, x + 1 + n, bak) - x;

  double ans = hypot (x[k] - xw, y) + dist (1, n);
  for (int i = 1; i <= n; ++i)
    {
      ans = min (ans, fabs (x[k] - x[n]) + fabs (x[n] - x[i]) + dist (1, min (i, k) - 1) + hypot (x[i] - xw, y));
      ans = min (ans, fabs (x[k] - x[1]) + fabs (x[1] - x[i]) + dist (max (i, k) + 1, n) + hypot (x[i] - xw, y));
      ans = min (ans, fabs (x[k] - x[i]) + fabs (x[i] - x[n]) + dist (1, min (i, k) - 1) + hypot (x[n] - xw, y));
      ans = min (ans, fabs (x[k] - x[i]) + fabs (x[i] - x[1]) + dist (max (i, k) + 1, n) + hypot (x[1] - xw, y));
    }
  cout << ans << endl;
  return 0; 
}
