/*
Approximate with scientific notation :
(precision, maximum possible error, and relative error)

Michael William Hentrich
29 October 208

INPUT: a x 10^n, where a, a rational number in finite decimal form,
       is between 1 and 10, and n is an integer.  Because the decimal for a
       contains as many digits as the accuracy of the measurement justifies,
       these are called significant digits.

       For the input, imagine a caret placed after the first significant digits
       in the given number.  By counting the number of places FROM THE CARET TO
       THE DECIMAL POINT, you obtain n.

       n is positive or negative according as you count to the right or
       to the left from the caret.

EXAMPLE:  0.03 04 : a = 3.04 so n = -2   (significant digits: 3, 0, 4)
          0.0304 = 3.04 x 10^(-2)
          precision to the nearest 1/10000

Enter significant digits:
Enter n:  (3.04 x 10^n):
Enter unit of measurement (string u):

OUTPUT:  The precision is the last significant digit plus n
         Example: 4.0 x 10^(-4)
         last significant digit is 0.1, which is 10^(-1)
         So, (-1) + (-4) = -5 and precision iis 10^(-5) or 1/100,000 u

         Maximum Possible Error: half of the precision
         Example: 0.5 x 10^(-5) = 5 x 10^(-6)

         Accuracy (relative error):
         (Maximum Possible Error)/(Actual Measurement)
         Example: (5 x 10^(-6))/(4 x 10^(-4)) = (5/4)10^(-6+4) = 1.25 x 10^(-2)
                  = 0.0125 = 1.25%
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>

int numbers_before_decimal_point(double x);

int main() {
  double a_real;
  std::string a_str;
  int Da;
  int Db {2};
  int n;
  std::string u;

     std::cout << "INPUT: a x 10^n,\nwhere a, a rational number in finite decimal form, "
               << "\nis between 1 and 10, and n is an integer.  Because the decimal for \n"
               << "'a' contains as many digits as the accuracy of the measurement justifies,"
               << "\nthese are called significant digits.\n\n";

     std::cout << "For the input, imagine a caret placed after the first significant digit"
               << "\nin the given number.  By counting the number of places FROM THE CARET"
               << "\nTO THE DECIMAL POINT, you obtain n.\n\nn is positive or negative"
               << " according as you count to the right or\nto the left from the caret.\n\n";

    while (Db > 1) {
      std::cout << "Enter significant digits ('a'): ";
      std::cin >> a_str;
      a_real = std::stod(a_str);
      if (a_str.length() == 1)  a_str += '.';
      Db = numbers_before_decimal_point(a_real);
      if (Db > 1) std::cout << "Number of digits before decimal point exceeds 1\n"
                            << "Please put in proper form.\n";
    }
    std::cout << "Enter n:  (" << a_str << " x 10^n): ";
    std::cin >> n;
    std::cout << "Enter unit of measurement: ";
    std::cin >> u;
    std::cout << "\n\nScientific Notation: " << a_str << " x 10^(" << n << ")\n\n";
    Da = a_str.length() - 2;

    if (n - Da < 0)
       std::cout << "The precision is 1/" << (long long)std::pow(10, -n + Da) << "th of a " << u;
    else
       std::cout << "The precision is " << (long long)std::pow(10, n - Da) << ' ' << u;

    // Create an output string stream
    std::ostringstream oss;
    oss.precision(std::numeric_limits<double>::digits10);


    // Set Fixed -Point Notation to suppress scientific notation
    // maximum possible error
    oss << std::fixed << 0.5*std::pow(10, n - Da);   //Add double to stream

    // Set precision to (n - Da - 1) digits
    //oss << std::setprecision(-n + Da + 1);

    // Get string from output string stream
    std::string err_str = oss.str();

    // Remove padding
    // This must be done in two steps because of numbers like 700.00
    std::size_t pos1 = err_str.find_last_not_of("0");
    if(pos1 != std::string::npos)   err_str.erase(pos1+1);

    std::size_t pos2 = err_str.find_last_not_of(".");
    if(pos2 != std::string::npos)  err_str.erase(pos2+1);

    std::cout << std::setprecision(1);
    std::cout << "\n\nThe maximum possible error is "
              << 0.5*std::pow(10, n - Da) << ' ' << u
              << " = 5 x 10^(" << n - Da - 1 <<  ") " << u << " = " << err_str << ' ' << u;

    std::cout << "\n\nThe accuracy (relative error) is " << std::setprecision(3)
              << (0.5)*std::pow(10, n - Da + 2)/(a_real*std::pow(10, n)) << '%';
    std::cout << std::endl << std::endl;
}

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
