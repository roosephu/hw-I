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

const int maxlen = 16, base = 100000000;

struct mpz
{
  int f[maxlen], len;

  mpz () : len (0){fill (f, f + maxlen, 0);}
  mpz (int x) : len (1) {fill (f, f + maxlen, 0); f[1] = x; }
};

ostream &operator << (ostream &os, const mpz &z)
{
  os << z.f[z.len];
  for (int i = z.len - 1; i > 0; --i)
    os << setw (8) << setfill ('0') << z.f[i];
  return os;
}

mpz operator * (const mpz &a, const mpz &b)
{
  int64 tmp[maxlen] = {0}; mpz ret; ret.len = a.len + b.len;
  for (int i = 1; i <= a.len; ++i)
    for (int j = 1; j <= b.len; ++j)
      tmp[i + j - 1] += (int64)a.f[i] * b.f[j];
  for (int i = 1; i <= ret.len; ++i)
    ret.f[i] = tmp[i] % base, tmp[i + 1] += tmp[i] / base;
  while (ret.len && !ret.f[ret.len]) --ret.len;
  // cerr << "multiply: " << a << " " << b << " " << ret << endl;
  return ret;
}

bool operator < (const mpz &a, const mpz &b)
{
  if (a.len != b.len) return a.len < b.len;
  for (int i = a.len; i; --i)
    if (a.f[i] != b.f[i])
      return a.f[i] < b.f[i];
  return false;                 // equal
}

const int maxn = 770;

Graph<int> G;
mpz f[maxn][maxn], g[maxn];
int size[maxn];

void dfs (int v, int fa)
{
  size[v] = 1, g[v] = f[v][1] = 1;
  
  for (auto &u : G[v])
    if (u != fa)
      {
        dfs (u, v);
        size[v] += size[u];
        for (int i = size[v]; i; --i)
          {
            f[v][i] = f[v][i] * g[u];
            for (int j = 1; j <= 2 && j <= i && j <= size[u]; ++j)
              {
                chkmax (f[v][i], f[u][j] * f[v][i - j]);
                chkmax (f[v][i], f[v][j] * f[u][i - j]);
              }
          }
      }

  for (int i = 1; i <= size[v]; ++i)
    chkmax (g[v], f[v][i] * i);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("23E.in" , "r", stdin);
  freopen ("23E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> n; G.resize (n);
  for (int i = 1, s, t; i < n; ++i)
    cin >> s >> t, G.add (s, t), G.add (t, s);
  dfs (1, 0);

  // mpz a (9999999),  b (9999999);
  // cerr << a * b << endl;
  
  cout << g[1] << endl;
  // cerr << g[1] << endl;
  return 0; 
}
