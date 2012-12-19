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

const int maxn = 11000, maxK2 = 20;

int n, K, L;
int dist[maxn];
int f[1 << maxK2 | 50];
int a[maxn], b[maxn], x[maxn], cost[maxK2][maxK2];
int ctz[1 << maxK2 | 50];

void BFS (int x)
{
  fill (dist, dist + maxn, oo), dist[x] = 0;
  queue<int> Q; Q.push (x);
  for (; !Q.empty (); Q.pop ())
    {
      x = Q.front ();
      for (int i = 1; i <= L; ++i)
        {
          if (x + a[i] <= n && dist[x + a[i]] > dist[x] + 1)
            dist[x + a[i]] = dist[x] + 1, Q.push (x + a[i]);
          if (x - a[i] >= 1 && dist[x - a[i]] > dist[x] + 1)
            dist[x - a[i]] = dist[x] + 1, Q.push (x - a[i]);
        }
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("79D.in" , "r", stdin);
  freopen ("79D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  cin >> n >> K >> L; ++n;
  for (int i = 1, x; i <= K; ++i)
    cin >> x, a[x] = 1;

  VI ones;
  for (int i = 1; i <= n; ++i)
    if (a[i] != a[i - 1])
      ones.push_back (i);
  
  for (int i = 1; i <= L; ++i)
    cin >> a[i];
  for (int i = 0; i < sz_m (ones); ++i)
    {
      BFS (ones[i]);
      // cerr << ones[i] << endl;
      for (int j = 0; j < sz_m (ones); ++j)
        cost[i][j] = dist[ones[j]];
    }

  int z = sz_m (ones);
  memset (f, 0x3F, sizeof (f));
  f[(1 << z) - 1] = 0;
  for (int i = 0; i < z; ++i)
    ctz[1 << i] = i;
  
  for (int S = (1 << z) - 1; S; --S)
    {
      int w = ctz[S & -S], T = S & (S - 1);
      for (int a = 0; a < z; ++a)
        if (T >> a & 1)
          chkmin (f[T ^ (1 << a)], f[S] + cost[w][a]);
    }
  
  cout << (f[0] == oo ? -1 : f[0]) << endl;
  return 0; 
}
