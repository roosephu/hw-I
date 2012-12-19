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

const int maxn = 15, maxS = 1 << maxn | 30, maxfwd = 105, maxK = 550000;

unordered_map<string, int> pattern;
int popcnt[maxS];
int f[maxS][maxfwd + 1];
int nptr[maxK][maxn];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("201D.in" , "r", stdin);
  freopen ("201D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  string S, text; int n, m, K;
  
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> S, pattern[S] = i;
  for (int i = 1; i < 1 << n; ++i)
    popcnt[i] = popcnt[i >> 1] + (i & 1);

  pair<int, int> ans = MKP (0, 0);
  cin >> m;
  for (int _ = 1; _ <= m; ++_)
    {
      cin >> K;
      vector<int> vec;
      for (int i = 1; i <= K; ++i)
        {
          cin >> text;
          if (!pattern.count (text)) continue;
          vec.push_back (pattern[text]);
        }
      // for (auto &w : vec)
      //   cerr << w << " ";
      // cerr << endl;

      K = SZ (vec);
      fill (nptr[K], nptr[K] + n, oo);
      for (int i = K - 1; i >= 0; --i)
        for (int j = 0; j < n; ++j)
          if (j == vec[i])
            nptr[i][j] = i;
          else
            nptr[i][j] = nptr[i + 1][j];

      int mask = (1 << n) - 1, maxfwd = n * (n - 1) / 2;
      memset (f, 0x3F, sizeof (f[0]) * (mask + 1));
      f[0][0] = -1;
      for (int S = 0; S < mask; ++S)
        for (int fwd = 0; fwd <= maxfwd; ++fwd)
          if (f[S][fwd] != oo)
            for (int x = 0; x < n; ++x)
              if ((~S >> x & 1) && nptr[f[S][fwd] + 1][x] < oo)
                chkmin (f[S | 1 << x][fwd + popcnt[S & ((1 << x) - 1)]], nptr[f[S][fwd] + 1][x]);
      // for (int S = 0; S <= mask; ++S)
      //   for (int fwd = 0; fwd <= maxfwd; ++fwd)
      //     if (f[S][fwd] != oo)
      //       cerr << "dp " << S << " " << fwd << " : " << f[S][fwd] << endl;
      
      for (int fwd = 0; fwd <= maxfwd; ++fwd)
        if (f[mask][fwd] != oo)
          ans = max (ans, MKP (fwd + 1, -_)); // , cerr << fwd << endl;
    }

  // cerr << ans << endl;
  if (ans.Py)
    {
      cout << -ans.Py << endl
           << "[:";
      for (; ans.Px--; ) cout << "|";
      cout << ":]";
    }
  else cout << "Brand new problem!" << endl;
  return 0; 
}
