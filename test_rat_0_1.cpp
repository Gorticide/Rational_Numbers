// Rationalize(double decimal)

//  g++ test_rat_0_1.cpp -std=c++11 -o testrat
// Michael William Hentrich
// September 2018


// code section to convert decimal between 0 and 1 to fraction
// Idea:
//      INPUT:  double
//      RETURN: fraction
//  to be used as constructor in Fraction class

//  Take decimal
//  double d = decimal - floor(decimal)
//  d = 0.333 = 3.333 - 3
//  Feed d to this function rat_0_1(double)

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

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;

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

// The main program will become Fraction(double) with max denominator defined

int main() {
  double target;
	int MAX_DENOMINATOR = 500;

  cout << "\n\nEnter a decimal number: ";
  cin >> target;

  double d = target - floor(target);
  fraction f = rat_0_1(d, MAX_DENOMINATOR);

  cout << "\n\n" << target << " ~=~ " << floor(target) << " + " << f.n << "/"
       << f.d << "\n\n";
  return 0;

}

/* rat_0_1 CONVERTED from Python code posted by John D. Cook
https://www.johndcook.com/blog/2010/10/20/best-rational-approximation/

def farey(x, N):
    a, b = 0, 1
    c, d = 1, 1
    while (b <= N and d <= N):
        mediant = float(a+c)/(b+d)
        if x == mediant:
            if b + d <= N:
                return a+c, b+d
            elif d > b:
                return c, d
            else:
                return a, b
        elif x > mediant:
            a, b = a+c, b+d
        else:
            c, d = a+c, b+d

    if (b > N):
        return c, d
    else:
        return a, b
***********************************************************/
