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

int gcd (int a, int b)
{
  for (int t; a; t = a, a = b % a, b = t);
  return b;
}

int is_2type (int b, int d)
{
  int x = 0;
  for (int t; (t = gcd (b, d)) != 1; d /= t, ++x);
  if (d == 1) return x;
  return -1;
}

bool is_3type (int b, int d)
{
  return b % d == 1;
}

bool is_11type (int b, int d)
{
  return (b + 1) % d == 0;
}

bool is_6type (int b, int d)
{
  for (int t; (t = gcd (b, d)) != 1; d /= t);
  d /= gcd ((b * b - 1) / (b % 2 + 1), d);
  return d == 1;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("180B.in" , "r", stdin);
  freopen ("180B.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int b, d, x;
  
  cin >> b >> d;
  if ((x = is_2type (b, d)) != -1)
    return cout << "2-type" << endl
                << x << endl, 0;
  if (is_3type (b, d))
    return cout << "3-type" << endl, 0;
  if (is_11type (b, d))
    return cout << "11-type" << endl, 0;
  if (is_6type (b, d))
    return cout << "6-type" << endl, 0;
  cout << "7-type" << endl;
  return 0; 
}
