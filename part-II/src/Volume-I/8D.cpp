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

// #define double long double

const double eps = 1e-6;
typedef pair<double, double> Tpoint;

template<class edge> struct Graph
{
  vector<vector<edge> > adj;
  Graph (int n) {adj.clear (); adj.resize (n + 5);}
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

double dist (Tpoint a, Tpoint b) {return hypot (a.Px - b.Px, a.Py - b.Py); }

pair<Tpoint, Tpoint> get_intersect (Tpoint C1, double R1, Tpoint C2, double R2)
{
  double d = dist (C1, C2);
  if (abs (R1 - R2) >= d) return MKP (MKP (1e100, 1e100), MKP (1e100, 1e100));
  double mid = atan2 (C2.Py - C1.Py, C2.Px - C1.Px);
  double dlt = acos ((R1 * R1 + d * d - R2 * R2) / (2 * R1 * d));
  Tpoint u = MKP (C1.Px + R1 * cos (mid + dlt), C1.Py + R1 * sin (mid + dlt));
  Tpoint v = MKP (C1.Px + R1 * cos (mid - dlt), C1.Py + R1 * sin (mid - dlt));
  return MKP (u, v);
}

bool valid (double x, Tpoint S, Tpoint t1, Tpoint t2, double w1, double w2)
{
  w1 -= x, w2 -= x;
  pair<Tpoint, Tpoint> p = get_intersect (t1, w1, S, x), q = get_intersect (t2, w2, S, x), r = get_intersect (t1, w1, t2, w2);
  return dist (p.Px, t2) <= w2 || dist (p.Py, t2) <= w2 || dist (q.Px, t1) <= w1 || dist (q.Py, t1) <= w1 || dist (r.Px, S) <= x || dist (r.Py, S) <= x;
}

double query (Tpoint S, Tpoint t1, Tpoint t2, double w1, double w2)
{
  double d1 = dist (S, t1), d2 = dist (S, t2);
  double L = 0, R = min (d1 + w1, d2 + w2), x;

  for (; x = (L + R) / 2, R - L > eps; )
    valid (x, S, t1, t2, d1 + w1, d2 + w2) ? (L = x) : (R = x);
  return x;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("8D.in" , "r", stdin);
  freopen ("8D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  double w1, w2; Tpoint S, t1, t2; 
  
  cin >> w1 >> w2 >> S.Px >> S.Py >> t1.Px >> t1.Py >> t2.Px >> t2.Py;
  cout << setprecision (15);
  
  if (dist (S, t2) + dist (t2, t1) <= dist (S, t1) + w2 || dist (S, t1) + w2 + dist (t1, t2) <= dist (S, t2) + w1)
    return cout << min (dist (S, t2) + dist (t2, t1) + w1, dist (S, t1) + w2) << endl, 0;
  // if (dist (S, t2) + dist (t2, t1) + w1 >= dist ())
  cout << query (S, t1, t2, w2, w1) << endl;

  return 0; 
}
