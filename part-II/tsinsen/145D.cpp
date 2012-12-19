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
#ifdef WIN32
#define fmt64 "%I64d"
#else
#define fmt64 "%lld"
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

const int maxn = 110000;

int n, m;
int a[maxn], pred[maxn], succ[maxn];
vector<int> pos;
int sz;

int64 calc (int L)
{
  int64 ret = 0, now = 0; set<int> S; S.insert (n + 1);
  for (int x = sz; x > L; --x)
    {
      int64 t = pos[x] - pos[x - 1] - 1;
      now += t * (t + 1) / 2;
      S.insert (pos[x - 1]);
      if (pos[x] <= n && pred[pos[x]] < pos[L])
        for (int i = pos[x]; i; i = succ[i]) // merge intervals
          {
            auto it = S.find (i), pre = it, nxt = it;
            int64 a = *--pre, b = *++nxt;
            now += (i - a) * (b - i);
            S.erase (it);
          }

      int64 w = *++S.begin () - *S.begin () - 1;
      ret += (t + 1) * (now - w * (w + 1) / 2) + w * (w + 1) * (w + 2) / 6 - (w - t + 1) * (w - t) * (w - t - 1) / 6;
      // cvar (now), evar (ret);
    }
  return ret;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("145D.in" , "r", stdin);
  freopen ("145D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);
  
  cin >> n; UMII f;
  
  pos.push_back (0);
  for (int i = 1; i <= n; ++i)
    {
      cin >> a[i];
      succ[pred[i] = f[a[i]]] = i;
      f[a[i]] = i;

      for (int x = a[i]; x; x /= 10)
        if (x % 10 != 4 && x % 10 != 7)
          pred[i] = -1;

      if (pred[i] != -1)
        pos.push_back (i);
    }

  // for (auto &x : pos)
  //   cerr << x << " ";
  // cerr << endl;
  
  sz = sz_m (pos);
  int64 ans = 0;
  pos.push_back (n + 1);
  for (int i = 1; i < sz; ++i)
    ans += (pos[i] - pos[i - 1]) * calc (i);

  evar (ans);
  
  for (int i = 1; i <= sz; ++i)
    for (int x = pos[i - 1] + 1; x < pos[i]; ++x)
      ans += (n - x + 1ll) * (n - x) / 2 * (x - pos[i - 1]);

  // int now = 0;
  // for (int i = 1; i <= n; ++i)
  //   for (int j = i; j <= n; ++j)
  //     for (int x = j + 1; x <= n; ++x)
  //       for (int y = x; y <= n; ++y)
  //         // if ((i <= 4 && 4 <= j)  || (i <= 7 && 7 <= j))
  //           ++now;
  // evar (now);
  
  cout << ans << endl;
  return 0; 
}
