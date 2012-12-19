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
typedef long double real;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef set<int> SI;
typedef pair<int, int> PII;

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

vector<PII> ans;
VI vec;

void move_partial (int, int, int, int);

void move_optimal (int d, int x, int y, int z) // x to y, using c
{
  if (vec[d] == 1) return move_partial (d, x, y, z);
  if (d == sz_m (vec) - 1)      // the only one
    {
      for (int i = 1; i < vec[d]; ++i)
        ans.push_back (MKP (x, z));
      ans.push_back (MKP (x, y));
      for (int i = 1; i < vec[d]; ++i)
        ans.push_back (MKP (z, y));
      return ;
    }
  move_partial (d + 1, x, y, z);
  for (int i = 1; i <= vec[d]; ++i)
    ans.push_back (MKP (x, z));
  move_partial (d + 1, y, x, z);
  for (int i = 1; i <= vec[d]; ++i)
    ans.push_back (MKP (z, y));
  move_optimal (d + 1, x, y, z);
}

void move_partial (int d, int x, int y, int z) // x to y, using c
{
  if (d == sz_m (vec)) return ;
  move_partial (d + 1, x, z, y);
  for (int i = 1; i <= vec[d]; ++i)
    ans.push_back (MKP (x, y));
  move_partial (d + 1, z, y, x);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("98D.in" , "r", stdin);
  freopen ("98D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, lx = 0;
  
  cin >> n;
  for (int i = 1, d; i <= n; ++i)
    {
      cin >> d;
      if (lx == d)
        ++vec[sz_m (vec) - 1];
      else
        vec.push_back (1);
      lx = d;
    }

  // foreach (it, vec)
  //   cerr << *it << endl;
  
  move_optimal (0, 1, 3, 2);

  cout << sz_m (ans) << endl;
  foreach (it, ans)
    cout << it->Px << " " << it->Py << endl;
  return 0; 
}
