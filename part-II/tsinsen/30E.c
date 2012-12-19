#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define DEBUG
typedef int (*cmp_t) (const void *, const void *);
typedef unsigned uint;
typedef long long int64;
typedef unsigned long long uint64;
#define max(i, j) ({int _ = (i), __ = (j); _ > __ ? _ : __;})
#define min(i, j) ({int _ = (i), __ = (j); _ < __ ? _ : __;})
#define swap(T, i, j) ({T _ = (i); (i) = (j); (j) = _;})
#ifdef DEBUG
#define cerr(...) fprintf (stderr, __VA_ARGS__)
void disp (char *s, int *x, int n) {int i; cerr ("[%s: ", s); for (i = 0; i < n - 1; ++i) cerr ("%d ", x[i]); if (n) cerr ("%d", x[i]); cerr ("]\n");}
#else
#define cerr(...) ({})
#define disp(...) ({})
#endif
#define CR cerr ("\n")
#ifdef WIN32
#define fmt64 "%I64d"
#else
#define fmt64 "%lld"
#endif

#define maxn 110000

char S[maxn], T[maxn];
int pal[maxn], next[maxn], pre[maxn];

int main ()
{
  /* freopen ("30E.in" , "r", stdin); */
  /* freopen ("30E.out", "w", stdout); */

  int n, i, j, t;

  /* scanf ("%d%s", &n, S + 1); */
  scanf ("%s", S + 1), n = strlen (S + 1);
  for (i = 2, t = 1, pal[1] = 1; i <= n; ++i)
    {
      j = t * 2 - i;
      pal[i] = min (pal[j], j - t + pal[t]);
      for (; i > pal[i] && S[i - pal[i]] == S[i + pal[i]]; ++pal[i]);
      if (i + pal[i] > t + pal[t]) t = i;
    }
  for (i = 1; i <= n; ++i)
    T[i] = S[n + 1 - i];
  /* for (i = 2, t = 1, ext[1] = 0; i <= n; ++i) */
  /*   { */
  /*     ext[i] = max (min (t + ext[t] - i, ext[i - t + 1]), 0); */
  /*     for (; T[i + ext[i]] == T[1 + ext[i]]; ++ext[i]); */
  /*     if (i + ext[i] >= t + ext[t]) t = i; */
  /*   } */
  /* for (i = 1, t = 1; i <= n; ++i) */
  /*   { */
  /*     lcp[i] = max (min (t + lcp[t] - i, ext[i - t + 1]), 0); */
  /*     for (; S[i + lcp[i]] == T[1 + lcp[i]]; ++lcp[i]); */
  /*     if (i + lcp[i] >= t + lcp[t]) t = i; */
  /*   } */

  for (i = 2, j = 0, next[0] = -1; i <= n; ++i)
    {
      for (; ~j && T[i] != T[j + 1]; j = next[j]);
      next[i] = ++j;
    }
  /* cerr ("[S: %s]\n", S + 1); */
  /* cerr ("[T: %s]\n", T + 1); */
  /* disp ("next", next + 1, n); */
  for (i = 1, j = 0; i <= n; ++i)
    {
      for (; ~j && S[i] != T[j + 1]; j = next[j]);
      pre[i] = ++j;
    }
  /* disp ("pre", pre + 1, n); */
  for (i = 1; i <= n; ++i)
    pre[i] = max (pre[i - 1], pre[i]);
  
  int ans = 0;
  for (i = n; i; --i)
    ans = max (ans, pal[i] + min (pre[i - pal[i]], n + 1 - i - pal[i]));
  /* cerr ("[ans] %d\n", ans); */
  for (i = 1; i <= n; ++i)
    if (pal[i] == ans)
      return printf ("1\n%d %d\n", i - pal[i] + 1, pal[i] * 2 - 1), cerr ("well\n"), 0;
    else if (pal[i] + min (pre[i - pal[i]], n + 1 - i - pal[i]) == ans)
      {
        printf ("3\n");
        for (j = 1; j <= n && pre[j] != pre[i - pal[i]]; ++j);
        printf ("%d %d\n", j - pre[j] + 1, pre[j]);
        printf ("%d %d\n", i - pal[i] + 1, pal[i] * 2 - 1);
        printf ("%d %d\n", n - pre[j] + 1, pre[j]);
        return 0;
      }

  printf ("%d\n", ans * 2 - 1);
  return 0;
}
