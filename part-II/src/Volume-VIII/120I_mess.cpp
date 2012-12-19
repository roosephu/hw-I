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
string S;
int w[maxn];

int main ()
{
  freopen ("input.txt" , "r", stdin);
  freopen ("output.txt", "w", stdout);
  ios_base::sync_with_stdio (false);
  cin >> S;

  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      for (int k = 0; k < 7; ++k)
        cost[i][j] += tab[i][k] && tab[j][k];
  
  int n = sz_m (S) >> 1, pos = -1, rem;
  for (int i = 2 * n - 1; i >= n; --i)
    {
      int R = S[i] - '0', L = S[i - n] - '0', x;
      for (x = R + 1; x < 10; ++x) if (cost[L][x] + w[i + 1] > cost[L][R]) break;
      if (x < 10) {rem = cost[L][x] - cost[L][R]; S[i] = x + '0'; pos = i; break; }
      w[i] = w[i + 1] + cost[L][8] - cost[L][R];
    }
  if (pos != -1)
    {
      cvar (pos), cvar (rem); --rem;
      for (int i = pos + 1; i < n * 2; ++i)
        {
          int L = S[i - n] - '0', x, R = S[i] - '0';
          for (x = 0; x < 10; ++x) if (cost[L][x] + w[i + 1] + rem >= cost[L][R]) break;
          S[i] = x + '0';
          rem += cost[L][x] - cost[L][R];
        }
      cout << S << endl;
      cerr << "case1" << endl;
      return 0;
    }

  int total = 0; rem = 0;
  for (int i = 0; i < n; ++i)
    {
      int L = S[i] - '0', R = S[i + n] - '0';
      rem += cost[L][L] - cost[L][R];
    }
  evar (rem);
  
  for (int i = n - 1; i >= 0; --i)
    {
      int L = S[i] - '0', x, R = S[i + n] - '0'; rem -= cost[L][L] - cost[L][R];
      for (x = L + 1; x < 10; ++x) if (cost[L][L] + total < cost[x][x] + (n - 1 - i) * 7 + rem) break;
      if (x != 10) {rem += cost[x][x] - cost[L][R]; S[pos = i] = x + '0'; break;}
      total += cost[L][L];
    }
  if (pos == -1) return cout << -1 << endl, 0;

  cvar (pos), cvar (rem), evar (total);
  for (int i = pos + 1, x; i < n; ++i)
    {
      for (x = 0; x < 10; ++x) if (cost[x][x] + (n - i - 1) * 7 + rem > total) break;
      S[i] = x + '0', total -= cost[x][x];
    }
  total = rem - total; cvar (total);
  
  for (int i = n; i < n * 2; ++i)
    {
      int L = S[i - n] - '0', x;
      for (x = 0; x < 10; ++x) if (cost[L][x] + total > cost[L][L]) break;
      // assert (x != 10);
      S[i] = x + '0';
      total += cost[L][x] - cost[L][L];
    }
  evar (total);
  cout << S << endl;
  cerr << "case2" << endl;
  return 0; 
}
