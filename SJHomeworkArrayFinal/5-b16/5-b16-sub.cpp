/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;
/* ����ʵ�ֲ��֣�{ }�ڵĶ����������������Ŀǰ��return 0ֻ��һ��ʾ�����ɸı� */

int tj_strlen(const char str[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return i; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strcat(char s1[], const char s2[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	int j = 0;
	while (s1[i])
	{
		i++;
	}
	while (s2[j])
	{
		s1[i] = s2[j];
		j++;
		i++;
	}
	s1[i] = s2[j];
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strcpy(char s1[], const char s2[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strncpy(char s1[], const char s2[], const int len)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while (s2[i] && i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strcmp(const char s1[], const char s2[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return s1[i] - s2[i];
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strcasecmp(const char s1[], const char s2[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i] && !(s1[i] >= 'A' && s1[i] <= 'Z' && (s1[i] + 'a' - 'A' == s2[i] || s1[i] == s2[i])) && !(s1[i] >= 'a' && s1[i] <= 'z' && (s2[i] + 'a' - 'A' == s1[i] || s1[i] == s2[i])))
			return s1[i] - s2[i];
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strncmp(const char s1[], const char s2[], const int len)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while ((s1[i] || s2[i]) && i < len)
	{
		if (s1[i] != s2[i])
			return s1[i] - s2[i];
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strcasencmp(const char s1[], const char s2[], const int len)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while ((s1[i] || s2[i]) && i < len)
	{
		if (s1[i] != s2[i] && !(s1[i] >= 'A' && s1[i] <= 'Z' && (s1[i] + 'a' - 'A' == s2[i] || s1[i] == s2[i])) && !(s1[i] >= 'a' && s1[i] <= 'z' && (s2[i] + 'a' - 'A' == s1[i] || s1[i] == s2[i])))
			return s1[i] - s2[i];
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strupr(char str[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while (str[i])
	{
		str[i] += -(str[i] >= 'a' && str[i] <= 'z') * ('a' - 'A');
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strlwr(char str[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while (str[i])
	{
		str[i] += (str[i] >= 'A' && str[i] <= 'Z') * ('a' - 'A');
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strchr(const char str[], char ch)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return i + 1;
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strstr(const char str[], const char substr[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (str[i] == substr[0]) {
			j = 0;
			while (substr[j])
			{
				j++;
				if (!(str[i + j] == substr[j]))
					break;
			}
			if (!substr[j])
				return i + 1;
		}
		i++;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strrchr(const char str[], const char ch)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = tj_strlen(str) - 1;
	while (str[i])
	{
		if (str[i] == ch)
			return i + 1;
		i--;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strrstr(const char str[], const char substr[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int i = tj_strlen(str) - 1;
	int j = tj_strlen(substr) - 1;
	int k = j;
	while (str[i])
	{
		if (str[i] == substr[j]) {
			while (j >= 0)
			{
				j--;
				if (!(str[i - (k - j)] == substr[j]))
					break;
			}
			if (j < 0)
				return i - k + 1;
			j = k;
		}
		i--;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}

int tj_strrev(char str[])
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
	int n = tj_strlen(str);
	char a;
	for (int i = 0; i < n / 2; i++)
	{
		a = str[n - i - 1];
		str[n - i - 1] = str[i];
		str[i] = a;
	}
	return 0; //returnֵ�ɸ�����Ҫ�޸�
}
