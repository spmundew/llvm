
#include <math.h>
#include <stdio.h>

long double fun(long double x) {
  int k, n = 5;
  long double t1, d1 = 1.0L;

  t1 = x;

  for( k = 1; k <= n; k++ ) {
    d1 = 2.0 * d1;
    t1 = t1 + sin (d1 * x) / d1;
  }
  return t1;
}


int main(int argc, char **argv) {

  int i, j, k, n = 1000000;
  long double h, t1, t2, dppi, ans = 5.795776322412856L;
  long double s1, threshold = 1e-14L;

  t1 = -1.0;
  dppi = acos(t1);
  s1 = 0.0;
  t1 = 0.0;
  h = dppi / n;

  for(i = 1; i <= n; i++) {
    t2 = fun (i * h);
    s1 = s1 + sqrt (h*h + (t2 - t1)*(t2 - t1));
    t1 = t2;
  }


  printf(" => total error: %d %1.15Le %1.15Le\n", fabsl(ans-s1) > threshold, fabsl(ans-s1), threshold);
  printf(" => ans: %1.15Le\n =>  s1: %1.15Le\n", (long double)ans, (long double)s1);

  return 0;
}


