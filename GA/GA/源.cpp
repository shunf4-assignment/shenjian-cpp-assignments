#include <iostream>
#include <time.h>
#include <cstdio>
#include <conio.h>
#include <stdlib.h>
using namespace std;


typedef struct Chrom//����ṹ�����ͣ���ʾ����Ⱦɫ��Ľṹ
{
	short int bit[6];//6bit����Ⱦɫ����б��룬�������һλΪ����λ��ȡֵ��ΧΪ-64��+64
	int fit;//��Ӧֵ
	double rfit;//��Ե�fitֵ������ռ�İٷֱ�
	double cfit;//���۸���
}chrom;


/*��������*/
void *evpop(chrom popcurrent[4]);//������Ⱥ�ĳ�ʼ��
int x(chrom popcurrent);
int y(int x);
void *pickchroms(chrom popcurrent[4]);//ѡ�����
void *pickchroms_new(chrom popcurrent[4]);//���ڸ��ʷֲ�
void *crossover(chrom popnext[4]);//�������
void *mutation(chrom popnext[4]);//ͻ�����
double r8_uniform_ab(double a, double b, int &seed);//����a-b֮����ȷֲ�������


													/*�ṹ������*/
chrom popcurrent[4];//��ʼ��Ⱥ��ģΪ��
chrom popnext[4];//���º���Ⱥ��ģ��Ϊ��


				 /*������*/
