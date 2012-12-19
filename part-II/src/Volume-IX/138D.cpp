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
#define sz_m(x) (int)((x).size ())
#define iter(x) (x).begin (), (x).end ()

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef long double real;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef unordered_map<int, int> UMII;
typedef unordered_set<int> USI;
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

const int maxn = 42;

int n, m;
int f[maxn][maxn][maxn][maxn];
char S[maxn][maxn];

int SG (int ls, int rs, int ld, int rd)
{
  if (ls > rs || ld > rd) return 0;
  int &ret = f[ls][rs][ld + m][rd + m];
  if (ret != -1) return ret;

  unordered_set<int> Q;
  for (int s = ls; s <= rs; s += 2) // s = x + y
    for (int d = max (-s, ld); d <= rd && d <= s; d += 2) // d = x - y
      {
        int x = (s + d) >> 1, y = (s - d) >> 1;
        if (x >= n || y >= m) continue;
        
        if (S[x][y] == 'L')
          Q.insert (SG (ls, s - 2, ld, rd) ^ SG (s + 2, rs, ld, rd));
        else if (S[x][y] == 'R')
          Q.insert (SG (ls, rs, ld, d - 2) ^ SG (ls, rs, d + 2, rd));
        else
          Q.insert (SG (ls, s - 2, ld, d - 2) ^ SG (s + 2, rs, ld, d - 2) ^ SG (ls, s - 2, d + 2, rd) ^ SG (s + 2, rs, d + 2, rd));
      }

  for (; Q.count (++ret); );
  // cerr << "SG: " << ls << " " << rs << " " << ld << " " << rd << ": " << ret << endl;
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("138D.in" , "r", stdin);
  freopen ("138D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n >> m;
  if (n == 1 || m == 1) return cout << ((n + m) % 2 == 1 ? "LOSE" : "WIN") << endl, 0;
  for (int i = 0; i < n; ++i)
    cin >> S[i];

  memset (f, -1, sizeof (f));
  int even = SG (0,  (n + m - 2) & -2     , - ((m - 1) & -2)     ,  (n - 1) & -2     );
  int odd  = SG (1, ((n + m - 3) & -2) + 1, -(((m - 2) & -2) + 1), ((n - 2) & -2) + 1);
  cvar (even), evar (odd);
  
  cout << (even != odd ? "WIN" : "LOSE") << endl;
  return 0; 
}
