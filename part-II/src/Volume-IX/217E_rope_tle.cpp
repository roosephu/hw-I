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
#include <ext/rope>

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

const int maxn = 5500;

int L[maxn], R[maxn], lmt[maxn];

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("217E.in" , "r", stdin);
  freopen ("217E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  string S; __gnu_cxx::rope<char> T;
  int K, n;

  cin >> S >> K >> n;
  for (int i = 1; i <= n; ++i)
    cin >> L[i] >> R[i];

  lmt[n] = K;
  for (int i = n; i; --i)
    lmt[i - 1] = min (max (lmt[i] - (R[i] - L[i] + 1), R[i]), lmt[i]);

  for (int i = 0; i < lmt[0]; ++i)
    T.insert (i + 1, S[i]);
  // cout << T << endl;
  for (int i = 1; i <= n; ++i)
    {
      if (R[i] >= lmt[i]) continue;
      int even = R[i], odd = R[i];
      auto ptr = T.begin () + (L[i] - 1);
      for (int x = L[i]; x <= R[i]; ++x, ++odd, ++ptr)
        {
          if ((x ^ L[i]) & 1)              // even
            T.insert (even, T[x - 1]), ++even;
          else
            T.insert (odd, T[x - 1]);
          // cout << T << endl;
        }
      for (; sz_m (T) > lmt[i]; T.pop_back ());
    }

  cout << T << endl;
  return 0; 
}





