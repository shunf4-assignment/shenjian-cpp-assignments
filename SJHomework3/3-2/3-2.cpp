/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	const double pi = 3.14159265;
	double r, h;
	double cirCir, cirArea, sphArea, sphVol, cylVol;
	cout << "Please input the radius of the circle. r = ";
	cin >> r;
	cout << "Please input the height. h = ";
	cin >> h;

	cirCir = r * 2 * pi;				//Բ�ܳ�
	cirArea = r * r * pi ;				//Բ���

	sphArea = r * r * pi * 4;			//������
	sphVol = r * r * r * pi * 4.0 / 3;	//�����
	
	cylVol = cirArea * h;				//Բ�����

	cout << endl;
	cout << "Results are as follows:" << endl;
	cout << setiosflags(ios::fixed) << setprecision(2);
	cout << "\tThe Circumference of the Circle: " << cirCir << endl;
	cout << "\tThe Area of the Circle: " << cirArea << endl;
	cout << "\tThe Superficial Area of the Sphere: " << sphArea << endl;
	cout << "\tThe Volume of the Sphere: " << sphVol<< endl;
	cout << "\tThe Volume of the Cylinder: " << cylVol << endl;

	return 0;
}