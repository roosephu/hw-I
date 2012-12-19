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
#define m_sz(x) (int)((x).size ())
#define m_it(x) (x).begin (), (x).end ()

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

const int maxn = 5500, maxm = 110000;

struct node {int s, t, w, z; } ;

int ufs[maxn], used[maxm], n, k;
vector<node> P, Q;
node E[maxm];

bool operator < (node a, node b) {return a.w < b.w;}

int find (int t) {return ufs[t] != t ? ufs[t] = find (ufs[t]) : t; }

void merge (node x, int &t, int &ans, int v)
{
  if (find (x.s) != find (x.t))
    ufs[find (x.s)] = find (x.t), ++t, ans += x.w, used[x.z] = v; //, cerr << x.s << " " << x.t << endl;
}

PII check (int v)
{
  vector<node>::iterator pa = P.begin (), pb = Q.begin (), p; int x = 0, cp = 0, cq = 0;
  for (int i = 1; i <= n; ++i)
    ufs[i] = i;
  
  // cerr << "--------------------" << v << endl;
  for (x = n; x != 1 && (pa != P.end () || pb != Q.end ()); )
    if (pb == Q.end () || (pa != P.end () && pa->w - v <= pb->w))
      merge (*pa, cp, x, v), pa++;
    else
      merge (*pb, cq, x, v), pb++;
  // cerr << v << " " << cp << " " << cq << " " << x << endl;
  return MKP (cp >= k, x);
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("125E.in" , "r", stdin);
  freopen ("125E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int m;
  
  cin >> n >> m >> k;
  for (int i = 1, s, t, w; i <= m; ++i)
    {
      cin >> s >> t >> w, E[i] = (node){s, t, w, i};
      if (s == 1 || t == 1)
        P.push_back (E[i]);
      else
        Q.push_back (E[i]);
    }
  // foreach (it, P)
  //   cerr << it->s << " " << it->t << " " << it->w << endl;
  
  sort (m_it (P));
  sort (m_it (Q));

  int L = -2e5, R = 2e5, mid;
  for (; mid = (L + R) >> 1, L < R; )
    check (mid).Px ? (R = mid) : (L = mid + 1);
  if (!check (L).Px || (n != 1 && k == 0)) return cout << -1 << endl, 0;

  memset (used, 0xC0, sizeof (used));
  cout << n - 1 << endl;
  // cerr << check (L).Py << endl;
  // cerr << L << endl;
  check (L - 1);          // the edges that must be in MST
  int w = 0; mid = 0; set<int> ans;
  foreach (it, P)
    if (used[it->z] == L - 1)
      ++w, ans.insert (it->z);
  
  check (L    );          // the edges that may be in MST
  // cerr << "mid" << mid << endl;
  for (int i = 1; i <= n; ++i)
    ufs[i] = i;
  foreach (it, P)
    if (used[it->z] == L && m_sz (ans) < k)
      ans.insert (it->z);
  foreach (it, ans)
    merge (E[*it], w, mid, oo), cout << *it << " ";
  foreach (it, Q)
    if (merge (*it, w, mid, oo), used[it->z] == oo)
      cout << it->z << " ";
  // cerr << endl << "total: " << mid << endl;
  return 0; 
}
