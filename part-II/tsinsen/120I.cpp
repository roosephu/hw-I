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


const int maxn = 220000;

int tab[10][7] = {
  {1, 1, 1, 0, 1, 1, 1}, 
  {0, 0, 1, 0, 0, 1, 0}, 
  {1, 0, 1, 1, 1, 0, 1}, 
  {1, 0, 1, 1, 0, 1, 1}, 
  {0, 1, 1, 1, 0, 1, 0}, 
  {1, 1, 0, 1, 0, 1, 1}, 
  {1, 1, 0, 1, 1, 1, 1}, 
  {1, 0, 1, 0, 0, 1, 0}, 
  {1, 1, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 1, 0, 1, 1}, 
};
int cost[10][10];
int v[maxn], pre[maxn], best[maxn];
char S[maxn];

int main ()
{
  // freopen ("input.txt" , "r", stdin);
  // freopen ("output.txt", "w", stdout);
  ios_base::sync_with_stdio (false);

  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      for (int k = 0; k < 7; ++k)
        cost[i][j] += tab[i][k] && tab[j][k];
  
  cin >> (S + 1); 
  int n = strlen (S + 1) >> 1, old = 0;
  for (int i = 1; i <= n * 2; ++i)
    v[i] = S[i] - '0';
  for (int i = 1; i <= n; ++i)
    {
      pre[i] = pre[i - 1] + cost[v[i]][v[i + n]];
      best[i] = best[i - 1] + cost[v[i]][v[i]];
    }

  int pos = 0; old = pre[n];
  for (int i = n << 1; i; --i)
    {
      int x;
      for (x = v[i] + 1; x < 10; ++x)
        {
          int now = i > n ? cost[v[i - n]][x] : cost[x][x];
          int suf = i > n ? (best[n] - best[i - n]) : ((n - i) * 7);
          if (now + (i > n ? pre : best)[(i - 1) % n] + suf > old)
            {pos = i; v[i] = x; break;}
        }
      if (x < 10) break;
    }
  if (!pos) return cout << -1 << endl, 0;

  // cvar (pos);
  if (pos <= n) best[pos] = best[pos - 1] + cost[v[pos]][v[pos]];
  for (int i = pos + 1; i <= n; ++i)
    {
      int x;
      for (x = 0; x < 10; ++x)
        if (best[i - 1] + cost[x][x] + (n - i) * 7 > old)
          break;
      best[i] = best[i - 1] + cost[x][x], v[i] = x;
    }
  // evar (0);
  // for (int i = 1; i <= n; ++i)
  //   cerr << v[i];
  // cerr << endl;

  int now = 0;
  for (int i = n + 1; i <= pos; ++i)
    now += cost[v[i - n]][v[i]];
  // cvar (now);

  // for (int i = 1; i <= n; ++i)
  //   pre[i] = pre[i - 1]
  for (int i = max (0, pos - n) + 1; i <= n; ++i)
    {
      int x;
      for (x = 0; x < 10; ++x)
        if (now + cost[v[i]][x] + (best[n] - best[i]) > old)
          break;
      v[i + n] = x, now += cost[v[i]][x];
    }

  for (int i = 1; i <= n << 1; ++i)
    cout << v[i];
  cout << endl;
  return 0; 
}

