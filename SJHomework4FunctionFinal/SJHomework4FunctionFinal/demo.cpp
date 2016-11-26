/*刘爱新 1652323 计算机三班*/
#include<iostream>
using namespace std;
double jisuan(double a, double b, char fuhao)
{
	//cout << a << " " << b << " ";
	switch (fuhao)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return (a*1.0)*b;
		case '/':
			if (b != 0)
				return  (a*1.0) / b;
			if (b == 0)
				return 1e-6;
	}
	return 0;
}

int main()
{
	double s1, s2, s3, s4;
	int  i, j, k;
	double temp1, temp2, temp3;
	char fuhao1, fuhao2, fuhao3;
	cin >> s1 >> s2 >> s3 >> s4;
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
			case 0:fuhao1 = '+', temp1 = jisuan(s1, s2, fuhao1);
			case 1:fuhao1 = '-', temp1 = jisuan(s1, s2, fuhao1);
			case 2:fuhao1 = '*', temp1 = jisuan(s1, s2, fuhao1);
			case 3:fuhao1 = '/', temp1 = jisuan(s1, s2, fuhao1);
		}
		cout << temp1 << " ";
		for (j = 0; j < 4; j++)
		{
			switch (j)
			{
				case 0:fuhao2 = '+', temp2 = jisuan(s3, s4, fuhao2);
				case 1:fuhao2 = '-', temp2 = jisuan(s3, s4, fuhao2);
				case 2:fuhao2 = '*', temp2 = jisuan(s3, s4, fuhao2);
				case 3:fuhao2 = '/', temp2 = jisuan(s3, s4, fuhao2);
			}
			for (k = 0; k < 4; k++)
			{
				switch (k)
				{
					case 0:fuhao3 = '+', temp3 = jisuan(temp1, temp2, fuhao3);
					case 1:fuhao3 = '-', temp3 = jisuan(temp1, temp2, fuhao3);
					case 2:fuhao3 = '*', temp3 = jisuan(temp1, temp2, fuhao3);
					case 3:fuhao3 = '/', temp3 = jisuan(temp1, temp2, fuhao3);
				}
				if (fabs(temp3 - 24)<1e-5)
					cout << "(" << s1 << fuhao1 << s2 << ")" << fuhao3 << "(" << s3 << fuhao2 << s4 << ")" << "=24" << endl;
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
			case 0:fuhao1 = '+', temp1 = jisuan(s1, s2, fuhao1);
			case 1:fuhao1 = '-', temp1 = jisuan(s1, s2, fuhao1);
			case 2:fuhao1 = '*', temp1 = jisuan(s1, s2, fuhao1);
			case 3:fuhao1 = '/', temp1 = jisuan(s1, s2, fuhao1);
		}
		for (j = 0; j < 4; j++)
		{
			switch (j)
			{
				case 0:fuhao2 = '+', temp2 = jisuan(temp1, s2, fuhao2);
				case 1:fuhao2 = '-', temp2 = jisuan(temp1, s2, fuhao2);
				case 2:fuhao2 = '*', temp2 = jisuan(temp1, s2, fuhao2);
				case 3:fuhao2 = '/', temp2 = jisuan(temp1, s2, fuhao2);
			}
			for (k = 0; k < 4; k++)
			{
				switch (k)
				{
					case 0:fuhao3 = '+', temp3 = jisuan(s4, temp2, fuhao3);
					case 1:fuhao3 = '-', temp3 = jisuan(s4, temp2, fuhao3);
					case 2:fuhao3 = '*', temp3 = jisuan(s4, temp2, fuhao3);
					case 3:fuhao3 = '/', temp3 = jisuan(s4, temp2, fuhao3);
				}
				if (fabs(temp3 - 24)<1e-5)
					cout << "((" << s1 << fuhao1 << s2 << ")" << fuhao2 << s3 << ")" << fuhao3 << s4 << "=24" << endl;
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
			case 0:fuhao1 = '+', temp1 = jisuan(s3, s2, fuhao1);
			case 1:fuhao1 = '-', temp1 = jisuan(s3, s2, fuhao1);
			case 2:fuhao1 = '*', temp1 = jisuan(s3, s2, fuhao1);
			case 3:fuhao1 = '/', temp1 = jisuan(s3, s2, fuhao1);
		}
		for (j = 0; j < 4; j++)
		{
			switch (j)
			{
				case 0:fuhao2 = '+', temp2 = jisuan(s1, temp1, fuhao2);
				case 1:fuhao2 = '-', temp2 = jisuan(s1, temp1, fuhao2);
				case 2:fuhao2 = '*', temp2 = jisuan(s1, temp1, fuhao2);
				case 3:fuhao2 = '/', temp2 = jisuan(s1, temp1, fuhao2);
			}
			for (k = 0; k < 4; k++)
			{
				switch (k)
				{
					case 0:fuhao3 = '+', temp3 = jisuan(s4, temp2, fuhao3);
					case 1:fuhao3 = '-', temp3 = jisuan(s4, temp2, fuhao3);
					case 2:fuhao3 = '*', temp3 = jisuan(s4, temp2, fuhao3);
					case 3:fuhao3 = '/', temp3 = jisuan(s4, temp2, fuhao3);
				}
				if (fabs(temp3 - 24)<1e-5)
					cout << "(" << s1 << fuhao2 << "(" << s2 << fuhao1 << s3 << "))" << fuhao2 << s4 << "=24" << endl;
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
			case 0:fuhao1 = '+', temp1 = jisuan(s3, s2, fuhao1);
			case 1:fuhao1 = '-', temp1 = jisuan(s3, s2, fuhao1);
			case 2:fuhao1 = '*', temp1 = jisuan(s3, s2, fuhao1);
			case 3:fuhao1 = '/', temp1 = jisuan(s3, s2, fuhao1);
		}
		for (j = 0; j < 4; j++)
		{
			switch (j)
			{
				case 0:fuhao2 = '+', temp2 = jisuan(temp1, s4, fuhao2);
				case 1:fuhao2 = '-', temp2 = jisuan(temp1, s4, fuhao2);
				case 2:fuhao2 = '*', temp2 = jisuan(temp1, s4, fuhao2);
				case 3:fuhao2 = '/', temp2 = jisuan(temp1, s4, fuhao2);
			}
			for (k = 0; k < 4; k++)
			{
				switch (k)
				{
					case 0:fuhao3 = '+', temp3 = jisuan(s1, temp2, fuhao3);
					case 1:fuhao3 = '-', temp3 = jisuan(s1, temp2, fuhao3);
					case 2:fuhao3 = '*', temp3 = jisuan(s1, temp2, fuhao3);
					case 3:fuhao3 = '/', temp3 = jisuan(s1, temp2, fuhao3);
				}
				if (fabs(temp3 - 24)<1e-5)
					cout << s1 << fuhao3 << "((" << s2 << fuhao1 << s3 << ")" << fuhao2 << s4 << ")" << "=24" << endl;
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
			case 0:fuhao1 = '+', temp1 = jisuan(s4, s3, fuhao1);
			case 1:fuhao1 = '-', temp1 = jisuan(s4, s3, fuhao1);
			case 2:fuhao1 = '*', temp1 = jisuan(s4, s3, fuhao1);
			case 3:fuhao1 = '/', temp1 = jisuan(s4, s3, fuhao1);
		}
		for (j = 0; j < 4; j++)
		{
			switch (j)
			{
				case 0:fuhao2 = '+', temp2 = jisuan(temp1, s2, fuhao2);
				case 1:fuhao2 = '-', temp2 = jisuan(temp1, s2, fuhao2);
				case 2:fuhao2 = '*', temp2 = jisuan(temp1, s2, fuhao2);
				case 3:fuhao2 = '/', temp2 = jisuan(temp1, s2, fuhao2);
			}
			for (k = 0; k < 4; k++)
			{
				switch (k)
				{
					case 0:fuhao3 = '+', temp3 = jisuan(s1, temp2, fuhao3);
					case 1:fuhao3 = '-', temp3 = jisuan(s1, temp2, fuhao3);
					case 2:fuhao3 = '*', temp3 = jisuan(s1, temp2, fuhao3);
					case 3:fuhao3 = '/', temp3 = jisuan(s1, temp2, fuhao3);
				}
				if (fabs(temp3 - 24)<1e-5)
				{
					cout << s1 << fuhao3 << "(" << s2 << fuhao2 << "(" << s3 << fuhao1 << s4 << "))" << "=24" << endl;
				}
			}
		}
	}
}
