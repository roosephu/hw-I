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

#define maxm 1100
#define maxsz 125

const int mod = 12345;
typedef int mat[maxsz][maxsz];

int qx[maxm], qc[maxm];
int sz = 0;
bool o[30][maxsz];
mat u, v;
int prod[30], val[30];

int fpm (int b, int64 e, int m)
{
  int t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = b * t % m : 0;
  return t;
}

int gcd (int a, int b)
{
  int t;
  for (; a; t = a, a = b % a, b = t);
  return b;
}

void matmul (mat a, mat b, mat c)
{
  mat t; int i, j, k;
  for (i = 0; i < sz; ++i)
    for (j = 0; j < sz; ++j)
      for (k = 0, t[i][j] = 0; k < sz; ++k)
        t[i][j] += a[i][k] * b[k][j] % mod;
  for (i = 0; i < sz; ++i)
    for (j = 0; j < sz; ++j)
      c[i][j] = t[i][j] % mod;
}

int main ()
{
#ifndef ONLINE_JUDGE
  freopen ("107D.in" , "r", stdin);
  freopen ("107D.out", "w", stdout);
#endif

  int64 n; int m, i, j, x, c; char C;
  
  scanf (fmt64 "%d", &n, &m);
  for (i = 0; i < 26; ++i)
    val[i] = -1;
  for (i = 1; i <= m; ++i)
    {
      scanf (" %c%d", &C, &x), c = C - 'A';
      qc[i] = c, qx[i] = x, val[c] = abs (val[c] * x / gcd (x, val[c]));
    }
  for (i = 1; i <= m; ++i)
    for (x = 0; x < val[qc[i]]; x += qx[i])
      o[qc[i]][x] = true;
  for (i = 1, prod[0] = 1; i < 26; ++i)
    prod[i] = prod[i - 1] * abs (val[i - 1]);
  /* disp ("prod", prod, 26); */
  /* disp ("val", val, 26); */

  sz = prod[26] = prod[25] * abs (val[25]);
  for (i = 0; i < sz; ++i)
    for (j = 0; j < 26; ++j)
      if (val[j] != -1)
        {
          x = i + prod[j];
          if (x % prod[j + 1] < prod[j])
            x -= prod[j + 1];
          ++u[i][x];
        }
  /* for (i = 0; i < sz; ++i) */
  /*   disp ("u", u[i], sz); */

  v[0][0] = 1;
  for (; n; n >>= 1, matmul (u, u, u))
    n & 1 ? matmul (v, u, v) : 0;
  
  /* for (i = 0; i < sz; ++i) */
  /*   disp ("u", v[i], sz); */
  /* for (i = 0; i < 26; ++i) */
  /*   { */
  /*     for (j = 0; j < val[i]; ++j) */
  /*       cerr ("%d ", o[i][j]); */
  /*     CR; */
  /*   } */
  int ans = 0;
  for (i = 0; i < sz; ++i)
    {
      bool b = true;
      for (j = 0; j < 26; ++j)
        if (val[j] != -1 && !o[j][i % prod[j + 1] / prod[j]])
          b = false;
      if (b) ans += v[0][i];
    }
  printf ("%d\n", ans % mod);
  return 0;
}
