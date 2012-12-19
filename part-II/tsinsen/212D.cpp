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

const int maxn = 1100000;

int a[maxn], L[maxn], R[maxn];
int64 dff[maxn];
char buf[20];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("212D.in" , "r", stdin);
  freopen ("212D.out", "w", stdout);
#endif
  // ios_base::sync_with_stdio (false);

  int n, m; stack<int> stk; 
  
  scanf ("%d", &n); // cin >> n;
  for (int i = 1; i <= n; ++i)
    scanf ("%d", &a[i]); // cin >> a[i];
  stk = stack<int>(), stk.push (0);
  for (int i = 1; i <= n; ++i)
    {
      for (; a[stk.top ()] >  a[i]; stk.pop ());
      L[i] = i - stk.top (), stk.push (i);
    }
  stk = stack<int>(), stk.push (n + 1);
  for (int i = n; i >= 1; --i)
    {
      for (; a[stk.top ()] >= a[i]; stk.pop ());
      R[i] = stk.top () - i, stk.push (i);
    }

  for (int i = 1; i <= n; ++i)
    {
      // int x = min (L[i], R[i]), y = max (L[i], R[i]);
      dff[0] += a[i], dff[L[i]] -= a[i], dff[R[i]] -= a[i], dff[L[i] + R[i]] += a[i];
      // cerr << L[i] << " " << R[i] << endl;
      // for (int i = 0; i < n; ++i) cerr << dff[i] << " ";
      // cerr << endl;
    }

  for (int i = 1; i < n; ++i) dff[i] += dff[i - 1];
  for (int i = 1; i < n; ++i) dff[i] += dff[i - 1];

  // cin >> m; cout << setprecision (16);
  scanf ("%d", &m);
  for (int i = 1, k; i <= m; ++i)
    // cin >> k, --k, sprintf (buf, "%.13f", 1.0 * dff[k] / (n - k)), cout << buf << endl;
    scanf ("%d", &k), --k, printf ("%.13f\n", 1.0 * dff[k] / (n - k));
  
  return 0; 
}
