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
#define it_m(x) (x).begin (), (x).end ()

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef set<int> SI;
typedef pair<int, int> PII;

int64 fpm (int64 b, int64 e, int64 m) { int64 t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }
template<class T> inline bool chkmin (T &a, T b) {return a < b ? a = b, true : false;}
template<class T> inline bool chkmax (T &a, T b) {return a > b ? a = b, true : false;}
template<class T> inline T sqr (T x) {return x * x;}

template<class edge> struct Graph
{
  vector<vector<edge> > adj;
  Graph (int n) {adj.clear (); adj.resize (n + 5);}
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

const int maxlmt = 51, mod = 51123987, maxn = 152;

int f[maxlmt][maxlmt][maxlmt][maxn], last[3], next[maxn][3];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("17C.in" , "r", stdin);
  freopen ("17C.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, ans = 0; string S;
  
  cin >> n >> S;
  int lmt = (n + 2) / 3;
  for (int i = 0; i < 3; ++i)
    last[i] = n;
  for (int i = n - 1; i >= 0; --i)
    {
      last[S[i] - 'a'] = i;
      for (int j = 0; j < 3; ++j)
        next[i][j] = last[j];
    }

  f[1][0][0][last[0]] = 1;
  f[0][1][0][last[1]] = 1;
  f[0][0][1][last[2]] = 1;
  for (int i = 0; i <= lmt; ++i)
    for (int j = 0; j <= lmt; ++j)
      for (int k = 0; k <= lmt; ++k)
        for (int p = 0, T; p < n; ++p)
          if ((T = f[i][j][k][p]))
            {
              // cerr << i << " " << j << " " << k << " " << p << ": " << T << endl;
              if (i + j + k == n)
                {
                  if (min (min (i, j), k) >= lmt - 1)
                    (ans += T) %= mod;
                  continue;
                }
              if (next[p][0] != n && i < lmt)
                (f[i + 1][j][k][next[p][0]] += T) %= mod;
              if (next[p][1] != n && j < lmt)
                (f[i][j + 1][k][next[p][1]] += T) %= mod;
              if (next[p][2] != n && k < lmt)
                (f[i][j][k + 1][next[p][2]] += T) %= mod;
            }

  cout << ans << endl;
  return 0; 
}
