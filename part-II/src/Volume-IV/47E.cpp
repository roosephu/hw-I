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

const int maxn = 11000, maxm = 110000;
const double eps = 1e-12;

double alpha[maxn], x[maxm], y[maxm];
int idx[maxn], ans[maxn];
priority_queue<pair<double, int> > Q;

bool cmp (int a, int b) {return alpha[a] < alpha[b]; }

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("47E.in" , "r", stdin);
  freopen ("47E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n, m; double V;
  cout << setprecision (15);
  cerr << setprecision (15);
  
  cin >> n >> V;
  for (int i = 1; i <= n; ++i)
    cin >> alpha[i], idx[i] = i; //, cerr << tan (alpha[i]) << endl;
  sort (idx + 1, idx + n + 1, cmp);
  cin >> m;
  for (int i = 1; i <= m; ++i)
    {
      double w;
      cin >> x[i] >> y[i];
      w = x[i] * 9.8 / (V * V);
      if (w > 1 || y[i] == 0) continue;
      double delta = 1 - w * (2 * y[i] / x[i] + w);
      Q.push (MKP (-(1 - sqrt (1 - w * w)) / w      , +i));
      Q.push (MKP (-(1 + sqrt (1 - w * w)) / w - eps, -i));
      if (delta >= 0)
        {
          Q.push (MKP (-(1 - sqrt (delta)) / w - eps, -i));
          Q.push (MKP (-(1 + sqrt (delta)) / w      , +i));
        }
    }

  set<pair<double, int> > S; Q.push (MKP (0, m + 1)); x[m + 1] = oo;
  for (int i = 1; i <= n; )
    {
      double t = Q.top ().Px;
      for (; !S.empty () && i <= n && tan (alpha[idx[i]]) <= -t; ++i)
        ans[idx[i]] = S.begin ()->Py;

      for (; Q.top ().Px == t; Q.pop ())
        if (Q.top ().Py > 0)
          S.insert (MKP (x[Q.top ().Py], Q.top ().Py));
        else
          S.erase (S.find (MKP (x[-Q.top ().Py], -Q.top ().Py)));
    }

  disp (ans + 1, n);
  for (int i = 1; i <= n; ++i)
    if (ans[i] <= m)
      {
        double t = x[ans[i]] / cos (alpha[i]) / V;
        double y = V * sin (alpha[i]) * t - 4.9 * t * t;
        cout << x[ans[i]] << " " << y << endl;
      }
    else
      cout << V * V * sin (2 * alpha[i]) / 9.8  << " 0" << endl;
  return 0; 
}
