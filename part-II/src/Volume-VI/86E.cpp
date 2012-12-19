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

const int maxk = 51;

typedef int64 mat[maxk];

int K;
mat x, y;
vector<int64> dvs;

void matmul (mat A, mat B, mat C)
{
  mat t, x;
  memcpy (x, A, sizeof (mat));
  memset (t, 0, sizeof (mat));
  for (int i = 0; i < K; ++i)
    for (int j = 0; j < K; ++j)
      t[j] ^= (int64)(B[i] >> j & 1) << i;
  memset (C, 0, sizeof (mat));
  for (int i = 0; i < K; ++i)
    for (int j = 0; j < K; ++j)
      C[i] |= (int64)__builtin_parityll (x[i] & t[j]) << j;
}

string bin (int64 x)
{
  string S;
  for (int i = 0; i < K; ++i)
    S += (char)('0' + (x >> i & 1));
  return S;
}

void print (mat x)
{
  for (int i = 0; i < K; ++i)
    cerr << bin (x[i]) << endl;
}

bool is_U (int64 B, int64 e)
{
  memset (x, 0, sizeof (mat));
  for (int i = 1; i < K; ++i)
    x[i] |= 1ll << (i - 1);
  for (int i = 0; i < K; ++i)
    x[i] |= (B >> i & 1) << (K - 1), y[i] = 1ll << i;
  // cerr << "x" << endl, print (x);
  for (; e; e >>= 1, matmul (x, x, x))
    e & 1 ? matmul (y, x, y) : (void)0;
  // cerr << "x" << endl, print (x), cerr << "y" << endl, print (y);
  for (int i = 0; i < K; ++i)
    if (y[i] != (1ll << i))
      return false;
  return true;
}

bool check (int64 B)
{
  // cerr << "## check: " << bin (B) << endl;

  int64 E = (1ll << K) - 1;
  if (!is_U (B, E)) return false;
  foreach (it, dvs)
    if (is_U (B, E / *it))
      return false;
  return true;
}

int Rbit () {return rand () & 1;}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("86E.in" , "r", stdin);
  freopen ("86E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int64 B = 0, cnt = 0, E;
  cin >> K, E = (1ll << K) - 1;
  for (int64 i = 2; i * i <= E; ++i)
    if (E % i == 0)
      for (dvs.push_back (i); E % i == 0; E /= i);
  if (E != 1) dvs.push_back (E);
  
  do
    {
      B = 0, ++cnt;
      for (int i = 0; i < K; ++i)
        B |= (int64)Rbit () << i;
      // B = 19;
    }
  while (!check (B));
  for (int i = K - 1; i >= 0; --i)
    cout << (B >> i & 1) << " ";
  cout << endl;
  for (int i = 0; i < K; ++i)
    cout << 1 << " ";
  cout << endl;

  cerr << cnt << endl << 1000.0 * clock () / CLOCKS_PER_SEC << endl;
  return 0; 
}
