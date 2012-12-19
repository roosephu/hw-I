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

const int maxn = 110;

vector<PII> S[maxn];

int calc (vector<PII> &x, vector<PII> &y)
{
  int ret = 0, wx = 0, wy = 0, t = 0, lx = 0;

  for (vector<PII>::iterator px = x.begin (), py = y.begin (); ; )
    {
      int nt = min (px->Py, py->Py), nx = wx + (nt - t) * px->Px, ny = wy + (nt - t) * py->Px;
      if (nt == oo) break;
      if (lx < 0 && wx <= wy && nx > ny) ++ret;
      if (lx > 0 && wx >= wy && nx < ny) ++ret;
      if (nx != ny) lx = (nx > ny) - (nx < ny);
      t = nt, wx = nx, wy = ny;
      px->Py < py->Py ? ++px : ++py;
    }
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("43E.in" , "r", stdin);
  freopen ("43E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, s;
  
  cin >> n >> s;

  for (int i = 1, k; i <= n; ++i)
    {
      cin >> k; int lx = 0;
      for (int j = 1, v, t; j <= k; ++j)
        cin >> v >> t, S[i].push_back (MKP (v, lx += t));
      S[i].push_back (MKP (0, oo));
    }

  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j)
      ans += calc (S[i], S[j]);

  cout << ans << endl;
  return 0; 
}
