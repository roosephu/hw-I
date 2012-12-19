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

int ufs[maxn], deg[maxn];
bool o[maxn];

int find (int t) {return ufs[t] ? ufs[t] = find (ufs[t]) : t; }

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("209C.in" , "r", stdin);
  freopen ("209C.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m;
  
  cin >> n >> m;
  for (int i = 1, s, t; i <= m; ++i)
    {
      cin >> s >> t, deg[s] ^= 1, deg[t] ^= 1, o[s] = o[t] = true;
      if (find (s) != find (t))
        ufs[find (s)] = find (t);
    }
  for (int i = 1; i <= n; ++i)
    if (ufs[i])
      deg[find (i)] += deg[i];

  vector<int> vec;
  for (int i = 1; i <= n; ++i)
    if ((!ufs[i] && o[i]) || (i == find (1)))
      vec.push_back (deg[i]); // cerr << deg[i] << endl;
  sort (ALL (vec), greater<int> ());
  
  int lx = -1;
  for (auto &x : vec)
    lx = (lx == -1 ? x : (abs (lx - 1) + abs (x - 1)));
  cout << SZ (vec) - 1 + lx / 2 << endl;
  return 0; 
}
