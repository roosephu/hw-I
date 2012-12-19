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

const int maxn = 11000, maxm = 11000;

struct edge {int t; edge *n; };

edge graph[maxm << 1], *eptr = graph + 1, *adj[maxn];
bool o[maxn];
int deg[maxn], m;
deque<int> cur, aux;
deque<deque<int> > ans;

void adde (int s, int t)
{
  *(++eptr) = (edge){t, adj[s]}, adj[s] = eptr;
}

void append ()
{
}

void dfs (int v)
{
  for (edge *e; (e = adj[v]); )
    {
      adj[v] = e->n; int x = (e - graph) >> 1;
      if (!o[x])
        {
          --deg[v], --deg[e->t], o[x] = true, dfs (e->t);
          cur.push_back (x);
        }
    }
}

int main ()
{
  freopen ("input.txt" , "r", stdin);
  freopen ("output.txt", "w", stdout);
  ios_base::sync_with_stdio (false);

  cin >> m;
  for (int i = 1, a, b; i <= m; ++i)
    cin >> a >> b, adde (a, b), adde (b, a), ++deg[a], ++deg[b];
  for (int i = 1, j = 0; i < maxn; ++i)
    if (deg[i] & 1)
      {
        if (j)
          adde (i, j), adde (j, i), ++deg[i], ++deg[j], j = 0;
        else
          j = i;
      }
  for (int i = 1; i < maxn; ++i)
    if (deg[i])
      {
        cur.clear ();
        dfs (i);
        for (int x = 0, y; x < sz_m (cur); ++x)
          if (cur.front () > m)
            break;
          else
            y = cur.front (), cur.pop_front (), cur.push_back (y);

        for (aux.clear (); sz_m (cur); cur.pop_front ())
          if (cur.front () > m)
            !aux.empty () ? ans.push_back (aux), 0 : 0, aux.clear ();
          else
            aux.push_back (cur.front ());

        if (!aux.empty ()) ans.push_back (aux);
      }
  
  if (ans.size () > 2 || m == 1)
    cout << -1 << endl;
  else if (ans.size () == 1)
    {
      cout << m - 1 << endl;
      for (int i = 0; i < sz_m (ans[0]) - 1; ++i)
        cout << ans[0][i] << " ";
      cout << endl << 1 << endl << ans[0][sz_m (ans[0]) - 1] << endl;
    }
  else
    for (int i = 0; i < 2; ++i)
      {
        cout << sz_m (ans[i]) << endl;
        for (int j = 0; j < sz_m (ans[i]); ++j)
          cout << ans[i][j] << " ";
        cout << endl;
      }
  return 0; 
}
