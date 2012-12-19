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

const int maxn = 2200, lmt = 200000;

queue<int> vec[maxn];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("207A2.in" , "r", stdin);
  freopen ("207A2.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, lx = -1, ans = 0;
  
  cin >> n;
  vector<pair<int, int>> out;
  set<pair<int, int>> S;
  
  for (int i = 1; i <= n; ++i)
    {
      int k, a, x, y, m; cin >> k >> a >> x >> y >> m;
      S.insert (MKP (a, i)); // cerr << a << endl;
      for (; --k; ) vec[i].push (a = ((int64)a * x + y) % m);
    }

  for (; !S.empty (); )
    {
      // auto x = heap.top (); heap.pop (); // cerr << x.Px << " " << x.Py << endl;
      auto it = S.lower_bound (MKP (lx, 0));
      if (it == S.end ())
        it = S.begin ();

      auto x = *it; S.erase (it);
      if (SZ (out) <= lmt)
        out.push_back (x);
      if (!vec[x.Py].empty ())
        S.insert (MKP (vec[x.Py].front (), x.Py)), vec[x.Py].pop ();
      ans += lx > x.Px, lx = x.Px;
    }
  cout << ans << endl;
  if (SZ (out) <= lmt)
    for (auto &x : out)
      cout << x.Px << " " << x.Py << endl;

  return 0; 
}
