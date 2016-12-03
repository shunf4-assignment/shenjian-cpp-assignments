#include <iostream>
#include <time.h>
#include <cstdio>
#include <conio.h>
#include <stdlib.h>
using namespace std;


typedef struct Chrom//定义结构体类型，表示单个染色体的结构
{
	short int bit[6];//6bit来对染色体进行编码，其中最后一位为符号位，取值范围为-64到+64
	int fit;//适应值
	double rfit;//相对的fit值，即所占的百分比
	double cfit;//积累概率
}chrom;


/*函数声明*/
void *evpop(chrom popcurrent[4]);//进行种群的初始化
int x(chrom popcurrent);
int y(int x);
void *pickchroms(chrom popcurrent[4]);//选择操作
void *pickchroms_new(chrom popcurrent[4]);//基于概率分布
void *crossover(chrom popnext[4]);//交叉操作
void *mutation(chrom popnext[4]);//突变操作
double r8_uniform_ab(double a, double b, int &seed);//生成a-b之间均匀分布的数字


													/*结构体数组*/
chrom popcurrent[4];//初始种群规模为；
chrom popnext[4];//更新后种群规模仍为；


				 /*主函数*/
int main()
{
	int num;//迭代次数
	int i, j, k, l, Max;
	Max = 0;//函数最大值
	cout << "               欢迎来看基因算法的介绍！" << endl;
	cout << "*********************************************************" << endl;
	cout << "    这个程序将通过基因算法来求y=-x^2+5这个函数的最大值   " << endl;
	cout << "*********************************************************" << endl;
	cout << "请输入您要设定的迭代数：";
	while (1)
	{
		cin >> num;
		if (cin.good())
		{
			if (num >= 1)
				break;
			else
			{
				cout << "输入非法，请重新输入" << endl;
				continue;
			}
		}
		else
		{
			cout << "输入非法，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
	}

	//	Q:不同的随机数可能结果不同？
	//	A:所设置的迭代次数过少，染色体的基因型过早陷入局部最优
	srand(unsigned int(time(0)));
	evpop(popcurrent);//随机产生初始种群

					  //  Q:是否需要指定x的取值范围？
					  //  A:6bit来表示数字，第一位为符号位，5bit表示数字大小，所以，取值范围为-32-+31
	Max = popcurrent[0].fit;//对Max值进行初始化

	for (i = 0; i < num; i++)//开始迭代
	{
		cout << endl;
		cout << "i=" << i << endl;///用于输出当前迭代次数

		for (j = 0; j < 4; j++)//更新种群
		{
			popnext[j] = popcurrent[j];
		}

		pickchroms(popnext);//挑选优秀个体
		crossover(popnext); //交叉得到新个体
		mutation(popnext);  //变异得到新个体

		for (j = 0; j < 4; j++)//种群更替
		{
			popcurrent[j] = popnext[j];
		}
	}//迭代终止
	 //对于真正随机数需要注意取较大的迭代次数
	for (k = 0; k < 3; k++)
	{
		if (popcurrent[k].fit > Max)
		{
			Max = popcurrent[k].fit;
			l = x(popcurrent[k]);//此时的值为所求的x值
		}
	}
	cout << endl;
	cout << "当x=" << l << "时，函数得到最大值为：" << Max << endl;
	getchar();
	return 0;

}

/*************************各种函数定义如下****************************/

/*生成初始随机种群的函数*/
void *evpop(chrom popcurrent[4])
{
	int i, j, value;
	int random;
	double sum = 0;

	for (i = 0; i < 4; i++)//从种群的第1个染色体到第4个染色体
	{
		for (j = 0; j < 6; j++)//从染色体的第1个基因位到第6个基因位
		{
			random = rand();
			random = (random % 2);
			popcurrent[i].bit[j] = random;//随机产生染色体上没一个基因位的值
		}

		value = x(popcurrent[i]);//将二进制转为十进制
		popcurrent[i].fit = y(value);//计算染色体的适应度值
		sum += popcurrent[i].fit;
		cout << endl;//输出整条染色体的编码情况如下
		cout << "popcurrent[" << i << "]=" << popcurrent[i].bit[5] << popcurrent[i].bit[4] << popcurrent[i].bit[3] << popcurrent[i].bit[2] << popcurrent[i].bit[1] << popcurrent[i].bit[0] << ' ';
		cout << "value=" << value << ' ';
		cout << "finess=" << popcurrent[i].fit << ' ';
	}
	for (i = 0; i < 4; i++)//计算适应值得百分比，用于轮盘赌选择法
	{
		popcurrent[i].rfit = popcurrent[j].fit / sum;
		popcurrent[i].cfit = 0;//将其初始化为0
	}
	return 0;
}

/*解码函数：将染色体的二进制信息转为十进制*/
int x(chrom popcurrent)
{
	int z;
	z = (popcurrent.bit[0] * 1) + (popcurrent.bit[1] * 2) + (popcurrent.bit[2] * 4) + (popcurrent.bit[3] * 8) + (popcurrent.bit[4] * 16);
	if (popcurrent.bit[5] == 1)//考虑符号
	{
		z = -z;
	}
	return z;
}

/*求个体的适应度函数*/
int y(int x)               //函数函数，求函数值
{                          //需要能从外部直接传输函数，加强鲁棒性
	int y;                 //鲁棒性：是指控制系统在一定（结构，大小）的参数摄动下，维持其它某些性能的特性。
	y = -(x*x) + 5;
	return y;
}

/*选择操作（基于轮盘赌选择方法）：进行基因型的选择*/
/*1.计算概率函数*/
void *pickchroms_new(chrom popnext[4])
{
	int men, i, j;
	double p, sum = 0.0;
	//求种群的总适应度
	for (men = 0; men < 4; men++)
	{
		sum += popnext[men].fit;
	}
	//计算每一个成员的适应度
	for (men = 0; men < 4; men++)
	{
		popnext[men].rfit = popnext[men].fit / sum;
	}
	//计算积累概率
	for (men = 0; men < 4; men++)
	{
		popnext[men].cfit = popnext[men - 1].cfit + popnext[men].rfit;
	}

	for (i = 0; i < 4; i++)
	{
		//产生0-1之间的随机数
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
	//新种群覆盖旧种群
	for (i = 0; i < 4; i++)
	{
		popnext[i] = popcurrent[i];
	}
	return 0;
}
/*2.选择个体函数*/
void *pickchroms(chrom popnext[4])
{
	int i, j;
	chrom temp;//中间变量
			   //冒泡法将个体按个体适应度来排序
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

/*产生0-1之间均匀分布数的函数*/
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

/*交叉操作*/
void *crossover(chrom popnext[4])
{
	int random, i;
	//srand(time(0));
	random = rand();//随机产生交叉点
	random = ((random % 5) + 1);//交叉点控制在0-5之间
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
		popnext[i].fit = y(x(popnext[i]));//为新个体计算适应值
	}

	for (i = 0; i < 4; i++)//输出新个体
	{
		cout << endl;
		cout << "CrosOver popnext[" << i << "]=" << popnext[i].bit[5] << popnext[i].bit[4] << popnext[i].bit[3] << popnext[i].bit[2] << popnext[i].bit[1] << popnext[i].bit[0] << ' ';
		cout << "value=" << x(popnext[i]) << ' ';
		cout << "fitness=" << popnext[i].fit;
	}
	return 0;
}

/*变异操作*/
void *mutation(chrom popnext[4])
{
	int random, row, col, value;
	//srand(time(0))
	random = rand() % 50;//随机产生0-50之间的数
						 //变异操作概率一般设置为0到0.5之间
	if (random == 25)//random==25的概率只有百分之二，所以小概率进行变异
	{
		col = rand() % 6;//随机产生要变异的基因位号
		row = rand() % 4;//随机产生要变异的染色体号

		if (popnext[row].bit[col] == 0)
			popnext[row].bit[col] = 1;
		else
			popnext[row].bit[col] = 0;
	}
	popnext[row].fit = y(x(popnext[row]));//计算变异后的适应度值
	value = x(popnext[row]);

	cout << endl;//输出变异后的新个体
	cout << "Mutation occured in popnext[" << row << "]bit[" << col << "]=" << popnext[row].bit[5] << popnext[row].bit[4] << popnext[row].bit[3] << popnext[row].bit[2] << popnext[row].bit[1] << popnext[row].bit[0] << ' ';
	cout << "value=" << value << ' ';
	cout << "fitness=" << popnext[row].fit;
	return 0;
}