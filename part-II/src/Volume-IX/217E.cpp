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
#define sz_m(x) (int)((x).size ())
#define iter(x) (x).begin (), (x).end ()

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

const int maxn = 5500, maxk = 3300000, base = 4194304;

int st[base << 1 | 10], f[maxk], ufs[maxk], L[maxn], R[maxn];
char S[maxk], T[maxk];
int K, ybeg, yend;

void update (int x) {st[x] = st[x << 1] + st[x << 1 | 1]; }

void clear (int L, int R)
{
  for (L += base - 1, R += base + 1; L ^ R ^ 1; )
    {
      if (~L & 1) st[L ^ 1] = 0;
      if ( R & 1) st[R ^ 1] = 0;
      update (L >>= 1), update (R >>= 1);
    }
  for (; L; update (L), L >>= 1);
}

int query (int x)
{
  // cerr << "query: " << x << " ";
  int t = 1;
  for (; t < base; )
    if (st[t << 1] >= x)
      t <<= 1;
    else
      x -= st[t << 1], t = t << 1 | 1;
  return t - base;
}

int find (int t) {return ufs[t] != t ? ufs[t] = find (ufs[t]) : t; }

void fill (int x, int v)
{
  // cerr << "fill: " << x << " # " << v << endl;
  yend = x, f[x] = v, ufs[x] = find (x + 1);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("217E.in" , "r", stdin);
  freopen ("217E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> (S + 1) >> K >> n; ufs[K + 1] = K + 1;
  for (int i = 1; i <= K; ++i)
    ufs[i] = i, st[i + base] = 1;
  for (int i = base - 1; i; --i)
    update (i);

  for (int i = 1; i <= n; ++i)
    cin >> L[i] >> R[i], ++R[i];
  for (int i = n, y; i; --i)
    if (R[i] <= K && (y = query (R[i])) <= K)
      {
        // cerr << "--------------------" << endl;
        ybeg = y;
        for (int t = L[i] + 1, x = query (t); t < R[i] && y <= K; t += 2)
          fill (y, x), y = find (y + 1), x = find (x + 1), x = find (x + 1);
        for (int t = L[i] + 0, x = query (t); t < R[i] && y <= K; t += 2)
          fill (y, x), y = find (y + 1), x = find (x + 1), x = find (x + 1);
        clear (ybeg, yend);
      }
  for (int i = 1, j = 1; i <= K; ++i)
    T[i] = f[i] ? T[f[i]] : S[j++];
  // for (int i = 1; i <= K; ++i)
  //   evar (f[i]);

  cout << T + 1 << endl;
  return 0; 
}
