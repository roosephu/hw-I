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

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef long double real;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef unordered_map<int, int> UMII;
typedef unordered_set<int> USI;
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

const int maxn = 1100;

vector<PII> ans, dots;
PII p[4];
vector<int> xs, ys;
int ox[5], oy[5];
char S[maxn][maxn];

bool cover_all ()
{
  int cirA = 2 * (p[1].Px + p[1].Py - p[0].Px - p[0].Py + 0);
  int cirB = 2 * (p[3].Px + p[3].Py - p[2].Px - p[2].Py + 0);
  // cout << "YES: " << cirA << " " << cirB << endl
  //      << p[0].Px << " " << p[0].Py << " " << p[1].Px << " " << p[1].Py << endl
  //      << p[2].Px << " " << p[2].Py << " " << p[3].Px << " " << p[3].Py << endl;
  for (auto &z : dots)
    {
      bool b = false;
      if (((z.Px == p[0].Px || z.Px == p[1].Px) && p[0].Py <= z.Py && z.Py <= p[1].Py) ||
          ((z.Py == p[0].Py || z.Py == p[1].Py) && p[0].Px <= z.Px && z.Px <= p[1].Px))
        b = true, --cirA;
      if (((z.Px == p[2].Px || z.Px == p[3].Px) && p[2].Py <= z.Py && z.Py <= p[3].Py) ||
          ((z.Py == p[2].Py || z.Py == p[3].Py) && p[2].Px <= z.Px && z.Px <= p[3].Px))
        b = true, --cirB;
      if (!b) return false;
    }
  return !cirA && !cirB;
}

void dfs (int d)
{
  if (SZ (ans)) return ;
  if (d == 4)
    {
      if (p[1].Px - p[0].Px < 2 || p[1].Py - p[0].Py < 2) return ;
      if (p[3].Px - p[2].Px < 2 || p[3].Py - p[2].Py < 2) return ;
      // for (int i = 0; i < SZ (xs); ++i) if (!ox[i]) return ;
      // for (int i = 0; i < SZ (ys); ++i) if (!oy[i]) return ;
      if (!cover_all ()) return ;
      ans = vector<PII>(p, p + 4);
      return ;
    }
  for (int i = 0; i < SZ (xs); ++i)
    for (int j = 0; j < SZ (ys); ++j)
      {
        ++ox[i], ++oy[j];
        p[d] = MKP (xs[i], ys[j]), dfs (d + 1);
        --ox[i], --oy[j];
      }
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("152D.in" , "r", stdin);
  freopen ("152D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m;
  
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> (S[i] + 1);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (S[i][j] == '#')
        {
          if (j != 1 && j != m && S[i][j - 1] == '#' && S[i][j + 1] == '#')
            xs.push_back (i);
          if (i != 1 && i != m && S[i + 1][j] == '#' && S[i - 1][j] == '#')
            ys.push_back (j);

          dots.push_back (MKP (i, j));
        }
  sort (ALL (ys));
  xs.resize (unique (ALL (xs)) - xs.begin ());
  ys.resize (unique (ALL (ys)) - ys.begin ());

  // for (auto &x : xs)
  //   cerr << x << endl;
  // for (auto &x : ys)
  //   cerr << x << endl;

  // if (SZ (xs) > 4 && SZ (ys) > 4)
  //   return cout << "NO" << endl, 0;
  if (SZ (xs) > 4) xs.erase (++++xs.begin (), ----xs.end ());
  if (SZ (ys) > 4) ys.erase (++++ys.begin (), ----ys.end ());

  cvar (SZ (xs)), evar (SZ (ys));
  // cerr << "dfs" << endl;
  dfs (0);

  // if (SZ (xs) == 4)
  //   {
  //     int ymin = ys[0], ymax = *--ys.end ();
  //     p[0] = MKP (xs[0], ymin), p[1] = MKP (xs[2], ymax);
  //     p[2] = MKP (xs[1], ymin), p[3] = MKP (xs[3], ymax);
  //     if (cover_all ()) ans = vector<PII>(p, p + 4);
  //   }
  // if (SZ (ys) == 4)
  //   {
  //     int xmin = xs[0], xmax = *--xs.end ();
  //     p[0] = MKP (xmin, ys[0]), p[1] = MKP (xmax, ys[2]);
  //     p[2] = MKP (xmin, ys[1]), p[3] = MKP (xmax, ys[3]);
  //     if (cover_all ()) ans = vector<PII>(p, p + 4);
  //   }
  
  if (SZ (ans) == 0) cout << "NO" << endl;
  else
    cout << "YES" << endl
         << ans[0].Px << " " << ans[0].Py << " " << ans[1].Px << " " << ans[1].Py << endl
         << ans[2].Px << " " << ans[2].Py << " " << ans[3].Px << " " << ans[3].Py << endl;
  return 0; 
}
