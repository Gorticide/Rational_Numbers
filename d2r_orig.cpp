//  g++ -g d2r.cpp fraction.cpp -std=c++11 -o d2r
// Michael William Hentrich
// 27 October 2018
// 5 December 2018 update: main() line 64 changed from (int)num, (int)den:
//            Fraction frac = Fraction(std::ceil(num), std::ceil(den));
// REASON:  number 0.03 with repeating 0.03: (int)2.9999999 becomes 2
// which gives bad result 2/90 = 1/45
// I need std::ceil(2.9999999) as it returns 3 to end up with 3/90 = 1/30

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <bits/stdc++.h>   // needed for fractionToDecimal
#include "fraction.h"

int numbers_after_decimal_point(double x);
int numbers_before_decimal_point(double x);
std::vector< std::pair< int, int> > dissect(double numeral);
Fraction build_fraction(std::vector< std::pair< int, int> > decimal);
int char2int(const char c);
std::string fractionToDecimal(int numr, int denr);

int main() {
  double N;
  double R;
  double den;
  double num;
  int p;
  int multiplier;
  int choice;

  std::cout << "\nTransform decimal numeral to rational number (fraction).\n";
  std::cout << "\n(1) Terminating decimal\n(2) Nonterminating repeating\n(3) Approximate\n\n";
  std::cin >> choice;

  switch(choice)  {
      case 1:
      {
          int Da, Db;  // number of digits after and before radix
          std::cout << "\nEnter the decimal numeral: ";
          std::cin >> N;
          std::vector< std::pair< int, int> > D = dissect(N);
          Fraction frac = build_fraction(D);
          std::cout << "\n " << N << " == " << frac << "\n\n";
          break;
      }
      case 2:
      {
           std::cout << "\nEnter the number up to and including repeating digits: ";
           std::cin >> N;
           std::cout << "\nPlease enter the number of repeating digits: ";
           std::cin >> p;
           std::cout << "\nYou must also enter the value of the first appearance of "
                     << "the repeating digits.\nThat is, include decimal point and leading zeros. "
                     << "For example:\n32.1306 with repeating 306 ----> 0.0306 : ";
           std::cin >> R;

           num = std::pow(10, p)*N + R - N;
           multiplier = numbers_after_decimal_point(num);
           num *= std::pow(10, multiplier);
           den = std::pow(10, p) - 1;
           den *= std::pow(10, multiplier);
           Fraction frac = Fraction(std::ceil(num), std::ceil(den));
           std::cout << "\n " << N << " == " << frac << "\n\n";
           break;
         }

      case 3:
      {
          printf("Enter a decimal number: ");
          scanf("%lf", &N);
          Fraction frac = Fraction(N);

           // printf("\n\n %lf ~=~ %d/%d", target, frac.getNum(), frac.getDen());
          std::cout << "\n " << N << " ~=~ " << frac << "\n";
          std::cout << "________________________________________________________________\n";

          // To inspect actual decimal representation of the approximate fraction
          std::string result = fractionToDecimal(frac.getNum(), frac.getDen());
          std::cout << "\nActual decimal representation of the approximate fraction ";
          std::cout << frac.getNum() << "/" << frac.getDen() << " :\n";
          std::cout << std::setprecision(12);
          std::cout << "\nDecimal Representation: " << frac.asDecimal() << std::endl;
        	if (result == "")
        		std::cout << "No recurring sequence\n\n";
        	else
        		std::cout << "Recurring sequence is " << result << std::endl
                      << "________________________________________________________________"
                      << std::endl;
          std::vector< std::pair< int, int> > D = dissect(N);
          Fraction frac2 = build_fraction(D);
          std::string clean = std::to_string(N);
          std::cout << "\nACTUAL RATIONAL VALUE of " << clean << " = " << frac2 << "\n\n";
          Fraction err = frac - frac2;
          std::cout << "Difference: " << frac << " - " << frac2 << " = " << err << " = "
                    << std::setprecision(9) << std::fixed
                    << err.asDecimal() << std::endl;
          std::cout << "\nrelative error: " << std::setprecision(3)
                    << std::fabs(err.asDecimal()/frac2.asDecimal()*100)
                    << "%\n\n";
          break;
        }
  }

}


