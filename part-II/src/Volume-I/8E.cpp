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

const int maxn = 55;

int n, h; int64 k;
int s[maxn];

int64 calc (int64 x)
{
  int64 ret = (x + 1) * ((1ll << h) - x);
  if (n & 1) ret = ret * 2 - x - 1;
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("8E.in" , "r", stdin);
  freopen ("8E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n >> k; k += 1; h = n >> 1;
  int64 L = 0, R = (1ll << h) - 1, mid;
  for (; mid = (L + R) >> 1, L < R; )
    calc (mid) >= k ? (R = mid) : (L = mid + 1);
  if (calc (mid) < k) return cout << -1 << endl, 0;
  for (int i = h - 1; i >= 0; --i)
    cout << ((L >> i) & 1);

  L = mid, R = (1 << h) - 1 - mid;
  k -= calc (mid - 1);
  if (n & 1)
    {
      if (k > (1 << h) - 2 * mid)
        cout << 1, k -= (1 << h) - 2 * mid, --R;
      else
        cout << 0;
    }
  
  // k += mid;
  for (int i = 0; i < h; ++i)
    {
      if ((R >> 1) - ((L + 1) >> 1) + 1 >= k)
        cout << 0, L = (L + 1) >> 1, R >>= 1;
      else
        cout << 1, k -= (R >> 1) - ((L + 1) >> 1) + 1, L = L >> 1, R = (R - 1) >> 1;
      // L = (L + 1) >> 1, R >>= 1;
    }
  cout << endl;
  return 0; 
}
