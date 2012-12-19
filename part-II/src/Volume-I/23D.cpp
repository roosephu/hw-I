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

struct crd {double x, y, z; } ;

crd operator^ (crd a, crd b) {return (crd){a.y * b.z - a.z * b.y, a.z * b.x - b.z * a.x, a.x * b.y - a.y * b.x};}
crd operator- (crd a, crd b) {return (crd){a.x - b.x, a.y - b.y};}
crd operator* (crd a, double b) {return (crd){a.x * b, a.y * b};}

bool check (crd A, crd B, crd C, vector<crd> &ans)
{
  ans.clear ();
  crd u = A ^ B, v = B ^ C, Lab, Lbc;
  Lab = (crd){u.y, -u.x, u.x * (A.y + B.y) / 2 - u.y * (A.x + B.x) / 2};
  Lbc = (crd){v.y, -v.x, v.x * (C.y + B.y) / 2 - v.y * (C.x + B.x) / 2};
  if ((Lab ^ Lbc).z == 0) return false;
  crd L = (crd){0, 0, 1}, R = (crd){0, 0, 1};
  R.x = (2 * Lab.x * Lbc.y * B.x + 2 * Lab.y * Lbc.y * B.y + Lab.z * Lbc.y + Lab.y * Lbc.z) / (Lab.x * Lbc.y - Lab.y * Lbc.x);
  R.y = (2 * Lab.y * Lbc.x * B.y + 2 * Lab.x * Lbc.x * B.x + Lab.z * Lbc.x + Lab.x * Lbc.z) / (Lab.y * Lbc.x - Lab.x * Lbc.y);
  L = B * 2.0 - R;
  crd X = A * 2.0 - L, Y = C * 2.0 - R;

  ans.PB (X), ans.PB (L), ans.PB (R), ans.PB (Y);
  // the tetragon is X - L - R - Y, we only need to check if it is convex
  if ((((L - X) ^ (R - L)).z > 0 && ((R - L) ^ (Y - R)).z > 0 &&
       ((Y - R) ^ (X - Y)).z > 0 && ((X - Y) ^ (L - X)).z > 0) ||
      (((L - X) ^ (R - L)).z < 0 && ((R - L) ^ (Y - R)).z < 0 &&
       ((Y - R) ^ (X - Y)).z < 0 && ((X - Y) ^ (L - X)).z < 0))
    return true;
  return false;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("23D.in" , "r", stdin);
  freopen ("23D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int T; crd A, B, C; vector<crd> ans;
  
  cin >> T;
  cout << setprecision (15);
  for (; T--; )
    {
      cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
      A.z = B.z = C.z = 1;
      if (check (A, B, C, ans) || check (B, C, A, ans) || check (C, A, B, ans))
        {
          cout << "YES" << endl;
          foreach (it, ans)
            cout << it->x << " " << it->y << " ";
          cout << endl;
        }
      else
        cout << "NO" << endl << endl;
    }

  return 0; 
}
