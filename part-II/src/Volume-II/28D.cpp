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

const int maxn = 110000;

int v[maxn], L[maxn], R[maxn], c[maxn];
map<PII, PII> f;
PII ans = MKP (0, 0), prev[maxn];

PII query (int L, int R)
{
  PII p = MKP (L, R);
  if (!f.count (p)) f[p] = MKP (L ? -oo : 0, 0);
  return f[p];
}

void update (int L, int R, int c, PII v)
{
  // cerr << L << " " << R << " " << v.Px << " " << v.Py << endl;
  if (R == 0) ans = max (ans, v);
  PII x = max (query (L + c, R), v);
  f[MKP (L + c, R)] = x;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("28D.in" , "r", stdin);
  freopen ("28D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> n;
  for (int i = 1; i <= n; ++i)
    {
      cin >> v[i] >> c[i] >> L[i] >> R[i];
      prev[i] = query (L[i], R[i] + c[i]);
      update (L[i], R[i], c[i], MKP (prev[i].Px + v[i], i));
    }

  VI out;
  for (int i = ans.Py; i; i = prev[i].Py)
    out.push_back (i);
  cout << sz_m (out) << endl;
  for (int i = sz_m (out) - 1; i >= 0; --i)
    cout << out[i] << " ";
  return 0; 
}
