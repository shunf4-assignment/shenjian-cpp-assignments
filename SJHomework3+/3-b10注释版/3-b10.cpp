/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;
#define out0 cout << "��"
#define nout cout << ""
#define outthis (toOut == 1) ? (cout << "Ҽ") : (nout),(toOut == 2) ? (cout << "��") : (nout),(toOut == 3) ? (cout << "��") : (nout),(toOut == 4) ? (cout << "��") : (nout),(toOut == 5) ? (cout << "��") : (nout),(toOut == 6) ? (cout << "½") : (nout),(toOut == 7) ? (cout << "��") : (nout),(toOut == 8) ? (cout << "��") : (nout),(toOut == 9) ? (cout << "��") : (nout),(toOut == 0) ? (cout << "��") : (nout)
/*
����һ�� outthis �Ĵ����߼�
��toOut��ֵΪĳ����λ���Ļ���ִ��outthis���Ϳ��������Ӧ��д��
outthis��ʮ���ӱ��ʽ���ֱ��ö��Ÿ�����ÿ���������(toOut == 1) ? (cout << "Ҽ") : (nout)�������׿���������nout��ʾ cout << ""����ʾʲô���������
*/

#define groupOutput ((!p1) ? ((!zeroPut && (p2 + p3 + p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p1, outthis, cout << "Ǫ", zeroPut = false, z), ((!p2) ? ((!zeroPut && (p3 + p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p2, outthis, cout << "��", zeroPut = false, z)), ((!p3) ? ((!zeroPut && (p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p3, outthis, cout << "ʰ", zeroPut = false, z)), ((!p4) ? (z) : (toOut = p4, outthis, zeroPut = false, z)))
/*
����һ�� groupOutput �Ĵ����߼�

��α��ʽ����Ҫ�����ǽ���λ��������� p1 p2 p3 p4 ���� XǧX�١��� �ĸ�ʽ�����

z��һ��Ϊ0�Ĳ���ֵ����;�Ƿ�����Ŀ����� boolean1 ? () : () ��û�в����ĵط�����������˵����ʲô�����ɡ�
zeroPut������ָʾ���㡱�Ƿ�����ǰ���Ѿ�������Ŀ��أ�����������ֹ�ظ�����㡣


��ʼ������p1, �ȼ���Ƿ��������㡣�ʼ�ķ�֧�ṹ��(!p1)����p1Ϊ������н������Ĳ���2,3������Ӳ���4��ʼ��
2. ��һ������������������(!zeroPut && (p2 + p3 + p4))��zeroPut���عرգ���p2 p3 p4��ȫΪ�� ������ȫΪ�㣬���൱��[0]000������ʡ���㣩
3. 2Ϊ�棬����������Ĳ��������ʱ��Ҫ��zeroPut��������true����ʾ����һλ��ʼ�����. ����p1���������������
����4����p1��Ϊ0������Ҫ��p1����������Ƚ�toOut��������ü�����������֣���ֵ��Ϊp1��ֵ��Ȼ��ִ��outthis���������ϣ�����ǧ��ʮλ��Ҫ��Ӧ���ǧ��ʮ����Ҫ��zeroPut��������false����������һλ��ʼ���������. ����p1���������������

����p2, p3, p4����p1��ͬ�����̣������ڼ�������������У�p2 p3 p4�ĳɱȸ�λ�͵�����λ���ɣ���λȫΪ�㣬�൱��01[0]0����һ��[��] ��[��] ����ʡ�ԣ�
*/

int main()
{
	double inputNum, inputNumCopy;
	int d10, d9, d8, d7, d6, d5, d4, d3, d2, d1, dm1, dm2, p1, p2, p3, p4, toOut;
	bool zeroPut = true, z = 0, hasYuan = false;  //zeroPut�ĳ�ʼֵ��Ϊtrue����Ϊ������� ����ʮ�ڡ�

	cout << "�������ת���Ľ������(0.01��100��) ";
	cin >> inputNum;
	inputNumCopy = inputNum;

	(((((((((inputNumCopy -= (d10 = (int)(inputNumCopy / 1e9)) * 1e9) -= (d9 = (int)(inputNumCopy / 1e8)) * 1e8) -= (d8 = (int)(inputNumCopy / 1e7)) * 1e7) -= (d7 = (int)(inputNumCopy / 1e6)) * 1e6) -= (d6 = (int)(inputNumCopy / 1e5)) * 1e5) -= (d5 = (int)(inputNumCopy / 1e4)) * 1e4) -= (d4 = (int)(inputNumCopy / 1e3)) * 1e3) -= (d3 = (int)(inputNumCopy / 1e2)) * 1e2) -= (d2 = (int)(inputNumCopy / 1e1)) * 1e1) -= (d1 = (int)(inputNumCopy));  //��������

	inputNumCopy = (int)(inputNumCopy * 100 + 0.5);  //С������
	(inputNumCopy -= (dm1 = (int)(inputNumCopy / 10)) * 10) -= (dm2 = (int)(inputNumCopy));

	cout << "�ֽ�����" << endl;
	cout << "\tʮ��λ�� " << d10 << endl;
	cout << "\t  ��λ�� " << d9 << endl;
	cout << "\tǧ��λ�� " << d8 << endl;
	cout << "\t����λ�� " << d7 << endl;
	cout << "\tʮ��λ�� " << d6 << endl;
	cout << "\t  ��λ�� " << d5 << endl;
	cout << "\t  ǧλ�� " << d4 << endl;
	cout << "\t  ��λ�� " << d3 << endl;
	cout << "\t  ʮλ�� " << d2 << endl;
	cout << "\t  ��λ�� " << d1 << endl;
	cout << "\tʮ��λ�� " << dm1 << endl;
	cout << "\t�ٷ�λ�� " << dm2 << endl;

	cout << "��д��";

	hasYuan = !!(d10 + d9 + d8 + d7 + d6 + d5 + d4 + d3 + d2 + d1);
	p1 = 0, p2 = 0, p3 = d10, p4 = d9, groupOutput, (p1 + p2 + p3 + p4) && (cout << "��");  //��&&�൱����if����Ϊ��·����
	p1 = d8, p2 = d7, p3 = d6, p4 = d5, groupOutput, (p1 + p2 + p3 + p4) && (cout << "��");
	p1 = d4, p2 = d3, p3 = d2, p4 = d1, groupOutput, hasYuan && (cout << "Բ");

	(!dm1) ? ((hasYuan && dm2) ? (out0) : (nout)) : (toOut = dm1, outthis, cout << "��"), (!dm2) ? (!!(inputNum) && (cout << "��"), z) : (toOut = dm2, outthis, cout << "��", z);

	(!(inputNum)) && (cout << "��Բ��");

	cout << endl;
	cout << "�������н�����" << endl;

	return 0;
}