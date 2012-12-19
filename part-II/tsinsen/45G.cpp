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
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

const int maxn = 6600;

int ans[maxn];
bool prime[maxn * maxn];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("45G.in" , "r", stdin);
  freopen ("45G.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
 
  int n, sum;
  cin >> n;
  if (n == 2) return cout << "1 1" << endl, 0;
  sum = n * (n + 1) / 2;
  prime[1] = 1;
  for (int i = 2; i <= sum; ++i)
    if (!prime[i] && sum / i >= i)
      for (int j = i * i; j <= sum; j += i)
        prime[j] = true;

  bool odd = sum & 1;
  if (odd)
    {
      if (!prime[sum - 2])
        {
          cout << "1 2";
          for (int i = 3; i <= n; ++i)
            cout << " 1";
          cout << endl;
          return 0;
        }
      sum -= 3;
      
    }
  
  int part;
  for (part = 2; part <= sum; ++part)
    if (!prime[part] && !prime[sum - part])
      break;
  // cerr << sum << " " << part << endl;

  for (int i = 1; i <= n; ++i)
    ans[i] = 2;
  for (int i = n; i; --i)
    if (part >= i)
      ans[i] = 1, part -= i;
  if (odd && ans[3] == 1) ans[1] = ans[2] = 3;
  else if (odd) ans[3] = 3;
  for (int i = 1; i <= n; ++i)
    cout << ans[i] << " ";

  return 0; 
}
