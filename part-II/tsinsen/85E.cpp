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
typedef pair<int, PII> PIPII;

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

const int maxn = 5500, mod = 1000000007, maxXY = 11000;

int ufs[maxn], x[maxn], y[maxn], n, rel[maxn];
vector<int> R[maxXY];

int find (int t)
{
  if (ufs[t] != t)
    {
      int r = ufs[t];
      ufs[t]  = find (r);
      rel[t] ^= rel[r];
    }
  return ufs[t];
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("85E.in" , "r", stdin);
  freopen ("85E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> x[i] >> y[i];

  int cnt = n, ans = 0;
  for (int i = 1; i <= n; ++i)
    ufs[i] = i, rel[i] = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      R[abs (x[i] - x[j]) + abs (y[i] - y[j])].push_back (i << 16 | j);

  for (ans = 10000; ans >= 0; --ans)
    {
      int bak = cnt;
      foreach (it, R[ans])
        {
          int i = *it >> 16, j = *it & 65535, x = find (i), y = find (j);
          // cerr << i << " " << j << endl;
          if (x != y)
            ufs[x] = y, rel[x] ^= rel[j] ^ rel[i] ^ 1, --cnt;
          else if (rel[i] == rel[j])
            return cout << ans << endl << fpm (2, bak, mod) << endl, 0;
        }
    }

  cout << 0 << endl << fpm (2, cnt, mod) << endl;
  return 0; 
}
