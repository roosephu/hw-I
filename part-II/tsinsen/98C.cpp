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

const int block = 21, blkcnt = 18;
real a, b, l, f[block + 5];

real func (real x)
{
  real y = sqrt (1 - x * x);
  return x * a + y * b - l * x * y;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("98C.in" , "r", stdin);
  freopen ("98C.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  real L = 0, R = 1; 
  
  cin >> a >> b >> l;

  cerr << setprecision (3);
  for (int _ = 0; _ <= 1000; ++_)
    {
      for (int i = block, j = 0; i >= 0; --i, ++j)
        f[j] = func ((i * L + j * R) / block);
      for (int i = 1; i <= block; ++i)
        f[i] += f[i - 1];

      int mid = blkcnt - 1; real now = f[mid];
      for (int i = blkcnt; i <= block; ++i)
        if (f[i] - f[i - blkcnt] < now)
          now = f[i] - f[i - blkcnt], mid = i;

      real bl = L, br = R; int x = mid - blkcnt + 1, y = mid;
      L = ((block - x) * bl + x * br) / block;
      R = ((block - y) * bl + y * br) / block;

      // cerr << L << " " << R << ": " << func (L) << ", " << func (R) << endl;
    }

  real ans = min (func ((L + R) / 2), (real)l);
  if (l <= max (a, b)) cout << min (min (a, b), l) << endl;
  else if (ans < 0) cout << "My poor head =(" << endl;
  else cout << setprecision (15) << ans << endl;
  return 0; 
}
