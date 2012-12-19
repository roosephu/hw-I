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

const int maxM = 14, mod = 1000000007;

typedef int64 mat[maxM][maxM];

mat U, V;
int mul[maxM];

void matmul (mat A, mat B, mat C)
{
  mat t;
  memset (t, 0, sizeof (t));
  for (int i = 0; i < maxM; ++i)
    for (int j = 0; j < maxM; ++j)
      for (int k = 0; k < maxM; ++k)
        t[i][j] += A[i][k] * B[k][j] % mod;
  for (int i = 0; i < maxM; ++i)
    for (int j = 0; j < maxM; ++j)
      C[i][j] = t[i][j] % mod;
}

void build_matrix ()
{
  vector<PII> vec; int ans = 13;
  
  memset (U, 0, sizeof (U));
  for (int i = -1; i < 4; ++i)
    vec.push_back (MKP (0, i + 1));
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      if ((i >> 1) != (j >> 1))
        vec.push_back (MKP (i + 1, j + 1));
  foreach (x, vec)
    foreach (y, vec)
    if (x->Py == y->Px && x->Px * x->Py * y->Py != 6)
      U[x - vec.begin ()][y - vec.begin ()] = 1;
  foreach (x, vec)
    mul[x - vec.begin ()] = 3 - ((x->Px != 4 && x->Py != 4 && x->Py) || (!x->Px));

  U[0][0] = 0, mul[0] = 4;
  for (int i = 0; i < ans; ++i)
    for (int j = 0; j < ans; ++j)
      U[i][ans] += U[i][j];
  U[ans][ans] = 1;

  // foreach (x, vec)
  //   cerr << x - vec.begin () << ": " << x->Px << " " << x->Py << " " << mul[x - vec.begin ()] << endl;
  // for (int i = 0; i < ans; ++i)
  //   for (int j = 0; j < ans; ++j)
  //     if (U[i][j])
  //       cerr << "mat: " << i << " " << j << endl;
  
  memset (V, 0, sizeof (V));
  V[0][0] = 1;
}

void matpow (int e)
{
  build_matrix ();
  for (; e; e >>= 1, matmul (U, U, U))
    e & 1 ? matmul (V, U, V) : (void)0;
}

int calc (int t)
{
  int64 ret = 0;
  matpow (t);
  ret += V[0][maxM - 1]; evar (ret);
  matpow ((t + 1) >> 1);
  // for (int i = 0; i < maxM - 1; ++i)
  //   ret += mul[i] * V[0][i];
  ret += V[0][maxM - 1];
  evar (ret);
  // ret >>= 1;
  ret = ret % mod * ((mod + 1) / 2) % mod;
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("93D.in" , "r", stdin);
  freopen ("93D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int L, R;
  
  cin >> L >> R;
  cout << (calc (R) + mod - calc (L - 1)) % mod << endl;
  // cerr << calc (R) << endl;

  return 0; 
}
