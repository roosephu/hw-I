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

const int maxcrd = 15, maxn = 22;

bool cmp (const pair<real, real> &a, const pair<real, real> &b) { return a.Py > b.Py;}

int v[maxcrd];
int nf, ne, ns; real rf, re, rs, df, de;
real f[maxn][maxn];
real ans;

void dyn_prg ()
{
  vector<pair<real, real>> profit;
  for (int i = 1; i <= 13; ++i)
    {
      int x = 2 - (i == 1 || i == 13) - v[i];
      real f = 2 * rf, e = 2 * re;
      for (int j = 1; j <= 13; ++j)
        {
          f += v[j] * max (min (i + rf, j + rs) - max (j - rs, i - rf), (real)0.0);
          e += v[j] * max (min (i + re, j + rs) - max (j - rs, i - re), (real)0.0);
        }
      for (; x--; )
        profit.push_back (MKP (f * df, e * de));
    }
  sort (ALL (profit), greater<pair<real, real>>());

  for (int i = 0; i <= nf; ++i)
    for (int j = 0; j <= ne; ++j)
      {
        f[i][j] = 0;
        if (i) chkmax (f[i][j], f[i - 1][j] + profit[i + j - 1].Px);
        if (j) chkmax (f[i][j], f[i][j - 1] + profit[i + j - 1].Py);
      }

  for (int i = 0; i <= ne; ++i)
    {
      sort (profit.begin () + nf + i, profit.end (), cmp);
      real now = f[nf][i];
      for (int j = 0; j < ne - i; ++j)
        now += profit[nf + i + j].Py;
      ans = max (ans, now);
    }
}

void search (int d, int ns)
{
  if (!d) return !ns ? dyn_prg () : (void)0;
  for (int i = 0; i <= 2 - (d == 1 || d == 13) && i <= ns; ++i)
    v[d] = i, search (d - 1, ns - i);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("175E.in" , "r", stdin);
  freopen ("175E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  cin >> nf >> ne >> ns >> rf >> re >> rs >> df >> de;
  rf = sqrt (rf * rf - 1);
  re = sqrt (re * re - 1);
  rs = sqrt (rs * rs - 1);
  
  search (13, ns);

  cout << setprecision (20) << ans << endl;
  return 0; 
}
