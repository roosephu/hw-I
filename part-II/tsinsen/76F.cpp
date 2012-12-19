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

const int maxn = 110000;

int x[maxn], t[maxn], f[maxn];

bool cmp (PII x, PII y) {return x.Px > y.Px || (x.Px == y.Px && x.Py < y.Py); }

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("76F.in" , "r", stdin);
  freopen ("76F.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, V;
  
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> x[i] >> t[i];
  cin >> V;

  vector<PII> val;
  for (int i = 1; i <= n; ++i)
    {
      int a = t[i] * V, b = x[i];
      val.push_back (MKP (a + b, a - b));
    }
  sort (iter (val), greater<PII>());

  int ans1 = 0, ans2 = 0;
  map<int, int> f;
  f[~0u >> 1] = 0;
  f[1 << 31] = 0;
  foreach (it, val)
    {
      int v = f.lower_bound (it->Py)->Py + 1;
      // cvar (it->Px), cvar (it->Py), evar (v);
      if (it->Px >= 0 && it->Py >= 0) chkmax (ans1, v);
      chkmax (ans2, v);

      map<int, int>::iterator p = f.upper_bound (it->Py), q;
      if (p != f.end () && p->Py >= v) continue;
      for (; (--p) != f.begin () && p->Py <= v; )
        q = p, --q, f.erase (p), p = q;
      f[it->Py] = v;
    }

  cout << ans1 << " " << ans2 << endl;
  return 0; 
}