/***********************************************************************/

int numbers_after_decimal_point(double x)  {
  double acceptedDiff = 2e-13;
  if (std::abs(x) - 0.0 < acceptedDiff) return 0;     // acceptedDiff = 2.27898e-13;
   std::stringstream sso;
   sso << std::setprecision(9) << std::showpoint << std::fixed
       << std::abs( x - (int)x );   // 27.44 - 27 ---> 0.44
   std::string Zahl;
   sso >> Zahl;
   size_t end = Zahl.find_last_not_of( '0' ) + 1 ;
   Zahl.erase(end);
   int result;

   if ( std::abs( x - (int)x ) == 0) return 0;
  // if (x > 0.1)
    result = Zahl.length() - 2;  // We don't want to count 0 and .
   //else result = Zahl.length();

   if (result < 0) return 0;
   else return result;

 }
/***********************************************************************/
/***********************************************************************/

 int numbers_before_decimal_point(double x)  {
     double acceptedDiff = 2e-13;
     int count = 0;
     int n = std::abs( (int)x );
     if (n - 0.0 > acceptedDiff) {
         while (n > 0) {
           n /= 10;
           count++;
         }
     }
     return count;
  }

/***********************************************************************/

std::vector< std::pair< int, int> > dissect(double numeral)   {
  //bool is_negative {false};
  int multiplier {1};
  std::vector< std::pair< int, int> > digits;
  int Db = numbers_before_decimal_point(numeral);
  //std::cout << "\nTEMP: digits before radix = " << Db << "\n";
  int Da = numbers_after_decimal_point(numeral);
  //std::cout << "\nTEMP: digits after radix = " << Da << "\n\n";
  std::string str = std::to_string(numeral);
  if (numeral < 0) {
    //is_negative = true;
    multiplier = -1;
    str.erase(0, std::min(str.find_first_not_of('-'), str.size()-1));
  }
  if (std::fabs(numeral) < 1.0) {
       str.erase(0, std::min(str.find_first_not_of('0'), str.size()-1));
  }

  for (int i = 0; i < Db; i++)  {
        std::pair<int, int> p(multiplier * char2int(str[i]), Db - (i+1));
        digits.push_back(p);
  }
  for (int i = 1; i <= Da; i++)  {
        std::pair<int, int> p(multiplier * char2int(str[Db+i]), -i);
        digits.push_back(p);
  }
  return digits;
}

Fraction build_fraction(std::vector< std::pair< int, int> > decimal)  {
     Fraction F(0,1);
     for (auto p : decimal)  {
       if (p.second >= 0)  {
           Fraction f(p.first * std::pow(10, p.second), 1);
           F = F + f;
       }
       else {
           Fraction f(p.first, std::pow(10, -p.second));
           F = F + f;
       }
     }
     return F;

}

int char2int (const char c)   {
    switch (c)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    default:
        return 0;
    }
}
// This function returns repeating sequence of
// a fraction. If repeating sequence doesn't
// exits, then returns empty string
std::string fractionToDecimal(int numr, int denr)
{
	std::string res; // Initialize result

	// Create a map to store already seen remainders.
	// Remainder is used as key and its position in
	// result is stored as value. Note that we need
	// position for cases like 1/6. In this case,
	// the recurring sequence doesn't start from first
	// remainder.
	std::map <int, int> mp;
	mp.clear();

	// Find first remainder
	int rem = numr%denr;

	// Keep finding remainder until either remainder
	// becomes 0 or repeats
	while ( (rem!=0) && (mp.find(rem) == mp.end()) )
	{
		// Store this remainder
		mp[rem] = res.length();

		// Multiply remainder with 10
		rem = rem*10;

		// Append rem / denr to result
		int res_part = rem / denr;
		res += std::to_string(res_part);

		// Update remainder
		rem = rem % denr;
	}

	return (rem == 0)? "" : res.substr(mp[rem]);
}