int main()
{
	int num;//��������
	int i, j, k, l, Max;
	Max = 0;//�������ֵ
	cout << "               ��ӭ���������㷨�Ľ��ܣ�" << endl;
	cout << "*********************************************************" << endl;
	cout << "    �������ͨ�������㷨����y=-x^2+5������������ֵ   " << endl;
	cout << "*********************************************************" << endl;
	cout << "��������Ҫ�趨�ĵ�������";
	while (1)
	{
		cin >> num;
		if (cin.good())
		{
			if (num >= 1)
				break;
			else
			{
				cout << "����Ƿ�������������" << endl;
				continue;
			}
		}
		else
		{
			cout << "����Ƿ�������������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
	}

	//	Q:��ͬ����������ܽ����ͬ��
	//	A:�����õĵ����������٣�Ⱦɫ��Ļ����͹�������ֲ�����
	srand(unsigned int(time(0)));
	evpop(popcurrent);//���������ʼ��Ⱥ

					  //  Q:�Ƿ���Ҫָ��x��ȡֵ��Χ��
					  //  A:6bit����ʾ���֣���һλΪ����λ��5bit��ʾ���ִ�С�����ԣ�ȡֵ��ΧΪ-32-+31
	Max = popcurrent[0].fit;//��Maxֵ���г�ʼ��

	for (i = 0; i < num; i++)//��ʼ����
	{
		cout << endl;
		cout << "i=" << i << endl;///���������ǰ��������

		for (j = 0; j < 4; j++)//������Ⱥ
		{
			popnext[j] = popcurrent[j];
		}

		pickchroms(popnext);//��ѡ�������
		crossover(popnext); //����õ��¸���
		mutation(popnext);  //����õ��¸���

		for (j = 0; j < 4; j++)//��Ⱥ����
		{
			popcurrent[j] = popnext[j];
		}
	}//������ֹ
	 //���������������Ҫע��ȡ�ϴ�ĵ�������
	for (k = 0; k < 3; k++)
	{
		if (popcurrent[k].fit > Max)
		{
			Max = popcurrent[k].fit;
			l = x(popcurrent[k]);//��ʱ��ֵΪ�����xֵ
		}
	}
	cout << endl;
	cout << "��x=" << l << "ʱ�������õ����ֵΪ��" << Max << endl;
	getchar();
	return 0;

}

/*************************���ֺ�����������****************************/

/*���ɳ�ʼ�����Ⱥ�ĺ���*/
void *evpop(chrom popcurrent[4])
{
	int i, j, value;
	int random;
	double sum = 0;

	for (i = 0; i < 4; i++)//����Ⱥ�ĵ�1��Ⱦɫ�嵽��4��Ⱦɫ��
	{
		for (j = 0; j < 6; j++)//��Ⱦɫ��ĵ�1������λ����6������λ
		{
			random = rand();
			random = (random % 2);
			popcurrent[i].bit[j] = random;//�������Ⱦɫ����ûһ������λ��ֵ
		}

		value = x(popcurrent[i]);//��������תΪʮ����
		popcurrent[i].fit = y(value);//����Ⱦɫ�����Ӧ��ֵ
		sum += popcurrent[i].fit;
		cout << endl;//�������Ⱦɫ��ı����������
		cout << "popcurrent[" << i << "]=" << popcurrent[i].bit[5] << popcurrent[i].bit[4] << popcurrent[i].bit[3] << popcurrent[i].bit[2] << popcurrent[i].bit[1] << popcurrent[i].bit[0] << ' ';
		cout << "value=" << value << ' ';
		cout << "finess=" << popcurrent[i].fit << ' ';
	}
	for (i = 0; i < 4; i++)//������Ӧֵ�ðٷֱȣ��������̶�ѡ��
	{
		popcurrent[i].rfit = popcurrent[j].fit / sum;
		popcurrent[i].cfit = 0;//�����ʼ��Ϊ0
	}
	return 0;
}

/*���뺯������Ⱦɫ��Ķ�������ϢתΪʮ����*/
int x(chrom popcurrent)
{
	int z;
	z = (popcurrent.bit[0] * 1) + (popcurrent.bit[1] * 2) + (popcurrent.bit[2] * 4) + (popcurrent.bit[3] * 8) + (popcurrent.bit[4] * 16);
	if (popcurrent.bit[5] == 1)//���Ƿ���
	{
		z = -z;
	}
	return z;
}

/*��������Ӧ�Ⱥ���*/
int y(int x)               //��������������ֵ
{                          //��Ҫ�ܴ��ⲿֱ�Ӵ��亯������ǿ³����
	int y;                 //³���ԣ���ָ����ϵͳ��һ�����ṹ����С���Ĳ����㶯�£�ά������ĳЩ���ܵ����ԡ�
	y = -(x*x) + 5;
	return y;
}

/*ѡ��������������̶�ѡ�񷽷��������л����͵�ѡ��*/
/*1.������ʺ���*/
void *pickchroms_new(chrom popnext[4])
{
	int men, i, j;
	double p, sum = 0.0;
	//����Ⱥ������Ӧ��
	for (men = 0; men < 4; men++)
	{
		sum += popnext[men].fit;
	}
	//����ÿһ����Ա����Ӧ��
	for (men = 0; men < 4; men++)
	{
		popnext[men].rfit = popnext[men].fit / sum;
	}
	//������۸���
	for (men = 0; men < 4; men++)
	{
		popnext[men].cfit = popnext[men - 1].cfit + popnext[men].rfit;
	}

	for (i = 0; i < 4; i++)
	{
		//����0-1֮��������
		p = rand() % 10;
		p = p / 10;
		if (p < popnext[0].cfit)
		{
			popcurrent[i] = popnext[0];
		}
		else
		{
			for (j = 0; j < 4; j++)
			{
				if (popnext[j].cfit <= p&&p < popnext[j + 1].cfit)
					popcurrent[i] = popcurrent[j + 1];
			}
		}
	}
	//����Ⱥ���Ǿ���Ⱥ
	for (i = 0; i < 4; i++)
	{
		popnext[i] = popcurrent[i];
	}
	return 0;
}
/*2.ѡ����庯��*/
void *pickchroms(chrom popnext[4])
{
	int i, j;
	chrom temp;//�м����
			   //ð�ݷ������尴������Ӧ��������
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3 - i; j++)
		{
			if (popnext[j + 1].fit > popnext[j].fit)
			{
				temp = popnext[j + 1];
				popnext[j + 1] = popnext[j];
				popnext[j] = temp;

			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		cout << endl;
		cout << "Sorting:popnext[" << i << "]fitness=" << popnext[i].fit << endl;
	}
	_flushall();
	return 0;
}

/*����0-1֮����ȷֲ����ĺ���*/
double r8_uniform_ab(double a, double b, int &seed)
{
	{
		int i4_huge = 2147483647;
		int k;
		double value;

		if (seed == 0)
		{
			std::cerr << endl;
			std::cerr << "R8_UNIFORM_AB-Fatal error!" << endl;
			std::cerr << "Input value of SEED =0." << endl;
			exit(1);
		}

		k = seed / 127773;

		seed = 16807 * (seed - k * 127773) - k * 2836;

		if (seed < 0)
		{
			seed += i4_huge;
		}

		value = double(seed)*4.656612875E-10;

		value = a + (b - a)*value;

		return value;
	}
}

/*�������*/
void *crossover(chrom popnext[4])
{
	int random, i;
	//srand(time(0));
	random = rand();//������������
	random = ((random % 5) + 1);//����������0-5֮��
	for (i = 0; i < random; i++)
	{
		popnext[2].bit[i] = popnext[0].bit[i];//
		popnext[3].bit[i] = popnext[1].bit[i];
	}

	for (i = random; i < 6; i++)
	{
		popnext[2].bit[i] = popnext[1].bit[i];
		popnext[3].bit[i] = popnext[0].bit[i];
	}

	for (i = 0; i < 4; i++)
	{
		popnext[i].fit = y(x(popnext[i]));//Ϊ�¸��������Ӧֵ
	}

	for (i = 0; i < 4; i++)//����¸���
	{
		cout << endl;
		cout << "CrosOver popnext[" << i << "]=" << popnext[i].bit[5] << popnext[i].bit[4] << popnext[i].bit[3] << popnext[i].bit[2] << popnext[i].bit[1] << popnext[i].bit[0] << ' ';
		cout << "value=" << x(popnext[i]) << ' ';
		cout << "fitness=" << popnext[i].fit;
	}
	return 0;
}

/*�������*/
void *mutation(chrom popnext[4])
{
	int random, row, col, value;
	//srand(time(0))
	random = rand() % 50;//�������0-50֮�����
						 //�����������һ������Ϊ0��0.5֮��
	if (random == 25)//random==25�ĸ���ֻ�аٷ�֮��������С���ʽ��б���
	{
		col = rand() % 6;//�������Ҫ����Ļ���λ��
		row = rand() % 4;//�������Ҫ�����Ⱦɫ���

		if (popnext[row].bit[col] == 0)
			popnext[row].bit[col] = 1;
		else
			popnext[row].bit[col] = 0;
	}
	popnext[row].fit = y(x(popnext[row]));//�����������Ӧ��ֵ
	value = x(popnext[row]);

	cout << endl;//����������¸���
	cout << "Mutation occured in popnext[" << row << "]bit[" << col << "]=" << popnext[row].bit[5] << popnext[row].bit[4] << popnext[row].bit[3] << popnext[row].bit[2] << popnext[row].bit[1] << popnext[row].bit[0] << ' ';
	cout << "value=" << value << ' ';
	cout << "fitness=" << popnext[row].fit;
	return 0;
}