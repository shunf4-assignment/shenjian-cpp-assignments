/* 1652270 计算机2班 冯舜 */

#include <iostream>
using namespace std;

/* 函数的原型定义不准变 */
int   tj_strlen(const char *str);
char *tj_strcat(char *s1, const char *s2);
char *tj_strcpy(char *s1, const char *s2);
char *tj_strncpy(char *s1, const char *s2, const int len);
int   tj_strcmp(const char *s1, const char *s2);
int   tj_strcasecmp(const char *s1, const char *s2);
int   tj_strncmp(const char *s1, const char *s2, const int len);
int   tj_strcasencmp(const char *s1, const char *s2, const int len);
char *tj_strupr(char *str);
char *tj_strlwr(char *str);
int   tj_strchr(const char *str, const char ch);
int   tj_strstr(const char *str, const char *substr);
int   tj_strrchr(const char *str, const char ch);
int   tj_strrstr(const char *str, const char *substr);
char *tj_strrev(char *str);

/* ----- 不允许定义任何形式的全局数组!!!!! ----- */

/* 函数实现部分，{ }内的东西可以任意调整，目前的return只是一个示例，可改变 */
int tj_strlen(const char *str)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL)
		return 0;
	char *p;
	for (p = (char *)str; *p; p++)
		;
	return p - str;
}

char *tj_strcat(char *s1, const char *s2)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if ((s1 == NULL) || (s2 == NULL))
		return s1;
	char *p = s1;
	while (*p)
		p++;
	while (*s2)
	{
		*(p++) = *(s2++);
	}
	*p = *s2;
	return s1;
}

char *tj_strcpy(char *s1, const char *s2)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if ((s1 == NULL) && (s2 == NULL))
		return NULL;
	if (s2 == NULL)
		return "";
	if ((s1 == NULL) || (s2 == NULL))
		return s1;
	char *p = s1;
	while (*s2)
	{
		*(p++) = *(s2++);
	}
	*p = *s2;
	return s1;
}

char *tj_strncpy(char *s1, const char *s2, const int len)
{
	if ((s1 == NULL) && (s2 == NULL))
		return NULL;
	if (s2 == NULL && len != 0)
		return s1;
	if (s2 == NULL)
		return "";
	if ((s1 == NULL) || (s2 == NULL))
		return s1;
	int i = 0;
	char *p = s1;
	while (*s2 && (i++) < len)
	{
		*(p++) = *(s2++);
	}
	return s1;
}

int tj_strcmp(const char *s1, const char *s2)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (s1 == NULL && s2 == NULL)
		return 0;
	if ((s1 == NULL) && !(s2 == NULL))
		return -1;
	if (!(s1 == NULL) && (s2 == NULL))
		return 1;
	const char *p = s1;
	while (*p || *s2)
	{
		if (*p != *s2)
			return *p - *s2;
		p++, s2++;
	}
	return 0;
}

int tj_strcasecmp(const char *s1, const char *s2)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (s1 == NULL && s2 == NULL)
		return 0;
	if ((s1 == NULL) && !(s2 == NULL))
		return -1;
	if (!(s1 == NULL) && (s2 == NULL))
		return 1;
	while (*s1 || *s2)
	{
		if (*s1 != *s2 && !(*s1 >= 'A' && *s1 <= 'Z' && (*s1 + 'a' - 'A' == *s2)) && !(*s1 >= 'a' && *s1 <= 'z' && (*s1 + 'A' - 'a' == *s2)))
			return *s1 - *s2;
		s1++, s2++;
	}
	return 0;
}

int tj_strncmp(const char *s1, const char *s2, const int len)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (s1 == NULL && s2 == NULL)
		return 0;
	if ((s1 == NULL) && !(s2 == NULL))
		return -1;
	if (!(s1 == NULL) && (s2 == NULL))
		return 1;
	int i = 0;
	while ((*s1 || *s2) && i < len)
	{
		if (*s1 != *s2)
			return *s1 - *s2;
		s1++, s2++, i++;
	}
	return 0;
}

int tj_strcasencmp(const char *s1, const char *s2, const int len)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (s1 == NULL && s2 == NULL)
		return 0;
	if ((s1 == NULL) && !(s2 == NULL))
		return -1;
	if (!(s1 == NULL) && (s2 == NULL))
		return 1;
	int i = 0;
	while ((*s1 || *s2) && i < len)
	{
		if (*s1 != *s2 && !(*s1 >= 'A' && *s1 <= 'Z' && (*s1 + 'a' - 'A' == *s2)) && !(*s1 >= 'a' && *s1 <= 'z' && (*s1 + 'A' - 'a' == *s2)))
			return *s1 - *s2;
		s1++, s2++, i++;
	}
	return 0;
}

char *tj_strupr(char *str)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL)
		return NULL;
	char *p = str;
	while (*p)
	{
		*p += (*p >= 'a' && *p <= 'z') ? ('A' - 'a') : 0;
		p++;
	}
	return str;
}

char *tj_strlwr(char *str)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL)
		return NULL;
	char *p = str;
	while (*p)
	{
		*p += (*p >= 'A' && *p <= 'Z') ? ('a' - 'A') : 0;
		p++;
	}
	return str;
}

int tj_strchr(const char *str, const char ch)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL)
		return 0;
	const char *p = str;
	while (*p)
	{
		if (*p == ch)
			return p - str + 1;
		p++;
	}
	return 0;
}

int tj_strstr(const char *str, const char *substr)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL || substr == NULL)
		return 0;
	const char *p = str;
	const char *p2 = str;
	const char *q = substr;
	while (*p)
	{
		q = substr;
		if (*p == *q)
		{
			p2 = p;
			while (*q)
			{
				q++;
				p2++;
				if (!(*p2 == *q))
					break;
			}
			if (!(*q))
				return p - str + 1;
		}
		p++;
	}
	return 0;
}

int tj_strrchr(const char *str, const char ch)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL)
		return 0;
	const char *p = str;
	while (*p)
		p++;
	p--;
	while (p != str - 1)
	{
		if (*p == ch)
			return p - str + 1;
		p--;
	}
	return 0;
}

int tj_strrstr(const char *str, const char *substr)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL || substr == NULL)
		return 0;
	const char *p = str + tj_strlen(str) - 1;
	const char *p2 = str;
	const char *q = substr + tj_strlen(substr) - 1;
	const char *q2;
	while (p != str - 1)
	{
		q2 = q;
		if (*p == *q2)
		{
			p2 = p;
			while (q2 != substr - 1)
			{
				q2--;
				p2--;
				if (!(*p2 == *q2))
					break;
			}
			if (q2 == substr - 1)
				return (p2 - str) + 2;
		}
		p--;
	}
	return 0;
}

char *tj_strrev(char *str)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL)
		return NULL;
	char *p = str, *q = str, c;
	while (*p)
		p++;
	p--;
	while (p - str >= 1)
	{
		c = *p;
		*p = *str;
		*str = c;
		p--;
		str++;
	}
	return q;
}
