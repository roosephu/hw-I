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

const int maxn = 220000, maxbuf = 1 << 22 | 50;

int val[maxn], len, mask, sum[maxn], f[maxn];
// map<int, int> z[21];
int buf[maxbuf], *z[22];

int cost (int p, int q)
{
  int bitmask = mask;
  for (int i = 0; i < len; ++i, bitmask >>= 1)
    if ((val[p] & bitmask) == (val[q] >> i))
      return i;
  return len;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("83E.in" , "r", stdin);
  freopen ("83E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> n; string S;
  for (int i = 1; i <= n; ++i)
    cin >> S, val[i] = bitset<20>(S).to_ulong ();
  len = S.size (), mask = (1 << len) - 1;
  for (int i = 0, *ptr = buf; i <= len; ++i)
    z[i] = ptr, ptr += 2 << (len - i);
  memset (buf, 0x3F, sizeof (buf));
  
  int ans = oo; sum[1] = len;
  for (int i = 1; i <= n; ++i)
    {
      sum[i + 1] = sum[i] + (i == n ? 0 : cost (i, i + 1));
      f[i] = sum[i - 1] + len;
      for (int j = 0, v = val[i]; j <= len; ++j, v >>= 1)
        f[i] = min (f[i], z[j][v] + j + sum[i - 1]);

      if (i != 1)
        {
          for (int j = 0, B = mask, v; v = B & val[i - 1], j <= len; ++j, B >>= 1)
            z[j][v] = min (z[j][v], f[i] - sum[i]);
          ans = min (ans, f[i] - sum[i]);
        }
      
      // cvar (i), evar (f[i]);
    }
  cout << min (sum[n], ans + sum[n]) << endl;

  // disp (sum + 1, n);
  
  return 0; 
}
