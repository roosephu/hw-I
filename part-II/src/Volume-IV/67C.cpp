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

const int maxn = 4400;

int f[maxn][maxn];
int ls[maxn][26], lt[maxn][26];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("67C.in" , "r", stdin);
  freopen ("67C.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int Ti, Td, Tr, Te; string A, B;
  
  cin >> Ti >> Td >> Tr >> Te >> A >> B;
  int n = sz_m (A), m = sz_m (B);
  memset (f, 0x3F, sizeof (f)), f[0][0] = 0;

  for (int c = 0; c < 26; ++c)
    ls[n - 1][c] = n, lt[m - 1][c] = m;
  for (int i = n - 2; i >= 0; --i)
    {
      memcpy (ls[i], ls[i + 1], sizeof (ls[i]));
      ls[i][A[i + 1] - 'a'] = i + 1;
    }
  for (int j = m - 2; j >= 0; --j)
    {
      memcpy (lt[j], lt[j + 1], sizeof (lt[j]));
      lt[j][B[j + 1] - 'a'] = j + 1;
    }
  
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= m; ++j)
      {
        if (j < m)
          chkmin (f[i][j + 1], f[i][j] + Ti);
        if (i < n)
          chkmin (f[i + 1][j], f[i][j] + Td);
        if (i < n && j < m)
          {
            chkmin (f[i + 1][j + 1], f[i][j] + (A[i] != B[j]) * Tr);
            int cs = A[i] - 'a', ct = B[j] - 'a', a, b;
            if ((a = ls[i][ct]) != n && (b = lt[j][cs]) != m)
              chkmin (f[a + 1][b + 1], f[i][j] + Te + (a - i - 1) * Td + (b - j - 1) * Ti);
          }
      }
  cout << f[n][m] << endl;
  return 0; 
}
