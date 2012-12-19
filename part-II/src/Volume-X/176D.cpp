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

const int maxn = 2200, maxm = 2200, maxt = 2200;

vector<vector<vector<int>>> nc;
vector<vector<int>> nb, lnk;
int n, m;
string S[maxn], T;
int blks[maxm];
pair<int, int> f[maxt][maxt];

void init_str (string &S, vector<vector<int>> &vec)
{
  int len = SZ (S);
  vec.resize (len + 1);
  vec[len].resize (26);
  fill (ALL (vec[len]), oo);
  for (int j = len - 1; j >= 0; --j)
    {
      vec[j] = vec[j + 1];
      vec[j][S[j] - 'a'] = j;
    }
}

void init ()
{
  nc.resize (n);
  for (int i = 0; i < n; ++i)
    init_str (S[i], nc[i]);
  init_str (T, lnk);

  nb.resize (m + 1);
  nb[m].resize (26);
  fill (ALL (nb[m]), oo);
  for (int i = m - 1; i >= 0; --i)
    {
      nb[i] = nb[i + 1];
      for (int j = 0; j < 26; ++j)
        if (nc[blks[i]][0][j] != oo)
          nb[i][j] = i;
    }
}

pair<int, int> find_next_char (pair<int, int> now, int c)
{
  // cerr << "query: " << now.Px << " " << now.Py << " " << c << endl;
  if (nc[blks[now.Px]][now.Py + 1][c] == oo)
    now.Px = nb[now.Px + 1][c], now.Py = -1;
  if (now.Px == oo) return // cerr << "ret: <oo, 0>" << endl,
                      MKP (oo, 0);
  // cerr << "ret: <" << now.Px << ", " << nc[blks[now.Px]][now.Py + 1][c] << ">" << endl;
  return MKP (now.Px, nc[blks[now.Px]][now.Py + 1][c]);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("176D.in" , "r", stdin);
  freopen ("176D.out", "w", stdout); 
#endif
  ios_base::sync_with_stdio (false);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> S[i];
  cin >> m;
  for (int i = 0; i < m; ++i)
    cin >> blks[i], --blks[i];
  cin >> T;

  init ();

  // find_next_char (MKP (0, 0), 3);
  // return 0;
  
  memset (f, 0x3F, sizeof (f));
  f[0][0] = MKP (0, -1);
  int ans = 0;
  for (int i = 0; i <= SZ (T); ++i)
    for (int j = 0; j <= i + 1; ++j)
      if (f[i][j].Px != oo)
        {
          // cerr << "now: " << i << ", " << j << endl;
          for (int c = 0; c < 26; ++c)
            if (lnk[i][c] != oo)
              chkmin (f[lnk[i][c] + 1][j + 1], find_next_char (f[i][j], c));
          ans = max (ans, j);
        }
  cout << ans << endl;
  return 0; 
}

