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
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

const int maxn = 1100;

typedef int arr32[maxn];

arr32 col, row, vrow, vcol;
int noans, mod;

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("40E.in" , "r", stdin);
  freopen ("40E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, K;
  
  cin >> n >> m >> K;
  for (int i = 1; i <= n; ++i)
    row[i] = m, vrow[i] = 1;
  for (int j = 1; j <= m; ++j)
    col[j] = n, vcol[j] = 1;

  for (int i = 1, a, b, c; i <= K; ++i)
    cin >> a >> b >> c, --row[a], --col[b], vrow[a] *= c, vcol[b] *= c;
  int unx = 0;
  if (K < n)
    {
      for (int i = 1; i <= n; ++i)
        if (row[i])
          unx += row[i] - 1;
        else if (vrow[i] != -1)
          noans = 1;
      unx -= m - 1;
    }
  else
    {
      for (int j = 1; j <= m; ++j)
        if (col[j])
          unx += col[j] - 1;
        else if (vcol[j] != -1)
          noans = 1;
      unx -= n - 1;
    }

  cin >> mod;
  if (noans || (n & 1) != (m & 1)) cout << 0 << endl;
  else cout << fpm (2, unx, mod) << endl;
  return 0; 
}
