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

const int maxn = 1100;
const double eps = 1e-7;

struct crd {long double x, y, z; };

crd p[maxn];

crd operator^ (crd a, crd b) {return (crd){a.y * b.z - b.y * a.z, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}; }
long double operator* (crd a, crd b) {return a.x * b.x + a.y * b.y + a.z * b.z; }
int sgn (long double t) {return t > -eps ? t > eps : -1; }

bool in (crd hp, crd p)
{
  return sgn ((hp * p) / p.z) >= 0;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("67E.in" , "r", stdin);
  freopen ("67E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> p[i].x >> p[i].y, p[i].z = 1;
  if (p[1].x > p[2].x)
    {
      reverse (p + 1, p + 1 + n);
      rotate (p + 1, p + n - 1, p + 1 + n);
      for (int i = 1; i <= n; ++i)
        p[i].y *= -1;
    }
  crd L = p[1], R = p[2], AB = p[1] ^ p[2];
  
  for (int i = 2; i <= n; ++i)
    {
      crd a = p[i], b = p[i % n + 1], line = b ^ a, w = line ^ AB; bool b1 = false, b2 = false;
      if (!in (line, L)) L = w, b1 = true;
      if (!in (line, R)) R = w, b2 = true;
      if (b1 && b2) return cout << 0 << endl, 0;
    }

  int l = (int)(ceil (L.x / L.z)), r = (int)(floor (R.x / R.z));
  cout << max (r - l + 1, 0) << endl;
  return 0; 
}
