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

const int maxn = 4400;

int f[maxn][maxn], c[maxn], r[maxn];
VI S, ans;
vector<VI> G;
map<PII, int> E;

void dfs (int L, int R)
{
  if (E.count (MKP (L, R))) ans.push_back (E[MKP (L, R)]), --f[L][R];
  if (f[L][R] == 0) return ;
  if (f[L][R] == f[L + 1][R]) return dfs (L + 1, R);
  if (f[L][R] == f[L][R - 1]) return dfs (L, R - 1);

  foreach (it, G[L])
    if (*it < R && f[L][*it] + f[*it][R] == f[L][R])
      return (void)(dfs (L, *it), dfs (*it, R));
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("39C.in" , "r", stdin);
  freopen ("39C.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> c[i] >> r[i], S.push_back (c[i] + r[i]), S.push_back (c[i] - r[i]);
  sort (iter (S)), S.resize (unique (iter (S)) - S.begin ());

  G.resize (sz_m (S) + 1);
  for (int i = 1; i <= n; ++i)
    {
      int L = lower_bound (iter (S), c[i] - r[i]) - S.begin () + 1;
      int R = lower_bound (iter (S), c[i] + r[i]) - S.begin () + 1;
      G[L].push_back (R);
      E[MKP (L, R)] = i;
      // cerr << L << " " << R << endl;
    }
  
  n = sz_m (S);
  for (int i = 1; i <= n; ++i)
    sort (iter (G[i]));
  for (int i = n; i; --i)
    for (int j = i; j <= n; ++j)
      {
        f[i][j] = max (f[i + 1][j], f[i][j - 1]);
        foreach (it, G[i])
          if (*it < j)
            chkmax (f[i][j], f[i][*it] + f[*it][j]);
          else
            break;

        if (E.count (MKP (i, j))) ++f[i][j];
        // cerr << i << " " << j << ": " << f[i][j] << endl;
      }

  cout << f[1][n] << endl;
  dfs (1, n);
  sort (iter (ans));
  foreach (it, ans)
    cout << *it << " ";
  return 0; 
}
