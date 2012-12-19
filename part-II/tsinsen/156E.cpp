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
  Graph () {adj.clear (); }
  void resize (int n) {adj.resize (n + 5); }
  void adde (int s, edge e){adj[s].push_back (e);}
  int deg (int v) {return adj[v].size (); }
  vector<edge>& operator [](int t) {return adj[t];}
};

const int maxlmt = 5000000, maxn = 22000, maxm = 33000;

int64 f[maxlmt], a[maxn], c[maxm];
string S[maxm];
VI sys[20];
int ans[maxm];

int init (int n, int d, int mod)
{
  int lmt = 1, dep = 0, cnt = 0;
  for (int j = n - 1; j; j /= d, lmt *= d + 1, ++dep);
  for (int i = 0, j, k, mul; i < lmt; ++i)
    {
      f[i] = 1; 
      for (j = 0, k = i, mul = 1; j < dep; ++j, k /= d + 1, mul *= 1 + d)
        if (k % (d + 1) == d)
          {
            for (int x = 1; x <= d; ++x)
              (f[i] *= f[i - x * mul]) %= mod;
            break;
          }
      if (j == dep)
        f[i] = a[cnt] % mod, cnt += cnt != n;
    }
  return lmt;
}

int groups[][11] = {
  {9, 2, 3, 5, 7, 11, 13, 17, 19, 23},
  {5, 29, 31, 37, 41, 43},
  {4, 47, 53, 59, 61},
  {4, 67, 71, 73, 79},
  {3, 83, 89, 97}
};

int convert (char c)
{
  if (c <= '9') return c - '0';
  return c - 'A' + 10;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("156E.in" , "r", stdin);
  freopen ("156E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, d;

  cin >> n;
  fill (a, a + maxn, 1);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  cin >> m;
  for (int i = 1; i <= m; ++i)
    cin >> d >> S[i] >> c[i], sys[d].push_back (i);

  memset (ans, -1, sizeof (ans));
  for (int L = 0; L < 5; ++L)
    {
      int v = 1;
      for (int i = 1; i <= groups[L][0]; ++i)
        v *= groups[L][i];

      for (int d = 2; d <= 16; ++d)
        {
          if (sys[d].empty ()) continue;
          // cerr << d << endl << flush;
          int lmt = init (n, d, v);
          // cerr << d << endl << flush;
          foreach (it, sys[d])
            {
              if (ans[*it] != -1) continue;
              int64 x = 0, v = 1, i;
              for (i = sz_m (S[*it]) - 1; i >= 0 && v < lmt; --i)
                {
                  if (S[*it][i] != '?')
                    x += v * convert (S[*it][i]);
                  else
                    x += v * d;
                  v *= d + 1;
                }
              // cerr << "step1" << endl;
              for (; i >= 0; --i)
                if (S[*it][i] != '?' && S[*it][i] != '0')
                  break;
              if (i >= 0) continue;
              // cerr << "step2" << endl;
              // if (x >= lmt) continue;
              x = f[x] + c[*it];
              for (int i = 1; i <= groups[L][0]; ++i)
                if (x % groups[L][i] == 0)
                  {ans[*it] = groups[L][i]; break; }
            }
        }
    }

  for (int i = 1; i <= m; ++i)
    cout << ans[i] << endl;
  
  // n = 10000, m = 30000;
  // cout << n << endl;
  // for (int i = 1; i <= n; ++i)
  //   cout << ((int64)rand () | (int64)rand () << 30) << " ";
  // cout << endl << m << endl;
  // for (int i = 1; i <= m; ++i)
  //   cout << rand () % 15 + 2 << " ?????????? " << ((int64)rand () | (int64)rand () << 30) << endl;
  return 0; 
}
