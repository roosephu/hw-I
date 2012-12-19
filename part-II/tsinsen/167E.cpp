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

const int maxn = 660;

Graph<int> G;
int ideg[maxn], odeg[maxn], f[maxn], rep[maxn];
int64 ways[maxn][maxn];
bool reach[maxn];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("167E.in" , "r", stdin);
  freopen ("167E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, mod;
  
  cin >> n >> m >> mod; G.resize (n);
  for (int i = 1, s, t; i <= m; ++i)
    cin >> s >> t, G.add (s, t), ++odeg[s], ++ideg[t];
  
  vector<int> S, T;
  for (int i = 1; i <= n; ++i)
    {
      if (!ideg[i])
        S.push_back (i);
      if (!odeg[i])
        T.push_back (i);
    }

  for (int v = 0; v < SZ (S); ++v)
    {
      memset (reach, 0, sizeof (reach));
      queue<int> Q; Q.push (S[v]), reach[S[v]] = 1;
      
      for (int u; !Q.empty (); Q.pop ())
        for (auto &x : G[u = Q.front ()])
          if (!reach[x])
            reach[x] = true, Q.push (x);

      memset (ideg, 0, sizeof (ideg));
      for (int i = 1; i <= n; ++i)
        if (reach[i])
          for (auto &u : G[i])
            ++ideg[u];

      Q.push (S[v]);
      memset (f, 0, sizeof (f)), f[S[v]] = 1;
      for (int u; !Q.empty (); Q.pop ())
        for (auto &x : G[u = Q.front ()])
          if (reach[x])
            {
              (f[x] += f[u]) %= mod;
              if (--ideg[x] == 0) Q.push (x);
            }

      for (int u = 0; u < SZ (T); ++u)
        ways[u][v] = f[T[u]];
    }

  // now, we're to perform Gaussian Elimination
  // the answer is the determination of the matrix `ways'
  int K = SZ (S); int64 ans = 1;
  for (int i = 0; i < K; ++i)
    rep[i] = i;

  // for (int i = 0; i < K; ++i)
  //   {
  //     for (int j = 0; j < K; ++j)
  //       cerr << ways[i][j] << " ";
  //     cerr << endl;
  //   }
  
  for (int i = 0, j, k; i < K; ++i)
    {
      for (j = i; j < K; ++j)
        if (ways[j][i] != 0)
          break;
      for (k = 0; k < K; ++k)
        swap (ways[i][k], ways[j][k]);
      ans = ans * ways[i][i] % mod;
      swap (rep[i], rep[j]);
      
      int64 inv = fpm (ways[i][i], mod - 2, mod);
      for (j = i; j < K; ++j)
        ways[i][j] = ways[i][j] * inv % mod;
      for (j = K - 1; j > i; --j)
        for (k = K - 1; k > i; --k)
          ways[j][k] = (ways[j][k] + mod - ways[j][i] * ways[i][k] % mod) % mod;
    }
  for (int i = 0; i < K; ++i)
    for (int j = i + 1; j < K; ++j)
      if (rep[i] > rep[j])
        ans = (mod - ans) % mod;

  cout << ans << endl;
  return 0; 
}
