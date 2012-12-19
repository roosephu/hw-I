#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>

FILE *fin, *fpsn, *flog, *fstd;

void close (double score, char *msg)
{
  fprintf (flog, "%lf\n%s", score, msg);

  fclose (fin);
  fclose (fpsn);
  fclose (flog);
  fclose (fstd);
  exit (0);
}

void init (char *argv[])
{
  fin  = fopen (argv[1], "r");
  fpsn = fopen (argv[2], "r");
  fstd = fopen (argv[3], "r");
  flog = fopen (argv[4], "w");
}

int main (int argc, char *argv[])
{
  init (argv);

  double std, out;
  
  fscanf (fstd, "%lf", &std);
  fscanf (fpsn, "%lf", &out);
  if (fabs (out - std) > 1e-6 * fmax (std, 1))
    close (0, "accuracy is too much");
  close (1, "ok");

  return 0;
}
