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

const int maxn = 2200;

int T[maxn][maxn];
real aux[maxn][maxn];
pair<int, int> ans;
int n;

void gauss_blur (int n)
{
  const real sigma = 0.8, pi = acos (-1); real total = 0, w[3][3] = {{0}};

  for (int i = -1; i <= 1; ++i)
    for (int j = -1; j <= 1; ++j)
      {
        w[i + 1][j + 1] = exp (- (i * i + j * j) / (2 * sigma * sigma)) / (2 * pi * sigma * sigma);
        total += w[i + 1][j + 1];
      }

  memset (aux, 0, sizeof (aux));
  for (int x = 1; x <= n; ++x)
    for (int y = 1; y <= n; ++y)
      for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
          {
            int a = x + i <= 0 || x + i > n ? (x - i) : (x + i), b = (y + j) <= 0 || y + j > n ? (y - j) : (y + j);
            aux[x][y] += T[a][b] * w[i + 1][j + 1];
          }
  for (int x = 1; x <= n; ++x)
    for (int y = 1; y <= n; ++y)
      T[x][y] = aux[x][y] <= total * 0.5 ? 0 : 1;
}

vector<pair<int, int>> Q;
bool o[maxn][maxn];
int enter;

void enque (int x, int y)
{
  if (1 <= x && x <= n && 1 <= y && y <= n && !o[x][y])
    o[x][y] = 1, Q.push_back (MKP (x, y));
}

void check (pair<int, int> p, bool solve)
{
  Q.clear (); enter = 0, enque (p.Px, p.Py);
  // cerr << p.Px << " " << p.Py << endl;
  int head = 0;
  for (; head != SZ (Q); ++head)
    for (int i = -1; i <= 1; ++i)
      for (int j = -1; j <= 1; ++j)
        if (abs (i) + abs (j) == 1 && T[Q[head].Px][Q[head].Py] == T[Q[head].Px + i][Q[head].Py + j])
          enque (Q[head].Px + i, Q[head].Py + j);
  if (SZ (Q) < 200)
    {
      for (auto &p : Q)
        T[p.Px][p.Py] ^= 1;
      return ;
    }
  if (!solve) return ;

  real cx = 0, cy = 0; int n = SZ (Q);
  real R = 0;
  for (auto &p : Q)
    cx += p.Px, cy += p.Py;
  cx /= n, cy /= n;
  for (auto &p : Q)
    chkmax (R, hypot (cx - p.Px, cy - p.Py));

  // cerr << n << " " << R << endl;
  if (n < 2.5 * R * R) // square
    ++ans.Py;
  else
    ++ans.Px;
}

int main ()
{
#ifndef ONLINE_JUDGE
  // freopen ("178E3.in" , "r", stdin);
  freopen ("easy_1.in" , "r", stdin);
  freopen ("178E3.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  // cout << setprecision (20) << endl;

  // cout << sigma << " " << calc (sigma) << endl;

  cin >> n;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      cin >> T[i][j];
  for (int i = 1; i <= 10; ++i)
    gauss_blur (n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (!o[i][j])
        check (MKP (i, j), 0);  
  // for (int i = 1; i <= n; ++i)
  //   for (int j = 1; j <= n; ++j)
  //     cout << T[i][j] << (j == n ? "\n" : " ");
  memset (o, 0, sizeof (o));
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (T[i][j] && !o[i][j])
        check (MKP (i, j), 1);  

  cout << ans.Px << " " << ans.Py << endl;
  return 0; 
}
