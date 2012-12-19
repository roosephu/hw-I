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

const int maxn = 440;

int c[maxn], s[maxn], ans, n;

void update (int v, int pos)
{
  int bak = v;
  for (int i = 1, w = bak; i <= n; ++i)
    s[i] = w / c[i], w %= c[i];
  int best = accumulate (s + 1, s + pos + 1, 0) + 1, val = v + c[pos];
  for (int i = pos + 1; i <= n; ++i)
    val -= s[i] * c[i];
  // if ((s[pos] + 1) * c[pos] > c[pos - 1]) return ;

  // cerr << val << endl;
  for (int i = 1, w = val; i <= n; ++i)
    s[i] = w / c[i], w %= c[i];
  int now = accumulate (s + 1, s + n + 1, 0);
  if (now > best) ans = min (ans, val);
  // cerr << bak << ": " << now << " " << best << endl;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("10E.in" , "r", stdin);
  freopen ("10E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> c[i];
  ans = oo;
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      update (c[i] - 1, j);
  
  if (ans == oo) cout << -1 << endl;
  else cout << ans << endl;
  return 0; 
}
