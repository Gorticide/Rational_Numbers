//  g++ -g test_constructor.cpp fraction.cpp -std=c++11 -o test
// Michael William Hentrich
// September 2018

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include "fraction.h"


int main() {
  double target;
	printf("Enter a decimal number: ");
	scanf("%lf", &target);
	Fraction frac = Fraction(target);

  // printf("\n\n %lf ~=~ %d/%d", target, frac.getNum(), frac.getDen());
  std::cout << "\n " << target << " ~=~ " << frac << "\n\n";
}
