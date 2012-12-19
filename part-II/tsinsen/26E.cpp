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
#define it_m(x) (x).begin (), (x).end ()

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef set<int> SI;
typedef pair<int, int> PII;

int64 fpm (int64 b, int64 e, int64 m) { int64 t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }
template<class T> inline bool chkmin (T &a, T b) {return a < b ? a = b, true : false;}
template<class T> inline bool chkmax (T &a, T b) {return a > b ? a = b, true : false;}
template<class T> inline T sqr (T x) {return x * x;}

template<class edge> struct Graph
{
  vector<vector<edge> > adj;
  Graph (int n) {adj.clear (); adj.resize (n + 5);}
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

const int maxn = 100;

int c[maxn];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("26E.in" , "r", stdin);
  freopen ("26E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, w, tot = 0, x = 0;
  
  cin >> n >> w;
  for (int i = 1; i <= n; ++i)
    cin >> c[i], tot += c[i], c[i] == 1 ? x = i : 0;
  if (w <= 0 || w > tot || (w == 1 && !x))
    return cout << "No" << endl, 0;
  if (n == 1)
    {
      if (w != c[1]) return cout << "No" << endl, 0;
      cout << "Yes" << endl;
      for (int i = 1; i <= c[1] * 2; ++i)
        cout << 1 << " ";
      cout << endl;
      return 0;
    }

  cout << "Yes" << endl;

  int waste = tot - w;
  if (!x) x = 1;
  if (c[x] != 1)
    {
      int t = min (waste, c[x] - 1), y = (1 + (x == 1));
      cout << y << " ";
      for (int i = 1; i <= t; ++i)
        cout << x << " " << x << " ";
      cout << y << " ";
      waste -= t, c[x] -= t, --c[y];
    }

  cout << x << " ";
  // cerr << waste << endl;
  for (int i = 1; i <= n && waste; ++i)
    if (i != x)
      for (; c[i] && waste; --c[i])
        cout << i << " " << i << " ", --waste;
  cout << x << " ", --c[x];
  for (int i = 1; i <= n; ++i)
    for (; c[i]; --c[i])
      cout << i << " " << i << " ";
  return 0; 
}
