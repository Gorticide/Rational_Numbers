// C++ program to find repeating sequence in a fraction
// g++ -g rat2dec.cpp -std=c++11 -o r2d
// need -std=c++11 to use std::string to_String(int)

#include <bits/stdc++.h>
#include <iomanip>      // std::setprecision
using namespace std;

// This function returns repeating sequence of
// a fraction. If repeating sequence doesn't
// exits, then returns empty string
string fractionToDecimal(int numr, int denr)
{
	string res; // Initialize result

	// Create a map to store already seen remainders
	// remainder is used as key and its position in
	// result is stored as value. Note that we need
	// position for cases like 1/6. In this case,
	// the recurring sequence doesn't start from first
	// remainder.
	map <int, int> mp;
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
		res += to_string(res_part);

		// Update remainder
		rem = rem % denr;
	}

	return (rem == 0)? "" : res.substr(mp[rem]);
}

// Driver code
int main(int argc, char* argv[])
{
  if (argc !=3)  {
    cout << "USE: " << argv[0] << " <numerator> <denominator>\n";
    cout << "to find recurring decimal sequence if it exists.\n";
    return 1;
  }
	int numr = atoi(argv[1]);
  int denr = atoi(argv[2]);
	string res = fractionToDecimal(numr, denr);
  cout << "\nRational Number: " << numr << "/" << denr << endl;
  cout << setprecision(18);
  cout << "\nDecimal Representation: " << double(numr)/double(denr) << endl;
	if (res == "")
		cout << "No recurring sequence\n\n";
	else
		cout << "Recurring sequence is " << res << endl << endl;
	return 0;
}
