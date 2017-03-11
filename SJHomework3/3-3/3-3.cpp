/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
	double c;
	double f;
	
	cout << "Please input temperature value in Fahrenheit(number f). f = ";
	cin >> f;

	c = 5.0 / 9 * (f - 32);
	cout << setiosflags(ios::fixed) << setprecision(2);
	cout << "Temperature in Celcius: " << c << " degree C." << endl;

	return 0;
}