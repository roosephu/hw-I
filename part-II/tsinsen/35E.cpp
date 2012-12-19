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
#define it_m(x) (x).begin (), (x).end ()

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef set<int> SI;
typedef pair<int, int> PII;

int64 fpm (int64 b, int64 e, int64 m) { int64 t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }
template<class T> inline bool chkmin (T &a, T b) {return a < b ? a = b, true : false;}
template<class T> inline bool chkmax (T &a, T b) {return a > b ? a = b, true : false;}
template<class T> inline T sqr (T x) {return x * x;}

template<class edge> struct Graph
{
  vector<vector<edge> > adj;
  Graph (int n) {adj.clear (); adj.resize (n + 5);}
  void adde (int s, edge e){adj[s].push_back (e);}
  typename vector<edge>::iterator operator [] (int t) {return adj[t].begin ();}
};

struct poly {int64 area, circum; vector<PII> vertex; };

multiset<int> S;
priority_queue<PII, vector<PII>, greater<PII> > evt;
poly now, ans;
// vector<PII> ans;

int main ()
{
  // freopen ("input.txt" , "r", stdin);
  // freopen ("output.txt", "w", stdout);
  ios_base::sync_with_stdio (false);

  int n, x, y;
  
  cin >> n;
  for (int i = 1, h, l, r; i <= n; ++i)
    cin >> h >> l >> r, evt.push (MKP (l, h)), evt.push (MKP (r, -h));
  ans.area = ans.circum = 1e18;
  for (; ; )
    {
      if (evt.empty ()) break;

      int xx = evt.top ().Px;
      if (S.empty ()) x = xx, y = 0;
      for (; !evt.empty () && evt.top ().Px == xx; evt.pop ())
        if (evt.top ().Py < 0)
          S.erase (S.find (-evt.top ().Py));
        else
          S.insert (evt.top ().Py);
      int yy = S.empty () ? 0 : *--S.end ();
      if (yy != y) now.vertex.push_back (MKP (xx, y)), now.vertex.push_back (MKP (xx, yy));
      // now.area += (int64)(xx - x) * y;
      // now.circum += abs (yy - y) + (xx - x) * 2ll;
      x = xx, y = yy;

      if (S.empty ())
        {
          // if (MKP (now.area, now.circum) < MKP (ans.area, ans.circum))
          //   ans = now;
          // now.area = now.circum = 0, now.vertex.clear ();
        }
    }

  cout << now.vertex.size () << endl;
  foreach (it, now.vertex)
    cout << it->Px << " " << it->Py << endl;
  return 0; 
}
