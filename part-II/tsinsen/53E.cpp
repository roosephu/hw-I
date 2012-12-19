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

const int maxn = 11, maxS = 1 << 10 | 50;

int G[maxn][maxn];
int f[maxS][maxS];
int pop[maxS], ctz[maxS];
int ans, n, m, k;

int dp (int S, int T)
{
  int &ret = f[S][T];
  if (ret != -1) return ret;
  if (pop[T] < 2) return 0;
  ret = 0;
  // for (int x = T, v; v = ctz[x & -x], x; x &= x - 1)
  int v = ctz[T & -T];
  for (int y = S & ~T, u; u = ctz[y & -y], y; y &= y - 1) // ensure that u is not a dead end
    if (G[v][u])
      ret += dp (S ^ (1 << v), T ^ (1 << v)) + dp (S ^ (1 << v), (T ^ (1 << v)) | 1 << u);
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("53E.in" , "r", stdin);
  freopen ("53E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n >> m >> k;
  memset (f, -1, sizeof (f));
  for (int i = 1, s, t; i <= m; ++i)
    cin >> s >> t, --s, --t, ++G[s][t], ++G[t][s], f[1 << s | 1 << t][1 << s | 1 << t] = 1;
  for (int i = 1; i <= 1 << n; ++i)
    pop[i] = pop[i >> 1] + (i & 1), ctz[i] = i & 1 ? 0 : (ctz[i >> 1] + 1);

  int ans = 0;
  for (int i = 0; i < 1 << n; ++i)
    if (pop[i] == k)
      ans += dp ((1 << n) - 1, i);
  // assert (ans % k == 0);
  cout << ans << endl;
  return 0; 
}
