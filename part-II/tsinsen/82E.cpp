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
typedef vector<int> VI;
typedef map<int, int> MII;
typedef set<int> SI;
typedef pair<int, int> PII;
typedef long double real;

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
  void del (int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
  int deg (int v) {return adj[v].size (); }
  vector<edge>& operator [](int t) {return adj[t];}
};

const int maxn = 550;

typedef pair<real, real> PRR;
typedef vector<PRR>::iterator ptr;

real rate, f, h;
real L[maxn], R[maxn];

real area (vector<PRR> &poly)
{
  real ret = 0; int n = sz_m (poly);
  for (int i = 0; i < n; ++i)
    ret += poly[i].Px * poly[(i + 1) % n].Py - poly[i].Py * poly[(i + 1) % n].Px;
  return fabs (ret) / 2;
}

PRR crd (real u, real b)
{
  real x = f / (f - h) * 2 / (1 / u + 1 / b), y = f * (u - b) / (u + b);
  return MKP (x, y);
}

real cap (int x, int y)         // return the cap area of trapezoid x and (rev)y
{
  vector<PRR> poly;
  // if (L[x] > L[y]) swap (x, y);
  // if (L[y] >= R[x] * rate) return 0;
  double Lxr = L[x] * rate, Lyr = L[y] * rate, Rxr = R[x] * rate, Ryr = R[y] * rate;

  if (L[x] <  Lyr && L[y] <  Lxr) poly.PB (crd (L[x], L[y]));
  if (Lyr <= L[x] && L[x] <= Ryr) poly.PB (MKP (L[x], +h));
  if (L[x] <= Lyr && Lyr <= R[x]) poly.PB (MKP (Lyr, +h));
  if (L[x] <= Ryr && Ryr <= R[x]) poly.PB (MKP (Ryr, +h));
  if (Lyr <= R[x] && R[x] <= Ryr) poly.PB (MKP (R[x], +h));
  if (R[x] <  Lyr && L[y] <  Rxr) poly.PB (crd (R[x], L[y]));
  if (R[x] <  Ryr && R[y] <  Rxr) poly.PB (crd (R[x], R[y]));
  if (Rxr >= R[y] && R[y] >= Lxr) poly.PB (MKP (R[y], -h));
  if (R[y] >= Rxr && Rxr >= L[y]) poly.PB (MKP (Rxr, -h));
  if (R[y] >= Lxr && Lxr >= L[y]) poly.PB (MKP (Lxr, -h));
  if (Rxr >= L[y] && L[y] >= Lxr) poly.PB (MKP (L[y], -h));
  if (L[x] <  Ryr && R[y] <  Lxr) poly.PB (crd (L[x], R[y]));

  return area (poly);
}

real calc (vector<PRR> &pt)
{
  int n = pt.size (); real ret = 0;
  for (int i = 0; i < n; ++i)
    L[i] = pt[i].Px, R[i] = pt[i].Py;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      ret += cap (i, j);
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("82E.in" , "r", stdin);
  freopen ("82E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n; real ans = 0; vector<PRR> neg, pos;
  
  cin >> n >> h >> f;
  rate = (f + h) / (f - h);
  for (int i = 1, l, r; i <= n; ++i)
    {
      cin >> l >> r;
      if (r <= 0) neg.push_back (MKP (-r, -l));
      if (l >= 0) pos.push_back (MKP (+l, +r));
      if (l < 0 && 0 < r)
        neg.PB (MKP (0, -l)), pos.PB (MKP (0, +r));
      ans += (r - l) * (rate + 1) * h * 2;
    }

  cout << setprecision (15) << ans - calc (neg) - calc (pos) << endl;
  return 0; 
}
