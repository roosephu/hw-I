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

const double eps = 1e-10;

template<class edge> struct Graph
{
  vector<vector<edge> > adj;
  Graph (int n) {adj.clear (); adj.resize (n + 5);}
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

double get_dist (double x, double b, double t)
{
  return min (max (eps, t * (b + b + t)) / max (2 * (b + t - b * cos (x)), eps * eps), b + t);
}

double dist (PII a, PII b) {return hypot (a.Px - b.Px, a.Py - b.Py); }

double query (PII S, PII t1, PII t2, double w1, double w2)
{
  double x1 = atan2 (t1.Py - S.Py, t1.Px - S.Px), x2 = atan2 (t2.Py - S.Py, t2.Px - S.Px);
  if (x1 > x2) swap (x1, x2), swap (t1, t2), swap (w1, w2);
  double d1 = dist (S, t1), d2 = dist (S, t2);
  double L = x1, R = x2, x;

  for (; x = (L + R) / 2, R - L > eps; )
    get_dist (x - x1, d1, w1) > get_dist (x2 - x, d2, w2) ? (L = x) : (R = x);
  
  return min (get_dist (x - x1, d1, w1), get_dist (x2 - x, d2, w2));
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("8D.in" , "r", stdin);
  freopen ("8D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  double w1, w2; PII S, t1, t2; 
  
  cin >> w1 >> w2 >> S.Px >> S.Py >> t1.Px >> t1.Py >> t2.Px >> t2.Py;
  cout << setprecision (15);
  
  if (dist (S, t2) + dist (t2, t1) <= dist (S, t1) + w2 || dist (S, t1) + w2 + dist (t1, t2) <= dist (S, t2) + w1)
    return cout << min (dist (S, t2) + dist (t2, t1) + w1, dist (S, t1) + w2) << endl, 0;
  // if (dist (S, t2) + dist (t2, t1) + w1 >= dist ())
  cout << query (S, t1, t2, w2, w1) << endl;

  return 0; 
}
