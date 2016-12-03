/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;
#define maxNum 50
#define maxLen 10


int outer_function(int param)
{
	return param;
}

int main()
{
	void input_data(int studentNum, char name[maxNum][maxLen], char id[maxNum][maxLen]);
	void search(char query[maxLen], int studentNum, char name[maxNum][maxLen], char id[maxNum][maxLen]);

	int studentNum = 0;
	char studentName[maxNum][maxLen] = { '\0' };
	char studentID[maxNum][maxLen] = { '\0' };
	char studentQuery[maxLen] = { '\0' };
	
	while (true)
	{
		cout << "Please input the Number of the students in the class: ";
		cin >> studentNum;
		if (!cin.good() || studentNum <= 0 || studentNum > maxNum)
		{
			cout << "Input invalid or out of range! ";
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else
		{
			break;
		}
	}

	input_data(studentNum, studentName, studentID);
	
	cout << "Please input the name of the student you want to find: (less than "<< maxLen - 1 << " characters)";
	cin >> studentQuery;

	search(studentQuery, studentNum, studentName, studentID);

	return 0;
}

void input_data(int studentNum, char name[maxNum][maxLen], char id[maxNum][maxLen])
{
	cout << "Please input the name and ID of the " << studentNum << " student(s), space for a divider:";
	for (int i = 0; i < studentNum; i++) {
		if (i != 0 && getchar() == '\n')
		{
			cout << "Please input the name and ID of student " << i + 1 << " :";
		}
		cin >> name[i] >> id[i];
	}
}
void search(char query[maxLen], int studentNum, char name[maxNum][maxLen], char id[maxNum][maxLen])
{
	int i = 0;
	for (; i < studentNum; i++) {
		if (strcmp(query, name[i]) == 0)
		{
			cout << query << " found with ID " << id[i] << endl;
			break;
		}
	}
	if (i == studentNum)
	{
		cout << "Can' t find this student." << endl;
	}
}