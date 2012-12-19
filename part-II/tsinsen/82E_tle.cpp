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
typedef vector<int> VI;
typedef map<int, int> MII;
typedef set<int> SI;
typedef pair<int, int> PII;
typedef long double real;

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
  void adde (int s, edge e){adj[s].push_back (e);}
  void del (int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
  int deg (int v) {return adj[v].size (); }
  vector<edge>& operator [](int t) {return adj[t];}
};

typedef pair<real, real> PRR;
typedef vector<PRR>::iterator ptr;

real rate, F, H;

real work (vector<PRR> &pt)
{
  vector<real> xaxis, mid, len, crds;

  sort (iter (pt));
  foreach (it, pt)
    {
      xaxis.PB (it->Px), xaxis.PB (it->Px * (rate + 1) / 2), xaxis.PB (it->Px * rate);
      xaxis.PB (it->Py), xaxis.PB (it->Py * (rate + 1) / 2), xaxis.PB (it->Py * rate);
      crds.PB (it->Px), crds.PB (it->Py);
    }
  foreach (pi, crds)
    foreach (pj, crds)
    if (*pi <= *pj * rate && *pj <= *pi * rate && *pi && *pj)
      xaxis.PB (F / (F - H) * 2 / (1 / *pi + 1 / *pj));
  // foreach (pi, pt)
  //   foreach (pj, pt)
  //   if (pi->Px <= pj->Py * rate && pj->Py <= pi->Px * rate && pi->Px && pj->Py)
  //     xaxis.push_back (F / (F - H) * 2 / (1 / pi->Px + 1 / pj->Py)), cerr << pi - pt.begin () << " " << pj - pt.begin () << " " << F / (F - H) * 2 / (1 / pi->Px + 1 / pj->Py) << endl;
  sort (iter (xaxis));
  xaxis.resize (unique (iter (xaxis)) - xaxis.begin ());
  for (int i = 1; i < sz_m (xaxis); ++i)
    mid.push_back ((xaxis[i] + xaxis[i - 1]) / 2), len.push_back (xaxis[i] - xaxis[i - 1]);
  
  real ans = 0; ptr p = pt.begin (), q = p;
  for (int _ = 0; _ < sz_m (mid); ++_)
    {
      real ny = 0, nx = mid[_];
      for (; p != pt.end () && p->Py * rate <  nx; ++p);
      for (; q != pt.end () && q->Px        <= nx; ++q);
      vector<PRR> vec;
      for (ptr i = p; i != q; ++i)
        if (i->Px <= nx && nx <= i->Py * rate)
          {
            real l = -H, r = H;
            if (nx < i->Px * rate) l = F - (F - H) * (nx / i->Px);
            if (i->Py        < nx) r = F - (F - H) * (nx / i->Py);
            if (r < 0) swap (l, r), l = -l, r = -r;
            
            // if (l > 0)
            //   vec.push_back (MKP (+l, +r)), vec.push_back (MKP (-r, -l));
            // else
            //   vec.push_back (MKP (min (l, -r), max (r, -l)));
            vec.push_back (MKP (max (l, (real)0.0), max (-l, r)));
          }
      sort (iter (vec));

      real lx = -oo;
      foreach (it, vec)
        if (it->Py > lx)
          {
            chkmax (lx, it->Px);
            ny += it->Py - lx;
            lx = it->Py;
          }
      
      ans += ny * len[_];
      // cvar (nx), evar (ny);
    }
  return ans * 2;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("82E.in" , "r", stdin);
  freopen ("82E.out", "w", stdout);
#endif
  ios_base::sync_with_stdio (false);

  int n; vector<PRR> neg, pos;
  
  cin >> n >> H >> F;
  for (int i = 1, l, r; i <= n; ++i)
    {
      cin >> l >> r;
      if (r <= 0) neg.push_back (MKP (-r, -l));
      if (l >= 0) pos.push_back (MKP (+l, +r));
      if (l < 0 && 0 < r)
        neg.PB (MKP (0, -l)), pos.PB (MKP (0, +r));
    }

  rate = (F + H) / (F - H);
  cout << setprecision (15) << work (neg) + work (pos) << endl;
  return 0; 
}
