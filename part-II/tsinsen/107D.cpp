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

const int maxC = 30, maxS = 125, mod = 12345;

typedef int mat[maxS][maxS];

int prod[maxC];
set<int> S[maxC];
mat U, V;
int m;

void matmul (mat A, mat B, mat C)
{
  mat t;
  memset (t, 0, sizeof (t));
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      for (int k = 0; k < m; ++k)
        t[i][j] += A[i][k] * B[k][j] % mod;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      C[i][j] = t[i][j] % mod;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("107D.in" , "r", stdin);
  freopen ("107D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int64 n; int T; char c;
  
  cin >> n >> T;
  for (int i = 0; i <= 26; ++i)
    prod[i] = 1;
  for (int i = 1, t; i <= T; ++i)
    {
      cin >> c >> t;
      prod[c - 'A' + 1] *= t;
      S[c - 'A'].insert (t);
    }
  for (int i = 1; i <= 26; ++i)
    prod[i] *= prod[i - 1];
  m = prod[26];

  memset (U, 0, sizeof (U));
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < 26; ++j)
      {
        if (S[j].empty ()) continue;
        if (i % prod[j + 1] / prod[j] != prod[j + 1] / prod[j] - 1)
          ++U[i][i + prod[j]];
        else
          ++U[i][i + prod[j] - prod[j + 1]];
      }

  for (int i = 0; i < m; ++i)
    V[i][i] = 1;
  for (; n; n >>= 1, matmul (U, U, U))
    n & 1 ? matmul (V, U, V), 0 : 0;
  
  int ans = 0;
  for (int i = 0; i < m; ++i)
    {
      bool valid = true;
      for (int j = 0; j < 26; ++j)
        {
          if (S[j].empty ()) continue;
          bool b = false; int v = i % prod[j + 1] / prod[j];
          for (auto &x : S[j])
            if (v % x == 0)
              b = true;
          valid &= b;
        }
      if (valid) ans += V[0][i];
    }

  cout << ans % mod << endl;
  return 0; 
}
