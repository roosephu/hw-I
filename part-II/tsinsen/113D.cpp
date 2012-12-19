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
typedef unordered_map<int, int> UMII;
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

const int maxn = 24;
const real eps = 1e-8;

real U[maxn * maxn][maxn * maxn + maxn], *ptr[maxn * maxn + maxn];
real G[maxn][maxn], P[maxn];
int deg[maxn];

void Gauss (int n, int m)
{
  for (int i = 0; i < n; ++i)
    ptr[i] = U[i];
  for (int i = 0, j, k; i < n; ++i)
    {
      for (j = i; j < n; ++j)
        if (abs (ptr[j][i]) >= eps)
          break;
      assert (j < n);
      swap (ptr[i], ptr[j]);
      for (j = n - 1; j > i; --j)
        for (k = m - 1; k >= i; --k)
          ptr[j][k] -= ptr[i][k] * ptr[j][i] / ptr[i][i];
    }
  for (int i = n - 1; i >= 0; --i)
    for (int j = m - 1; j >= n; --j)
      {
        ptr[i][j] /= ptr[i][i];
        for (int k = 0; k < i; ++k)
          ptr[k][j] -= ptr[k][i] * ptr[i][j];
      }
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("113D.in" , "r", stdin);
  freopen ("113D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, a, b;

  vector<PII> vec;
  cin >> n >> m >> a >> b; cout << setprecision (15);
  if (a == b)
    {
      for (int i = 1; i <= n; ++i)
        cout << (i == a) << endl;
      return 0;
    }
  for (int i = 1, s, t; i <= m; ++i)
    cin >> s >> t, G[s][t] = G[t][s] = 1, ++deg[s], ++deg[t];
  for (int i = 1; i <= n; ++i)
    cin >> P[i];
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (i != j)
        G[i][j] *= (1 - P[i]) / deg[i];
      else
        G[i][j] = P[i];
    
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      vec.push_back (MKP (i, j));

  int T = sz_m (vec);
  for (int i = 0; i < T; ++i)
    for (int j = 0; j < T; ++j)
      {
        PII &x = vec[i], &y = vec[j];
        U[i][j] = G[x.Px][y.Px] * G[x.Py][y.Py] + G[x.Py][y.Px] * G[x.Px][y.Py];
      }
  for (int z = 0; z < T; ++z)
    {
      PII &x = vec[z];
      U[z][z] -= 1;
      for (int i = 1; i <= n; ++i)
        U[z][i + T - 1] -= G[x.Px][i] * G[x.Py][i];
    }
  Gauss (T, T + n);

  if (a > b) swap (a, b);
  for (int i = 0; i < T; ++i)
    if (vec[i] == MKP (a, b))
      {
        for (int j = 0; j < n; ++j)
          cout << U[i][T + j] << " ";
        break;
      }

  return 0; 
}
