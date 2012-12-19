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

const int maxn = 33, maxv = 16;

Graph<int> G (maxv);
char S[maxn][maxn];
bool saved = false;
int col[maxv], bak[maxv];
int o[maxv][maxv], tms, ans;
int rep[maxn][maxn];
vector<PII> vec;

void search (int x)
{
  if (x > 14)
    {
      ++tms;
      for (int v = 1; v <= 14; ++v)
        foreach (e, G[v])
          {
            if (o[col[v]][col[*e]] == tms)
              return ;
            o[col[v]][col[*e]] = o[col[*e]][col[v]] = tms;
          }
      if (!saved) memcpy (bak, col, sizeof (bak));
      // for (int i = 1; i <= 14; ++i)
      //   cerr << col[i] << " ";
      // cerr << endl;
      ++ans, saved = true;
      return ;
    }
  if (~col[x]) return search (x + 1);
  int z = 0;
  foreach (e, G[x])
    if (col[*e] != -1)
      z |= 1 << col[*e];
  z ^= 127;
  
  for (int i = 0; i <= 6; ++i)
    if (z >> i & 1)
      col[x] = i, search (x + 1);
  col[x] = -1;
}

void dfs (int x, int now)
{
  if (x == sz_m (vec))
    return now == 7 ? search (1) : (void)0;
  dfs (x + 1, now);
  if (col[vec[x].Px] == -1 && col[vec[x].Py] == -1 && now <= 6)
    {
      col[vec[x].Px] = now, col[vec[x].Py] = now;
      dfs (x + 1, now + 1);
      col[vec[x].Px] = -1 , col[vec[x].Py] = -1;
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("97A.in" , "r", stdin);
  freopen ("97A.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m, tot = 0;
  
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> (S[i] + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (S[i][j] != '.' && !rep[i][j])
        {
          ++tot;
          for (int x = 0; x < 2; ++x)
            for (int y = 0; y < 2; ++y)
              rep[i + x][j + y] = tot;
        }
  
  for (int i = 1; i <= n; ++i)
    {
      for (int j = 1; j <= m; ++j)
        cerr << rep[i][j] << " ";
      cerr << endl;
    }

  int cnt = 0;
  memset (col, -1, sizeof (col));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (S[i][j] != '.')
        for (int x = 0, y = 1; x <= 1; ++x, --y)
          if (S[i][j] == S[i + x][j + y])
            {
              if (rep[i][j] == rep[i + x][j + y])
                col[rep[i][j]] = cnt++, cerr << rep[i][j] << endl;
              else
                G.add (rep[i][j], rep[i + x][j + y]);
            }

  for (int i = 1; i <= 14; ++i)
    for (int j = 1; j <= 14; ++j)
      if (count (iter (G[i]), j) == 1)
        vec.push_back (MKP (i, j)), cerr << "pushed: " << i << " " << j << endl;

  dfs (0, cnt);
  // search (1);
  cout << ans * 5040 << endl;
  for (int i = 1; i <= n; ++i)
    {
      for (int j = 1; j <= m; ++j)
        if (S[i][j] != '.')
          cout << bak[rep[i][j]];
        else
          cout << ".";
      cout << endl;
    }

  cerr << 1.0 * clock () / CLOCKS_PER_SEC << endl;
  return 0; 
}
