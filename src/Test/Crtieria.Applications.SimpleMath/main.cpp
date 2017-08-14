#include "MathFunctions.h"

int main()
{

	MathFunctions functions;
	

	cout << atof("3,20") << endl;
	cout << (int)atof("3.20") << endl;
	cout << functions.Add (1.1, 1) << endl;
	cout << functions.Sub(1, 1) << endl;
	cout << functions.Div(15.6,5) << endl;
	cout << functions.Mul(1,1) << endl;
	cout << functions.Pot(2,3) << endl;
	cout << functions.Sqrt(4) << endl;
	cout << functions.Int(4.76) << endl;

	char a;
	cin >> a;

	return 0;
}