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

bool noans;
vector<vector<PII> > blk;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
const int maxn = 1100;

char S[maxn][maxn];
int rep[maxn][maxn];
int col[maxn * maxn];

PII _put (int x, int y) {return rep[x][y] = sz_m (blk) + 1, S[x][y] = '.', MKP (x, y); }
void put (int x, int y, int dx, int dy)
{
  vector<PII> t;
  t.push_back (_put (x - dx, y - dy));
  t.push_back (_put (x     , y     ));
  t.push_back (_put (x + dx, y + dy));
  blk.push_back (t);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("44J.in" , "r", stdin);
  freopen ("44J.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m;
  
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> (S[i] + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (S[i][j] == 'b')
        noans = true;
      else if (S[i][j] == 'w' && S[i][j + 1] == 'b' && S[i][j + 2] == 'w')
        put (i, j + 1, 0, 1);
      else if (S[i][j] == 'w' && S[i + 1][j] == 'b' && S[i + 2][j] == 'w')
        put (i + 1, j, 1, 0);
      else if (S[i][j] == 'w')
        noans = true;

  if (noans) return cout << "NO" << endl, 0;
  for (int b = 0; b < sz_m (blk); )
    {
      bool c[6] = {0};
      foreach (it, blk[b])
        for (int i = 0; i < 4; ++i)
          c[col[rep[it->Px + dx[i]][it->Py + dy[i]]]] = true;
      ++b;
      for (; col[b] <= 4 && c[col[b]]; ++col[b]);
      if (col[b] == 5)
        return cout << "NO" << endl, 0;
      assert (col[b] != 5);
    }

  cout << "YES" << endl;
  for (int i = 1; i <= n; ++i)
    {
      for (int j = 1; j <= m; ++j)
        if (rep[i][j])
          cout << (char)(col[rep[i][j]] + 'a' - 1);
        else
          cout << '.';
      cout << endl;
    }
  return 0; 
}
