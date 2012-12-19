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
#define UNIQ(x) sort (ALL (x)), x.resize (unique (ALL (x)) - x.begin ());
#ifdef WIN32
#define fmt64 "%I64d"
#else
#define fmt64 "%lld"
#endif

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

struct gripper { int m, p; int64 x, y, r, d;} ;

const int maxn = 260000;

gripper g[maxn];
int ans;
vector<int64> distances;
queue<int> Q;
set<pair<int, int>> bit[maxn];
set<pair<int, int>>::iterator lnk[maxn];
int n, lmt;
int pos[maxn], o[maxn];

void insert (int x, int t)
{
  for (pos[t] = x; x <= lmt; x += x & -x)
    bit[x].insert (MKP (g[t].m, t));
}

void erase (int t)
{
  if (o[t]) return ;
  // int x = pos[t];
  Q.push (t), ++ans, o[t] = true;
  // for (; x <= lmt; x += x & -x)
  //   bit[x].erase (MKP (g[t].m, t));
}

int hasher (int64 x)
{
  return upper_bound (ALL (distances), x) - distances.begin ();
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("198E.in" , "r", stdin);
  freopen ("198E.out", "w", stdout);
#endif
  // ios_base::sync_with_stdio (false);
  
  // cin >> g[0].x >> g[0].y >> g[0].p >> g[0].r >> n;
  scanf (fmt64 fmt64 "%d" fmt64 "%d", &g[0].x, &g[0].y, &g[0].p, &g[0].r, &n);
  for (int i = 1; i <= n; ++i)
    // cin >> g[i].x >> g[i].y >> g[i].m >> g[i].p >> g[i].r;
    scanf (fmt64 fmt64 "%d" "%d" fmt64, &g[i].x, &g[i].y, &g[i].m, &g[i].p, &g[i].r);
  for (int i = 0; i <= n; ++i)
    {
      g[i].d = sqr (g[i].x - g[0].x) + sqr (g[i].y - g[0].y);
      distances.push_back (g[i].d);
    }
  UNIQ (distances);

  lmt = n + 2;
  for (int i = 1; i <= n; ++i)
    insert (hasher (g[i].d), i);
  for (int i = 1; i <= lmt; ++i)
    lnk[i] = bit[i].begin ();

  for (Q.push (0); !Q.empty (); Q.pop ())
    for (int x = Q.front (), z = hasher (g[x].r * g[x].r); z; z &= z - 1)
      for (; lnk[z] != bit[z].end () && lnk[z]->Px <= g[x].p; ++lnk[z])
        erase (lnk[z]->Py);

  printf ("%d\n", ans);
  // cout << ans << endl;
  // cvar (ans);
  return 0; 
}
