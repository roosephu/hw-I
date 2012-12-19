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

vector<PII> w;

bool cmp (PII a, PII b)
{
  // if (a.Px != b.Px) 
    return a.Px < b.Px;
  // return (a.Py < b.Py) == (a.Px < 0);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("39A.in" , "r", stdin);
  freopen ("39A.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int64 a; string S;
  
  cin >> a >> S; S = "+" + S;
  for (int i = 0; i < sz_m (S); )
    {
      int coef = 1, sgn = S[i] == '+' ? 1 : -1; ++i;
      if (isdigit (S[i]))         // split coef
        {
          coef = 0;
          for (; isdigit (S[i]); ++i)
            coef = coef * 10 + S[i] - '0';
          ++i;
        }

      coef *= sgn;
      w.push_back (MKP (coef, S[i] == 'a'));
      cerr << coef << " " << S[i] << endl;
      i += 3;
    }
  
  sort (iter (w), cmp);
  int64 ans = 0;
  foreach (it, w)
    {
      if (it->Py == 0)
        ++a;
      ans += it->Px * a;
      if (it->Py == 1)
        ++a;
    }
  cout << ans << endl;
  return 0; 
}
