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
 
using namespace std;

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

#define oo 0x3F3F3F3F
#ifdef DEBUG
#define cvar(x) cerr << "[" << #x << ": " << x << "]"
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
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

const int lmtx = 40000, lmty = 33;

int f[lmtx + 10][lmty + 3];
string ans[] = {"Stas", "Missing", "Masha"};
int n, a, b;

bool valid (int x, int y)
{
  int w = n - 1;
  for (; y && w; --y, w /= x);
  return w;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("39E.in" , "r", stdin);
  freopen ("39E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> a >> b >> n;
  
  f[lmtx][1] = (n - lmtx) & 1 ? 0 : 2;
  for (int j = lmty; j > 1; --j)
    f[lmtx][j] = 2;
  for (int i = lmtx - 1; i; --i) // i ^ j
    {
      f[i][lmty] = i == 1 ? 1 : 2;
      for (int j = lmty - 1; j; --j)
        if (!valid (i, j))        // win
          f[i][j] = 2;
        else
          f[i][j] = 2 - min (f[i + 1][j], f[i][j + 1]);
    }

  cout << ans[f[a][b]] << endl;
  return 0; 
}
