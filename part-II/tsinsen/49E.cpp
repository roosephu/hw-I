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

const int maxn = 55;

vector<vector<int> > f, g;
vector<PII> G[27];
int h[maxn][maxn];

void work (string S, vector<vector<int> > &f)
{
  int n = sz_m (S);
  f.resize (n);
  for (int i = 0; i < n; ++i)
    f[i].resize (n + 1), f[i][i + 1] = 1 << (S[i] - 'a');
  for (int i = n - 1; i >= 0; --i)
    for (int j = i + 2; j <= n; ++j)
      for (int c = 0; c < 26; ++c)
        for (int k = i + 1; k < j; ++k)
          foreach (it, G[c])
            if ((f[i][k] >> it->Px & 1) && (f[k][j] >> it->Py & 1))
              {f[i][j] |= 1 << c; break;}
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("49E.in" , "r", stdin);
  freopen ("49E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n; string s1, s2, S;
  
  cin >> s1 >> s2 >> n;
  for (int i = 1; i <= n; ++i)
    {
      cin >> S;
      int c = S[0] - 'a', x = S[3] - 'a', y = S[4] - 'a';
      G[c].push_back (MKP (x, y));
    }
  work (s1, f), work (s2, g);

  memset (h, 0x3F, sizeof (h)), h[0][0] = 0;
  int l1 = sz_m (s1), l2 = sz_m (s2);
  for (int i = 1; i <= l1; ++i)
    for (int j = 1; j <= l2; ++j)
      for (int a = 0; a < i; ++a)
        for (int b = 0; b < j; ++b)
          if (f[a][i] & g[b][j])
            chkmin (h[i][j], h[a][b] + 1);
  
  if (h[l1][l2] == oo) cout << -1 << endl;
  else cout << h[l1][l2] << endl;
  return 0; 
}
