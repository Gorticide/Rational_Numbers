//  g++ -g ratroots.cpp fraction.cpp -std=c++11 -o ratroots
// Michael William Hentrich
// 2 November 2018

#include <iostream>
#include <cmath>
#include <vector>
#include <utility>  // for std::pair
//#include <algorithm>  // for std::sort
#include <set>
#include <string>
#include "fraction.h"

using std::cout;
using std::cin;
using std::vector;
using std::set;

typedef vector<int> factors;

// terms[i].first: coefficient
// terms[i].second exponent
vector< std::pair< int, int> > terms;

vector< std::pair< int, int> > get_terms();
Fraction power(Fraction base, int degree);
factors get_factors(int num);
set<Fraction> build_possible_roots(factors LT, factors C);
set<Fraction> write_results(factors LT, factors C);
bool test(Fraction R);
std::string simpleEquation(vector< std::pair<int, int> > poly);

bool error {false};
int divisor, last;

int main()  {
    set<Fraction> solutions;
    terms = get_terms();
    std::string equation = simpleEquation(terms);
    if (!error)  {
      factors leading_term = get_factors(terms[0].first);
      factors constant = get_factors(terms[last - 1].first);
      solutions = write_results(leading_term, constant);
    }
    else cout << "ILLEGAL POLYNOMIAL\n\n";

    cout << "___________________________________________________________\n\n"
         << "For the equation, " << equation;

    if ( solutions.empty() ) {
         cout << ",\nthere are no rational roots.\n";
         cout << "\n___________________________________________________________\n\n";
    }
    else  {
      cout << ",\nthe set of rational roots is:\n\n{  ";
      for (auto r : solutions) {
        cout << r << "  ";
      }
      cout << "}\n" << "___________________________________________________________"
           << "\n\n";
    }

}

std::vector< std::pair< int, int> > get_terms()  {
    int coef, deg;
    vector< std::pair< int, int> > polynomial;
    error = false;

    cout << "\nEnter number of terms in the polynomial: ";
    cin >> last;
    cout << "\nTerms will be numbered from highest degree term down to constant.\n";
    for (int i = 0; i < last; i++)  {
      cout << "\nEnter coefficient " << i + 1 << ": ";
      cin >> coef;
      cout << "Enter degree: ";
      cin >> deg;
      std::pair<int, int> p(coef, deg);
      polynomial.push_back(p);
    }

    if (polynomial[0].first == 0)    error = true;  // must have leading term
    if (polynomial[last - 1].first == 0)  error = true;   // must have constant term
    if (polynomial[last - 1].second != 0)  error = true;  // x^0 = 1

    return polynomial;
}

// if this works, add to Fraction class with overloaded operator:
// 	 Fraction operator^(int degree) {return power(degree);}
Fraction power (Fraction base, int degree)  {
  Fraction frac(0,1);
  if (degree >= 0) {
    if (degree == 0)   frac = 1;
    else frac = power(base, degree - 1) * base;
  }
  else {
      degree = -degree;
      frac = Fraction(1,1)/power(base, degree);
  }
  return frac;
}


factors  get_factors (int num)  {
  num = abs(num);
  factors list;
  divisor = 0;

  do {
    divisor += 1;
    if (num%divisor == 0) list.push_back(divisor);
  }  while (divisor != num);

  return list;
}

set<Fraction> build_possible_roots(factors LT, factors C)  {

  set<Fraction> PRR; // possible rational roots

  // the first integer of factors vector contained number of elements
  // but I replaced this with size() as it is more direct and eliminates need for count
  for (int i = 0; i < LT.size(); i++)  {
      for (int j = 0; j < C.size(); j++)  {
          Fraction f = Fraction(C[j], LT[i]);
          PRR.insert(f);
          Fraction g = Fraction(-C[j], LT[i]);
          PRR.insert(g);
      }
  }

  return PRR;
}

set<Fraction> write_results (factors LT, factors C)  {

    cout << "\n p is a factor of " << terms[terms.size() - 1].first
         << "\n p belongs to the set {  ";
    for (auto f : C)  {
      cout << f << "  " << -f << "  ";
    }
    cout << "}\n";

    cout << "\n q is a factor of " << terms[0].first
         << "\n q belongs to the set {  ";
    for (auto f : LT)  {
      cout << f << "  " << -f << "  ";
    }
    cout << "}\n";

    // vector of fractions, where
    //  numerator = [+/-] constant
    //  denominator = leading_term
    set<Fraction> possible = build_possible_roots(LT, C);

    cout << "\n-------------------------------------------------------\n"
         << "\nThe possible rational roots in fractional form p/q:\n\n";

    int j = 1;
    // print out the possible roots in fractional form
    for (auto f : possible) {
        // 6 per row
        if (j % 6) {
            cout << f << '\t';
        }
        else {
            cout << f << '\n';
        }
        j++;
    }
    cout << "\n-------------------------------------------------------\n";
    cout << "\n\nTesting possible rational roots:\n";
    set<Fraction> roots;

    for (auto p : possible)  if ( test(p) ) roots.insert(p);

    return roots;
}

bool test(Fraction R)  {
    int coefficient, exponent;
    Fraction p_of_x = Fraction(0,1);

    for (int i = 0; i < last; i++)  {
        coefficient = terms[i].first;
        Fraction C = Fraction(coefficient, 1);
        exponent = terms[i].second;
        p_of_x += C*power(R, exponent);
    }
    cout << std::endl << R;
    Fraction Zero = Fraction(0, 1);
    if (p_of_x == Zero)  {
      cout << " is a root.\n";
      return true;
    }
    else {
      cout << " is not a root.\n";
      return false;
    }
}
std::string simpleEquation(vector< std::pair<int, int> > poly)  {
  char sign;
  std::string val;
  std::string exp;
  std::string eqn = "";

  for (auto t : poly)  {
    if (t.first < 0)  {
      sign = '-';
      val = std::to_string(-t.first);
    }
    else  {
      sign = '+';
      val = std::to_string(t.first);
    }
    if (t.second != 0) {
      if (t.second != 1)  exp = " x^" + std::to_string(t.second) + ' ';
      else exp = " x ";
    }
    else exp = ' ';
    eqn += sign;

    if ( abs(t.first) != 1 ) {
      eqn += ' ';
      eqn.append(val);
    }
    eqn += exp;
  }
   eqn.append("== 0");
   return eqn;
}
/*  Used before deciding to change vector<Fraction> to set<Fraction>
std::sort(PRR.begin(), PRR.end());
auto hindmost = std::unique(PRR.begin(), PRR.end());
PRR.erase(hindmost, PRR.end());
*/
