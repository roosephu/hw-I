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

struct crd
{
  real x, y, z;
  void read () {cin >> x >> y >> z; }
  void out () {cerr << "(" << x << ", " << y << ", " << z << ")"; }
  crd operator ^ (crd &w) {return (crd){y * w.z - w.y * z, z * w.x - w.z * x, x * w.y - y * w.x}; }
  real operator * (crd &w) {return x * w.x + y * w.y + z * w.z; }
  crd operator + (crd &w) {return (crd){x + w.x, y + w.y, z + w.z}; }
  crd operator - (crd &w) {return (crd){x - w.x, y - w.y, z - w.z}; }
  crd operator * (real &w) {return (crd){x * w, y * w, z * w};}
  real len () {return sqrt (x * x + y * y + z * z); }
};

crd A, p, O, v;
real R, r;

real sphere (crd o, real r)
{
  o = o - A;
  crd plane = o ^ v;      // vector of plane which contain O, A, v
  crd vert = v ^ plane;
  real mindis = o * vert / vert.len ();
  if (mindis > R + r || o * v < 0) return 1e300;
  o.out (), vert.out (), plane.out (), evar (mindis);
  real dist = o.len ();
  real run = sqrt (sqr (dist) - sqr (mindis)) - sqrt (sqr (R + r) - sqr (mindis));
  return run / v.len ();
}

// real segment ()
// {
//   crd plane = v ^ p;
//   crd dist = (O - A) * plane / plane.len (); // dist (A, plane)
//   if (dist > R) return 1e300;                // won't intersect forever
  
//   return 1e300;
// }

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("89D.in" , "r", stdin);
  freopen ("89D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  real ans = 1e300;
  A.read (), v.read ();
  v.out (), cerr << endl;

  int n, m;
  
  cin >> R >> n;
  for (int i = 1; i <= n; ++i)
    {
      O.read ();
      cin >> r >> m;
      
      ans = min (ans, sphere (O, r));
      for (; m--; )
        p.read (), ans = min (ans, sphere (O + p, 0));
    }

  cout << setprecision (15) << (ans > 1e200 ? -1 : ans) << endl;
  return 0; 
}
