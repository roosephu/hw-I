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

const int MOVE = 1, LIFT = 2, THR = 4;

struct unit {int pos, todo, lifted, mv, thr; };

unit S[4];
int ans = 0;

void dfs ()
{
  int dist = 0, add = 0;
  for (auto &x : S)
    {
      dist = max (dist, x.pos);
      if (x.todo & MOVE) add += x.mv;
      if (x.todo & THR) add += x.thr;
    }
  if (dist + add <= ans) return ;

  for (int i = 0; i < 3; ++i)
    {
      unit &x = S[i];
      ans = max (ans, x.pos);
      if (ans == 42) return ;

      if (x.lifted != -1) continue; // can do nothing

      if ((!(x.todo & THR) || (x.todo & LIFT)) && (x.todo & MOVE))        // move
        {
          x.todo ^= MOVE;
          
          for (int z = x.mv; z >= -x.mv; --z)
            {
              int t = z + x.pos; bool b = t > 0;
              for (int j = 0; j < 3; ++j)
                if (S[j].lifted == -1 && t == S[j].pos) b = false;
              if (b)
                {
                  x.pos += z;
                  dfs ();
                  x.pos -= z;
                }
            }
          x.todo ^= MOVE;
        }
      
      if (x.todo & LIFT)        // lift
        {
          x.todo ^= LIFT; int a = x.pos + 1, b = x.pos - 1;
          for (int j = 0; j < 3; ++j)
            if (S[j].lifted == -1 && (S[j].pos == a || S[j].pos == b))
              {
                int bak = S[j].pos;
                S[j].lifted = i;
                dfs ();
                S[j].lifted = -1;
                S[j].pos = bak;
                // S[j] = bak;
              }
          x.todo ^= LIFT;
        }
      
      if (x.todo & THR)         // throw
        {
          x.todo ^= THR;

          int z = -1;
          for (int j = 0; j < 3; ++j)
            if (S[j].lifted == i) z = j;
          if (z != -1)
            {
              // int X = i != 0 ? S[0].pos : S[1].pos, Y = i != 2 ? S[2].pos :
              for (int j = x.thr; j >= -x.thr; --j)
                {
                  int t = j + x.pos; bool b = t > 0;
                  for (int r = 0; r < 3; ++r)
                    if (S[r].lifted == -1 && t == S[r].pos) b = false;
                  if (b)
                    {
                      S[z].pos = t, S[z].lifted = -1;
                      dfs ();
                      S[z].lifted = i;
                    }
                }
            }

          x.todo ^= THR;
        }
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("105E.in" , "r", stdin);
  freopen ("105E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  for (auto &x : S)
    {
      cin >> x.pos >> x.mv >> x.thr;
      x.todo = 7, x.lifted = -1;
    }

  dfs ();
  cout << ans << endl;
  // cerr << 1.0 * clock () / CLOCKS_PER_SEC << endl;
  return 0; 
}
