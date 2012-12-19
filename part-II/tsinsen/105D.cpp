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

const int maxn = 330, TRANSPARENT = -2;

int sx, sy;
int a[maxn][maxn], b[maxn][maxn];
map<int, vector<PII> > syms;
MII panel, ufs, rep;

int calc (int x, int y)
{
  x -= sx, y -= sy;
  int ret = 0, k = max (abs (x), abs (y));
  ret = sqr (2 * k - 1) - 1;
  if (x == -k && -k < y) return ret + y + k; ret += k << 1;
  if (y == +k && -k < x) return ret + x + k; ret += k << 1;
  if (x == +k && -k < y) return ret - y + k; ret += k << 1;
  return ret - x + k; 
}

int cmp (PII a, PII b) {return calc (a.Px, a.Py) < calc (b.Px, b.Py);}
int find (int t) {return ufs[t] ? ufs[t] = find (ufs[t]) : t; }

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("105D.in" , "r", stdin);
  freopen ("105D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m;
  
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> a[i][j], ++panel[a[i][j]];
  for (int i = 1; i <= n; ++i)
    for (int j = 1, x; j <= m; ++j)
      {
        cin >> x, b[i][j] = x;
        if (x != -1 && a[i][j])
          syms[a[i][j]].push_back (MKP (i, j));
      }
  
  cin >> sx >> sy;
  if (b[sx][sy] == -1) return cout << 0 << endl, 0;

  int64 ans = 0; queue<PII> Q;
  Q.push (MKP (sx, sy));

  // sx = sy = 0;
  // for (int i = -5; i <= 5; ++i)
  //   {
  //     for (int j = -5; j <= 5; ++j)
  //       cerr << calc (i, j) << " ";
  //     cerr << endl;
  //   }

  for ( ; !Q.empty (); Q.pop ())
    {
      sx = Q.front ().Px, sy = Q.front ().Py;

      int now = b[sx][sy], old = find (a[sx][sy]); // we need repaint old to now
      if (!now) now = TRANSPARENT;
      if (!old) old = TRANSPARENT;
      if (!rep.count (old)) rep[old] = old;
      
      if (rep[old] == now || rep[old] == TRANSPARENT) continue;
      ans += panel[old];
      cvar (ans), cvar (sx), cvar (sy), cvar (now), cvar (rep[old]), evar (panel[old]);
      if (find (now) == old) rep[old] = now;
      else ufs[old] = now, panel[now] += panel[old];
      
      vector<PII> &sym = syms[old];
      // evar (sz_m (sym));
      sort (iter (sym), cmp);
      foreach (it, sym)
        if (it->Px != sx || it->Py != sy)
          Q.push (*it); //cerr << "push: " << it->Px << " " << it->Py << endl;
      sym.clear ();
    }
  
  cout << ans << endl;
  return 0; 
}
