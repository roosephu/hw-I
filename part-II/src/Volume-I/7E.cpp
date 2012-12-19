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

typedef pair<bool, int> prio;

map<string, prio> f;
map<char, int> c2i;

prio check (string expr)
{
  // cerr << "check: " << "\"" << expr << "\"" << " -> ";
  for (int i = 0; i < sz_m (expr); ++i)
    if (expr[i] != ' ') {expr = expr.substr (i); break;}
  for (int i = sz_m (expr) - 1; i >= 0; --i)
    if (expr[i] != ' ') {expr = expr.substr (0, i + 1); break;}
  PII p = MKP (oo, 0);

  bool brackets = false;
  for (int i = 0, stk = 0; i < sz_m (expr); ++i)
    if (expr[i] == '(')
      ++stk, brackets = true;
    else if (expr[i] == ')')
      --stk;
    else if (!stk && c2i.count (expr[i]))
      p = min (p, MKP (c2i[expr[i]], -i)); //, cerr << "lower: " << expr[i] << " " << c2i[expr[i]] << endl;

  if (brackets && p.Px == oo) return f[expr] = MKP (check (expr.substr (1, sz_m (expr) - 2)).Px, oo);
  if (p.Px == oo) return !f.count (expr) ? f[expr] = MKP (true, oo), 0 : 0, f[expr];
  prio L = check (expr.substr (0, -p.Py)), R = check (expr.substr (-p.Py + 1));
  cerr << "\"" << expr << "\"" << endl;
  cerr << "cut: " << p.Px << " " << -p.Py << endl;
  cerr << "prio: " << L.Py << " " << p.Px << " " << R.Py << endl;
  return f[expr] = MKP (L.Px && R.Px && (L.Py == oo || L.Py / 2 >= p.Px / 2) && (p.Px < R.Py || (p.Px == R.Py && p.Px % 2 == 0)), p.Px);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("7E.in" , "r", stdin);
  freopen ("7E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n; string S, name, expr;
  
  c2i['+'] = 0, c2i['-'] = 1, c2i['*'] = 2, c2i['/'] = 3;
  cin >> n;
  for (; n--; )
    {
      for (int t = 7; t; cin >> S, t -= sz_m (S));
      cin >> name, getline (cin, expr);
      cerr << name << ": " << expr << endl;

      f[name] = check (expr);
    }

  getline (cin, expr);
  if (check (expr).Px) cout << "OK" << endl;
  else cout << "Suspicious" << endl;
  // cerr << f["sum"].Py << endl;
  return 0; 
}
