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

const int maxn = 110;

int64 f[maxn];
string S;

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("212C.in" , "r", stdin);
  freopen ("212C.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  cin >> S;
  int n = SZ (S);
  S = S + S;
  
  f[1] = 1;
  for (int i = 2; i <= n; ++i)
    f[i] = f[i - 1] + f[i - 2];

  int beg = -1;
  for (int i = 0; i < n; ++i)
    if (S[i] == S[i + 1])
      {beg = i; break; }
  if (beg == -1) return cout << f[(n >> 1) - 1] + f[(n >> 1) + 1] << endl, 0;
  S = S.substr (beg + 1, n); cerr << S << endl;
  
  int64 ans = 1;
  for (int i = 0, j; i < n; i = j + 1)
    {
      for (j = i; j < n - 1 && S[j] != S[j + 1]; ++j);
      int L = i, R = j; // cerr << L << " " << R << endl;
      if (S[L] == 'A') L += 3;
      if (S[R] == 'B') R -= 3;
      cerr << L << " " << R << endl;
      ans = ans * f[(R - L + 1) / 2 + 2];
    }
  cout << ans << endl;
  return 0; 
}
