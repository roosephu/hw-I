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

#define maxn 1100

long double f[maxn][maxn];
int buf1[maxn], buf2[maxn], *ptr = buf1, k[maxn];
double Q[maxn];
long double fac[maxn];

int cmp (int *a, int *b)
{
  return *a - *b;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("229E.in" , "r", stdin);
  freopen ("229E.out", "w", stdout);
#endif

  int n, m, i, j;
  
  scanf ("%d%d", &n, &m);
  for (i = 1; i <= m; ++i)
    {
      scanf ("%d", &k[i]);
      for (j = 1; j <= k[i]; ++j)
        scanf ("%d", ++ptr);
      qsort (ptr - k[i] + 1, k[i], sizeof (ptr[0]), (cmp_t)cmp);
    }
  memcpy (buf2, buf1, sizeof (buf1));
  qsort (buf2 + 1, ptr - buf1, sizeof (buf2[0]), (cmp_t)cmp);

  int x = 0, mid = buf2[ptr - buf1 - n + 1]; double ans = 1;
  for (i = 1, fac[0] = 1; i < maxn; ++i)
    fac[i] = fac[i - 1] * i;

  int tail = 0;
  /* evar (mid); */
  for (i = 1; i <= m; ++i)
    {
      int t = 1;
      for (; t <= k[i] && buf1[x + t] < mid; ++t);
      int w = k[i] - t + 1;
      if (t <= k[i] && buf1[x + t] == mid) Q[++tail] = 1.0 * w / t, --w;
      
      ans *= fac[k[i] - w] * fac[w] / fac[k[i]];
      n -= w;
      x += k[i];
    }
  f[0][0] = 1;
  for (i = 1; i <= tail; ++i)
    for (j = 0; j <= n; ++j)
      f[i][j] = (j ? f[i - 1][j - 1] * Q[i] : 0) + f[i - 1][j];
  
  printf ("%.10e\n", (double)(ans * f[tail][n] * fac[n] * fac[tail - n] / fac[tail]));
  return 0; 
}
