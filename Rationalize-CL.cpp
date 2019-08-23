//  g++ -g Rationalize-CL.cpp fraction.cpp -std=c++11 -o rat
// Michael William Hentrich
// September 2018

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <cstdlib>   // atof
#include "fraction.h"


int main(int argc, char *argv[])  {

      if (argc!= 2)  {
	std::cout << "[USE] : " << argv[0] << " <decimal>";
  std::cout << "\nYou cannot have " << argc - 1 << " parameters.\n\n";
	return -1;
     }
  double target = atof(argv[1]);
	Fraction frac = Fraction(target);
  std::cout << "\n " << target << " ~=~ " << frac << "\n\n";
}
