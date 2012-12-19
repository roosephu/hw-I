#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>

FILE *fin, *fout, *flog, *fstd, *fmsg;

void close (double score, char *msg)
{
  fprintf (flog, "%d\n", (int)(score * 10));
  fprintf (fmsg, "%s\n", msg);

  fclose (fin);
  fclose (fout);
  fclose (flog);
  fclose (fstd);
  fclose (fmsg);
  exit (0);
}

void init (char *argv[])
{
  fin  = fopen (argv[1], "r");
  fout = fopen (argv[2], "r");
  fstd = fopen (argv[3], "r");
  flog = fopen (argv[5], "w");
  fmsg = fopen (argv[6], "w");
}

#define maxn 110000

char S[maxn], T[maxn];

int main (int argc, char *argv[])
{
  init (argv);

  int i, j, k, ans = 0, start, count;
  
  fscanf (fstd, "%d", &k);
  for (i = 1; i <= k; ++i)
    fscanf (fstd, "%*d%d", &count), ans += count;

  fscanf (fin, "%s", S + 1);
  int last = -1, top = 0, first;
  fscanf (fout, "%d", &k);
  for (i = 1; i <= k; ++i)
    {
      fscanf (fout, "%d%d", &start, &count);
      if (i == 1) first = count;
      if (i == k && first != count) close (0, "first != last");
      if (count <= 0) close (0, "count <= 0");
      if (start < last) close (0, "a character used more than 1 times");
      if (i * 2 == k + 1 && count % 2 != 1) close (0, "middle is not a palindrome");
      last = start + count;
      for (; count; --count)
        T[top++] = S[start++];
    }
  if (top != ans) close (0, "not long enough");

  for (i = 0, j = top - 1; i < j; ++i, --j)
    if (T[i] != T[j])
      close (0, "not a palindrome");

  close (1, "ok");
  return 0;
}
