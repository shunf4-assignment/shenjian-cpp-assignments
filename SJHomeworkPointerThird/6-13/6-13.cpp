/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
using namespace std;
#define FS_SLICES 1e7
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max())

double fun_sin(double x)
{
	return sin(x);
}

double fun_cos(double x)
{
	return cos(x);
}

double fun_exp(double x)
{
	return exp(x);
}

double definite_integration(double fun(double), double low, double high)
{
	double value = 0;
	double dx = (high - low) / FS_SLICES;
	int sign = (high > low ? 1 : -1);
	while ((high - low)*sign > 0)
	{
		value += dx * fun(low);
		low += dx;
	}
	return value;
}

template <typename T>
void inputThing(T* p, const char * promptText, const char * cinUngoodText, const char * outLimitText, T lowerLimit, T upperLimit, bool clearBuffer = false)
{
	bool valid;
	do
	{
		valid = true;
		cout << promptText;
		cin >> *p;

		if (!cin.good())
		{
			valid = false;
			cout << cinUngoodText << endl;
		}
		else if (*p > upperLimit || *p < lowerLimit)
		{
			valid = false;
			cout << outLimitText << endl;
		}

		if (!valid)
		{
			cin.clear();
			cin.ignore(FS_MAX_LENGTH, '\n');
		}

	} while (!valid);
	if (clearBuffer)
		cin.ignore(FS_MAX_LENGTH, '\n');
}

int main()
{
	//REINPUT:
	
	double high, low, value;
	inputThing(&low, "������sinx�Ļ������ޣ�", "��������Ƿ���", "�������볬����Χ��", -DBL_MAX, DBL_MAX, true);
	inputThing(&high, "������sinx�Ļ������ޣ�", "��������Ƿ���", "�������볬����Χ��", -DBL_MAX, DBL_MAX, true);
	value = definite_integration(fun_sin, low, high);
	cout << "Integrate(" << low << "," << high << ")[sinxdx] = " << value << endl;

	inputThing(&low, "������cosx�Ļ������ޣ�", "��������Ƿ���", "�������볬����Χ��", -DBL_MAX, DBL_MAX, true);
	inputThing(&high, "������cosx�Ļ������ޣ�", "��������Ƿ���", "�������볬����Χ��", -DBL_MAX, DBL_MAX, true);
	value = definite_integration(fun_cos, low, high);
	cout << "Integrate(" << low << "," << high << ")[cosxdx] = " << value << endl;

	inputThing(&low, "������e^x�Ļ������ޣ�", "��������Ƿ���", "�������볬����Χ��", -DBL_MAX, DBL_MAX, true);
	inputThing(&high, "������e^x�Ļ������ޣ�", "��������Ƿ���", "�������볬����Χ��", -DBL_MAX, DBL_MAX, true);
	value = definite_integration(fun_exp, low, high);
	cout << "Integrate(" << low << "," << high << ")[e^xdx] = " << value << endl;

	//goto REINPUT;
	return 0;
}
