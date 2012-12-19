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

const int maxn = 1100, maxm = 1100;

int n, m, K;

int ufs[maxn], pos[maxn], room[maxn];
PII E[maxm];
map<string, int> f;

int find (int t) {return ufs[t] != t ? ufs[t] = find (ufs[t]) : t; }

VI work ()
{
  VI ret; string S;

  for (int i = 1; i <= n; ++i)
    ufs[i] = i;
  for (int i = 1, j, k; i <= K; ++i)
    {
      cin >> S; 
      if (!f.count (S)) f[S] = i;
      int x = f[S];
      cin >> room[x] >> k;
      for (; k--; )
        cin >> j, pos[j] = room[x];
    }
  for (bool b = true; b; )
    {
      b = false;
      for (int i = 1; i <= m; ++i)
        {
          int L = find (E[i].Px), R = find (E[i].Py), z = find (pos[i]);
          if (L != R && (L == z || R == z))
            b = true, ufs[min (L, R)] = max (L, R);
        }
    }
  sort (iter (ret));
  for (int i = 1; i <= m; ++i)  // which edges can be chosen
    if (find (E[i].Px) == find (E[i].Py))
      ret.push_back (i);
  for (int i = 1; i <= K; ++i)  // everyone's position
    ret.push_back (find (room[i]));
  for (int i = 1; i <= m; ++i)  // keys' position
    ret.push_back (find (pos[i]));
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("46F.in" , "r", stdin);
  freopen ("46F.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  cin >> n >> m >> K;
  for (int i = 1; i <= m; ++i)
    cin >> E[i].Px >> E[i].Py;

  VI x = work (), y = work ();
  if (x == y) cout << "YES" << endl;
  else cout << "NO" << endl;
  return 0; 
}
