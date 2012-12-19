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
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>

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
#define MKP make_pair
#define Px first
#define Py second
#define PB push_back
#define SZ(x) (int)((x).size ())
#define ALL(x) (x).begin (), (x).end ()

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef long double real;
typedef unordered_map<int, int> UMII;
typedef unordered_set<int> USI;

int64 pow (int64 b, int64 e, int64 m) { int64 t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }
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

const int maxr = 33;

pair<int64, int64> get_mod (int k, int m, int P, int r) // return <a, r> k^{2^m} = a * (p^r) + (r != 0)
{
  int64 v[maxr] = {0}, u[maxr];
  
  for (int i = 0; i <= r; ++i)
    v[i] = k % P, k /= P;
  for (int i = 1; i <= m; ++i)
    {
      for (int x = 0; x <= r; ++x)
        u[x] = 0;
      for (int x = 0; x <= r; ++x)
        {
          int64 s = 0;
          for (int y = 0; x + y <= r; ++y)
            s += v[x] * v[y] + u[x + y], u[x + y] = s % P, s /= P;
        }
      for (int x = 0; x <= r; ++x)
        v[x] = u[x];
    }
  assert (v[0] == 1);

  int lx = 1;
  for (; !v[lx] && lx < r; ++lx);
  return MKP (v[lx], lx);
}

pair<int64, int64> calc (int k, int64 R, int P) // return <a, r> k^{2^R} - 1 = a * p^r
{
  // cerr << "calc: " << k << " " << R << " " << P << endl;
  int64 rem = pow (k, pow (2, R, P - 1), P);
  if (rem != 1) return MKP (rem - 1, 0);

  int64 w = 0;
  for (; 2 << w < P; ++w);
  pair<int64, int64> ret = MKP (0, 0);
  for (int r = 1; ret.Px == 0; r *= 2)
    ret = get_mod (k, min (w, R), P, r);
  ret.Px = ret.Px * pow (2, R - min (w, R), P);
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("185D.in" , "r", stdin);
  freopen ("185D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int tc, k, P; int64 L, R;
  
  cin >> tc;
  for (; tc--; )
    {
      int64 ans;
      
      cin >> k >> L >> R >> P;
      if (k % P == 0)
        ans = 1;
      else if (k % P == 1)
        ans = pow (2, R - L + 1, P);
      else
        {
          pair<int64, int64> ansR = calc (k, R + 1, P), ansL = calc (k, L, P);
          if (ansL.Py != ansR.Py)
            ans = 0;
          else
            ans = ansR.Px * pow (ansL.Px, P - 2, P) % P;
        }
      if (k & 1)
        ans = ans * pow (2, (R - L) % (P - 1) * (P - 2) % (P - 1), P) % P;
      cout << ans << endl;
    }

  return 0; 
}
