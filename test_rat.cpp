#include<iostream>
#include<cstdlib>
#include<cmath> // for sqrt() function
#include<string>

struct fraction {
	int n;
	int d;
	fraction(int n, int d) {
		this->n = n;
		this->d = d;
	}
	double asDecimal() {
		return double((double)n/(double)d);
	}
};

// Explanation of rat_0_1:
// N: largest acceptable denominator
/******************************************************************
 * The idea is to start with two fractions, a/b = 0/1 and c/d = 1/1.
 * We update either a/b or c/d at each step so that a/b will be the
 * best lower bound of x with denominator no bigger than b,
 * and c/d will be the best upper bound with denominator no bigger
 * than d.
 *
 * At each step we do a sort of binary search by introducing
 * the mediant of the upper and lower bounds.
 * The mediant of a/b and c/d is the fraction (a+c)/(b+d)
 * which always lies between a/b and c/d.
******************************************************************/
fraction rat_0_1(double x, int N)   {
     int a = 0;
     int b = 1;
     int c = 1;
     int d = 1;
     double mediant;

     while ( (b <= N) && (d <= N) )  {
         mediant = (double)((double)a + (double)c)/((double)b + (double)d);
         if (x == mediant)   {
             if (b + d <= N)  return fraction(a + c, b + d);
             else {
               if (d > b)  return fraction(c, d);
               else return fraction(a, b);
             }
        }
         else {
           if  (x > mediant) {
              a += c;
              b += d;
           }
           else {
              c += a;
              d += b;
           }
         }
     }
     if (b > N)  return fraction(c, d);
     else  return fraction(a, b);
}

int main() {
    double d;
    std::cout << "\nEnter decimal number: ";
    std::cin >> d;
    std::cout << '\n' << d << " = ";
    fraction f = rat_0_1(d, 500);
      if (f.n == 0) std::cout << 0;
  else {
    if (f.d == 1) std::cout << f.n;
    else std::cout << f.n << "/" << f.d;
  }
  std::cout << "\n\n";
  return 0;
}