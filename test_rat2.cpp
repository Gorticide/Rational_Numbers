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

int gcd(int a, int b);
int lcm(int a, int b);

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
    double target;
		int num, den;
		char choice;

		std::cout << "\nINPUT decimal [D] or fraction [F] <d/f> ? : ";
		std::cin >> choice;

		while (choice != 'd' && choice != 'D' && choice != 'F' && choice != 'f')
		{
			std::cout << "\nINPUT decimal [D] or fraction [F] <d/f> ? : ";
			std::cin >> choice;
		}

		switch (choice)
		{
			case 'D': case 'd':
			    std::cout << "\nEnter decimal number: ";
			    std::cin >> target;
					break;

			case 'F': case 'f':
			   std::cout << "\nEnter fraction (2 integers: enter a/b as a b):  ";
			   std::cin >> num >> den;
				 target = (double)num / (double)den;
			   break;
		}

    std::cout << '\n' << target << " = ";
		double d = target - floor(target);  // 3.333 - 3 = 0.3333; -3.333 - (-4) = 0.6667
	  fraction f = rat_0_1(d, 500);
	                                                    // 1/3 + 3 = 10/3
	  fraction g = fraction(std::floor(target), 1);     // 2/3 - 4 = -10/3
	  int lcd = lcm(f.d, g.d);
	  int quot1 = lcd/f.d;
	  int quot2 = lcd/g.d;
	  //    fract.set(num * quot1 + other.num * quot2, lcd);
	  int numerator = f.n * quot1 + g.n * quot2;
	  int denominator = lcd;

		if (numerator == 0) std::cout << 0;
	  else {
	    if (denominator == 1) std::cout << numerator;
	    else std::cout << numerator << "/" << denominator;
	  }
	  std::cout << "\n\n";
		return 0;
	}

int gcd(int a, int b)    {
  int t;
  while (a)
    {
      t = a;
      a = b%a;
      b = t;
    }
  return b;
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}
