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

const int maxn = 2200;

string S[maxn];
int f[maxn][maxn], h[maxn], tms;

int calc (int L, int R)
{
  if (L >= R) return 0;
  int t = ++tms, x = min_element (h + L, h + R) - h;
  int p = calc (L, x), q = calc (x + 1, R);
  for (int i = 0; i <= x - L + 1; ++i)
    for (int j = 0; j <= R - x; ++j)
      chkmax (f[t][i + j], f[p][i] + f[q][j] + i * j * h[x]);
  return t;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("178F2.in" , "r", stdin);
  freopen ("178F2.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, k;
  
  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    cin >> S[i];
  sort (S + 1, S + n + 1);
  for (int i = 1; i < n; ++i)
    for (; h[i] < SZ (S[i]) && h[i] < SZ (S[i + 1]) && S[i][h[i]] == S[i + 1][h[i]]; ++h[i]);

  cout << f[calc (1, n)][k] << endl;
  return 0; 
}
