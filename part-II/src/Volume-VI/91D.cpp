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
typedef long double real;
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
  Graph () {adj.clear (); }
  void resize (int n) {adj.resize (n + 5); }
  void add (int s, edge e){adj[s].push_back (e);}
  void del (int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
  int deg (int v) {return adj[v].size (); }
  vector<edge>& operator [](int t) {return adj[t];}
};

const int maxn = 110000;

int next[maxn];
bool o[maxn];

void push (VI &src, VI &dst, VI x)
{
  foreach (it, x)
    src.push_back (*it);
  rotate (x.begin (), x.begin () + 1, x.end ());
  foreach (it, x)
    dst.push_back (*it);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("91D.in" , "r", stdin);
  freopen ("91D.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n;
  
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> next[i];

  vector<VI> rec2, rec3; vector<pair<VI, VI> > ans;
  for (int i = 1; i <= n; ++i)
    if (!o[i] && next[i] != i)
      {
        VI vec;
        for (int j = i; vec.empty () || j != i; j = next[j])
          vec.push_back (j), o[j] = true;
        
        for (; sz_m (vec) >= 4; )
          {
            VI src, dst; int n = sz_m (vec);
            for (int i = 1; i <= min (5, n); ++i)
              src.push_back (vec[n - i]);
            dst = src;
            rotate (dst.begin (), dst.end () - 1, dst.end ());
            ans.push_back (MKP (src, dst));

            vec.erase (vec.begin () + n - min (5, n), vec.end ());
            if (n != 4) vec.push_back (*dst.begin ());
          }
        
        if (sz_m (vec) == 2)
          rec2.push_back (vec);
        else if (sz_m (vec) == 3)
          rec3.push_back (vec);
      }

  vector<VI>::iterator p = rec2.begin (), q = rec3.begin (), t;
  for (; p != rec2.end (); ) // 3 + 2
    {
      VI src, dst;
      push (src, dst, *p++);
      if (q != rec3.end ()) push (src, dst, *q++);
      else if (p != rec2.end ()) push (src, dst, *p++);
      ans.push_back (MKP (src, dst));
    }
  for (; q != rec3.end (); )
    {
      VI src, dst, SRC, DST;
      push (src, dst, *q++);
      if (q != rec3.end ()) push (SRC, DST, *q++);
      if (q != rec3.end ())
        {
          push (src, dst, VI (q->begin () + 1, q->begin () + 3));
          push (SRC, DST, VI (q->begin () + 0, q->begin () + 2));
          ++q;
        }
      ans.push_back (MKP (src, dst));
      if (!SRC.empty ()) ans.push_back (MKP (SRC, DST));
    }

  cout << sz_m (ans) << endl;
  foreach (it, ans)
    {
      cout << it->Px.size () << endl;
      foreach (e, it->Px)
        cout << *e << " ";
      cout << endl;
      foreach (e, it->Py)
        cout << *e << " ";
      cout << endl;
    }
  return 0; 
}
