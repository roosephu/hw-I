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

const double eps = 1e-8;

struct crd {double x, y, z;} ;
typedef pair<crd, crd> line;

crd V, P, Wx, Wy, Mx, My;

crd operator^ (crd a, crd b) {return (crd){a.y * b.z - a.z * b.y, a.z * b.x - b.z * a.x, a.x * b.y - a.y * b.x};}
crd operator* (crd a, double b) {return (crd){a.x * b, a.y * b, 1};}
crd operator+ (crd a, crd b) {return (crd){a.x + b.x, a.y + b.y, 1};}
crd operator- (crd a, crd b) {return (crd){a.x - b.x, a.y - b.y, 1};}
bool operator< (crd a, crd b) {return a.x < b.x || (a.x == b.x && a.y < b.y); }

int sgn (double x) {return x > -eps ? x > eps : -1; }

int intersect (line a, line b, int cmp, int if2)
{
  crd ca = a.Px ^ a.Py, cb = b.Px ^ b.Py, cx = ca ^ cb;
  if (!sgn (cx.x) && !sgn (cx.y) && !sgn (cx.z))
    {
      if (a.Py < a.Px) swap (a.Px, a.Py);
      if (b.Py < b.Px) swap (b.Px, b.Py);
      return a.Py < b.Px || b.Py < a.Px ? 0 : if2;
    }
  if (!(sgn (((b.Px - a.Px) ^ (a.Py - a.Px)).z) * sgn (((a.Py - a.Px) ^ (b.Py - a.Px)).z) >= cmp)) return 0;
  return sgn (((a.Px - b.Px) ^ (b.Py - b.Px)).z) * sgn (((b.Py - b.Px) ^ (a.Py - b.Px)).z) >= cmp;
}

crd reflect (line L, crd P)
{
  crd x = L.Py - L.Px, y = P - L.Px;
  double mid = atan2 (x.y, x.x);
  double dff = atan2 (y.y, y.x);
  double now = mid * 2 - dff, dist = hypot (y.x, y.y);
  return L.Px + (crd){cos (now), sin (now)} * dist;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("32E.in" , "r", stdin);
  freopen ("32E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> V.x >> V.y >> P.x >> P.y
      >> Wx.x >> Wx.y >> Wy.x >> Wy.y
      >> Mx.x >> Mx.y >> My.x >> My.y;

  V.z = P.z = Wx.z = Wy.z = Mx.z = My.z = 1;
  line W = MKP (Wx, Wy), M = MKP (Mx, My);
  // check if it can be seen straight
  if (!intersect (W, MKP (V, P), 0, 1) && !intersect (M, MKP (V, P), 0, 0))
    return cout << "YES" << endl, cerr << "case1" << endl, 0;

  // find reflect point
  crd Rp = reflect (M, P);
  if (intersect (M, MKP (V, Rp), 0, 0))
    {
      crd x = (V ^ Rp) ^ (Mx ^ My); x.y /= x.z, x.x /= x.z, x.z = 1;
      if (!intersect (W, MKP (V, x), 0, 1) && !intersect (W, MKP (x, P), 0, 1))
        return cout << "YES" << endl, cerr << "case2" << endl, 0;
    }
  cout << "NO" << endl;
  return 0; 
}
