#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#ifndef ONLINE_JUDGE
#define DEBUG
#endif
typedef int (*cmp_t) (const void *, const void *);
typedef unsigned uint;
typedef long long int64;
typedef unsigned long long uint64;
#define max(i, j) ({int _ = (i), __ = (j); _ > __ ? _ : __;})
#define min(i, j) ({int _ = (i), __ = (j); _ < __ ? _ : __;})
#define swap(T, i, j) ({T _ = (i); (i) = (j); (j) = _;})
#define oo 0x3F3F3F3F
#ifdef DEBUG
#define cerr(...) fprintf (stderr, __VA_ARGS__)
#define cvar(x) cerr ("[" #x ": %d]", x)
#define evar(x) cerr ("[" #x ": %d]\n", x)
void DISP (char *s, int *x, int n) {int i; cerr ("[%s: ", s); for (i = 0; i < n - 1; ++i) cerr ("%d ", x[i]); if (n) cerr ("%d", x[i]); cerr ("]\n");}
#define disp(T,n) DISP (#T " to " #n, T, n)
#else
#define cerr(...) ({})
#define cvar(...) ({})
#define evar(...) ({})
#define disp(...) ({})
#endif
#define CR cerr ("\n")
#ifdef WIN32
#define fmt64 "%I64d"
#else
#define fmt64 "%lld"
#endif

#define maxn 110000
#define maxm 110000
#define maxbuf 2200000
#define maxdep 18

typedef struct node {struct node *lc, *rc; int sum;} node;
typedef struct edge {int t; struct edge *n;} edge;
typedef struct query {int a, b, k, y, t;} query;
typedef int arr32[maxn];

node buf[maxbuf], *pbuf = buf, *st[maxn], *null = buf;
query Q[maxm];
arr32 root, size, aux, depth, w;
int f[maxdep][maxn];
int m;
edge graph[maxn << 1], *eptr = graph, *adj[maxn];

node *st_modify (node *t, int v)
{
  node *dfs (node *o, int l, int r)
  {
    node *t = ++pbuf; *t = *o; ++t->sum;
    if (v - 1 == l && r == v) return t;
    int m = (l + r + 1) >> 1;
    if (v <= m) t->lc = dfs (t->lc, l, m);
    else        t->rc = dfs (t->rc, m, r);
    return t;
  }
  return dfs (t, -1, m + 1);
}

int st_query (node *t, int x)
{
  int dfs (node *t, int l, int r)
  {
    if (r <= x) return t->sum;
    if (l >= x) return 0;
    int m = (l + r + 1) >> 1;
    return dfs (t->lc, l, m) + dfs (t->rc, m, r);
  }
  return dfs (t, -1, m + 1);
}

void dfs (int v)
{
  edge *e; size[v] = 0;
  int i;
  for (i = 0; f[i][v]; ++i)
    f[i + 1][v] = f[i][f[i][v]];
  for (e = adj[v]; e; e = e->n)
    {
      st[e->t] = st_modify (st[v], w[e->t]);
      f[0][e->t] = v; depth[e->t] = depth[v] + 1;
      dfs (e->t);
      if (size[e->t] > size[aux[v]]) aux[v] = e->t;
      size[v] += size[e->t];
    }
  ++size[v];
}

int LCA (int p, int q)
{
  for (; root[p] != root[q]; p = f[0][root[p]])
    if (depth[root[p]] < depth[root[q]])
      swap (int, p, q);
  return depth[p] > depth[q] ? q : p;
}

int calc (int t, int L, int R) /* exclude (L, R] */
{
  return depth[t] - st_query (st[t], R) + st_query (st[t], L);
}

void adde (int s, int t)
{
  *(++eptr) = (edge){t, adj[s]}, adj[s] = eptr;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("226E.in" , "r", stdin);
  freopen ("226E.out", "w", stdout);
#endif

  int n, i, j, a, b, k, y, tot = 0; char cmd;
  
  scanf ("%d", &n);
  for (i = 1; i <= n; ++i)
    scanf ("%d", &k), adde (k, i), cerr ("%d %d\n", k, i);
  scanf ("%d", &m);
  
  for (i = 1; i <= n; ++i)
    w[i] = m + 1;
  for (i = 1; i <= m; ++i)
    if (scanf (" %c", &cmd), cmd == '1')
      scanf ("%d", &k), w[k] = i;
    else
      scanf ("%d%d%d%d", &a, &b, &k, &y), Q[++tot] = (query){a, b, k, y, i};

  *null = (node){null, null, 0};
  st[0] = null, dfs (0);

  for (i = 0; i <= n; ++i)
    if (!root[i])
      for (a = i; a; a = aux[a])
        root[a] = i;

  disp (root + 1, n);
  /* cvar (LCA (1, 2)); */
  /* evar (LCA (3, 2)); */
  disp (w + 1, n);

#define valid(x) (w[x] <= L || w[x] > R)
  for (j = 1; j <= tot; ++j)
    {
      a = Q[j].a, b = Q[j].b, k = Q[j].k;
      
      int L = Q[j].y, R = Q[j].t, x = LCA (a, b);
      int pa = calc (a, L, R) - valid (a), pb = calc (b, L, R) - valid (b), px = calc (x, L, R);
      int tot = (pa - px) + (pb - px) + valid (x);

      cvar (pa), cvar (pb), cvar (px), evar (tot);
      if (tot < k)
        {printf ("-1\n"); continue;}
      /* if (valid (x) && pa - px + 1 == k) */
      /*   {printf ("%d\n", x); continue;} */
      if (pa - px < k)
        k = tot + 1 - k, a = b, pa = pb;

      for (i = 16; i >= 0; --i)
        if (f[i][a] && pa - (pb = calc (f[i][a], L, R) - valid (f[i][a])) < k)
          a = f[i][a];
      printf ("%d\n", f[0][a]);
    }
  
  return 0; 
}
