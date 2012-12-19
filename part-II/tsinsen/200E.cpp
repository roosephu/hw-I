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

int c3, c4, c5, ans, a, b, c, G;

int gcd (int a, int b)
{
  for (int t; a; t = a, a = b % a, b = t);
  return b;
}

int calc (int k3, int k4, int k5) { return abs (k3 * c3 * G - k4 * c4) + abs (k4 * c4 - k5 * c5 * G);}

void update (int k3, int k4, int k5)
{
  int t = calc (k3, k4, k5);
  if (t < ans) ans = t, a = k3, b = k4, c = k5;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("200E.in" , "r", stdin);
  freopen ("200E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, S;
  
  cin >> n >> S;
  for (int i = 1, j; i <= n; ++i)
    {
      cin >> j;
      if (j == 3) ++c3;
      if (j == 4) ++c4;
      if (j == 5) ++c5;
    }

  ans = oo;
  G = gcd (c3, c5); c3 /= G, c5 /= G;
  int inv = 1; 
  for (; c3 && c5 && inv * c3 % c5 > 1; ++inv);
  for (int k4 = 0; k4 <= S / c4; ++k4)
    {
      int rem = S - k4 * c4;
      if (rem % G != 0) continue;
      rem /= G;

      if (!c3 || !c5)
        {update (rem * c3, k4, rem * c5); continue;}

      // k3 = k3 + c5 t, k5 = k5 - c3 t
      int k3 = rem * inv % c5, k5 = (rem - k3 * c3) / c5;
      if (k3 > k4 || k5 < k4) continue;
      int T = min ((k4 - k3) / c5, (k5 - k4) / c3); // 0 <= t <= T
      // cerr << k3 << " " << k4 << " " << k5 << " " << T << endl;

      int L = 0, R = T, llr, lrr;
      for (; R - L > 2; )
        {
          llr = (L * 2 + R) / 3, lrr = (L + R * 2) / 3;
          if (calc (k3 + c5 * llr, k4, k5 - c3 * llr) <= calc (k3 + c5 * lrr, k4, k5 - c3 * lrr))
            R = lrr;
          else
            L = llr;
        }
      // cerr << k3 << " " << k4 << " " << k5 << " " << L << " " << R << endl;
      for (; L <= R; ++L)
        update (k3 + c5 * L, k4, k5 - c3 * L);
    }
  
  if (ans == oo)
    cout << -1 << endl;
  else
    cout << a << " " << b << " " << c << endl;
  return 0; 
}
