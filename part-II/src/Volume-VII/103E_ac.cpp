#include <stdio.h>
#include <memory.h>

#define maxn 305
#define maxv 608
#define maxe 100000

typedef long long int64;
typedef struct etype
{
  int t; int64 w;
  struct etype *n, *o;
} etype;
typedef int arr32[maxv];

etype graph[maxe * 2], *edge[maxv], *eptr = graph, *adm[maxv];
arr32 gap, dist, queue, pred;
int src, sink;

void rev_bfs ()
{
  memset (gap, 0, sizeof (gap));
  memset (dist, 0x3F, sizeof (dist));
  int u, d, head = 0, tail = 0; etype *e;
  ++gap[dist[queue[++tail] = sink] = 0];
  for (; head < tail; )
    for (e = edge[u = queue[++head]], d = dist[u] + 1; e; e = e->n)
      if (e->o->w && dist[e->t] > d)
        ++gap[dist[queue[++tail] = e->t] = d];
}

int64 augment ()
{
  int u; int64 w = (int64)1e18; etype *e;
  for (e = adm[u = src]; u != sink; e = adm[u = e->t])
    w > e->w ? w = e->w : 0;
  for (e = adm[u = src]; u != sink; e = adm[u = e->t])
    e->w -= w, e->o->w += w;
  return w;
}

int64 isap ()
{
  rev_bfs ();
  memcpy (adm, edge, sizeof (edge));
  int u, d, mindist; int64 flow = 0; etype *e;
  for (u = src; dist[src] < sink; )
    {
      for (e = adm[u], d = dist[u] - 1; e; e = e->n)
        if (e->w && dist[e->t] == d)
          break;
      if (e)
        {
          pred[e->t] = u, adm[u] = e, u = e->t;
          if (u == sink)
            flow += augment (), u = src;
        }
      else 
        {
          --gap[d = dist[u]];
          e = adm[u] = edge[u];
          for (mindist = sink; e; e = e->n)
            if (e->w && dist[e->t] < mindist)
              mindist = dist[e->t];
          ++gap[dist[u] = mindist + 1];
          if (!gap[d]) break;
          if (u != src) u = pred[u];
        }
    }
  return flow;
}

void adde (int s, int t, int64 w)
{
  *(++eptr) = (etype){t, w, edge[s]}, edge[s] = eptr;
  *(++eptr) = (etype){s, 0, edge[t]}, edge[t] = eptr;
  edge[s]->o = edge[t], edge[t]->o = edge[s];
}

int main ()
{

  int i, j, k, n; int64 ans = 0;

  scanf ("%d", &n), src = n * 2 + 1, sink = src + 1;
  for (i = 1; i <= n; ++i)
    for (scanf ("%d", &j); j; --j)
      scanf ("%d", &k), adde (i, n + k, (int64)1e18);
  for (i = 1; i <= n; ++i)
    scanf ("%d", &j), adde (src, i, (int64)1e9 - j), ans += 1e9 - j;
  for (i = 1; i <= n; ++i)
    adde (i + n, sink, (int64)1e9);
  printf ("%d\n", (int)(isap () - ans));
  return 0;
}

