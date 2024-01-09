#include <iostream>
#include <string>
#include "io.h"
#include <fstream>
using namespace std;

//login paswor score

class Question
{
private:
	string question;
	int answer;
public:

	bool AddQuestion()
	{

		string useranswer;
		cout << question << endl;
		cout << "Введите ответ: ";
		cin >> useranswer;


		for (int i = 0; i < useranswer.size(); i++)
		{
			if (!isdigit(useranswer[i]))
			{

				if (i == 0 and useranswer[i] == '-')
				{
					continue;
				}

			}
		}

		if (to_string(answer) == useranswer)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void SetQuestion(string str)
	{
		question = str;
	}

	void SetAnswer(int answer)
	{
		this->answer = answer;
	}
};
class Test : public Question
{
private:
	Question test[4];
	double results = 0;
public:
	void SetTest()
	{
		/*P:\\Студенты\\П22\\C++\\ООП\\Вопросы.txt*/
		fstream file("C:\\Users\\User\\Desktop\\Вопросы.txt");
		string str;
		for (int i = 0; i < 4; i++)
		{
			getline(file, str);
			test[i].SetQuestion(str);
		}
		file.close();
		/*P:\\Студенты\\П22\\C++\\ООП\\Ответы.txt*/
		fstream file2("C:\\Users\\User\\Desktop\\ответы.txt");
		string str2;
		for (int i = 0; i < 4; i++)
		{
			getline(file2, str2);
			test[i].SetAnswer(atoi(str2.c_str()));
		}
		file2.close();
	}

	double Pass()
	{
		/*P:\\Студенты\\П22\\C++\\ООП\\Answers.txt*/
		ofstream file("C:\\Users\\User\\Desktop\\qwerqwerqwer.txt", ios::app);
		for (int i = 0; i < 4; i++)
		{
			results += test[i].AddQuestion();
		}
		file << results / 4 * 100 << '%' << endl;
		file.close();
		return results / 4 * 100;

	}
};

class User :Test
{
	string login;
	string password;
	double scors[1024];
	int scorsAmount;
public:
	User()
	{
		scorsAmount = 0;
		SetTest();
	}

	bool GetUser()
	{
		fstream file;
		string str;
		bool wrongPasswd = false;
		string _login;
		bool noUser = true;

		file.open("C:\\Users\\User\\Desktop\\qwerqwerqwer.txt");

		while (getline(file, str))
		{
			if (str == _login)
			{
				noUser = false;

				getline(file, str);

				string passwd;


				for (int i = 0; i < 3; i++)
				{
					cout << "Введите пароль: ";
					cin >> password;

					if (passwd != str)
					{
						cout << "Неверный пароль!";
						if (i != 2)
						{
							cout << " Повторите попытку.\n";
						}
						else
						{
							cout << endl;
						}
						wrongPasswd = true;
						continue;
					}
					wrongPasswd = false;
					break;
				}
			}
		}

		file.close();

		if (noUser)
		{
			cout << "Пользователя с таким логином не существует!\n";
			cout << "Возвращение в главное меню...\n\n";
			return false;
		}

		if (wrongPasswd)
		{
			return false;
		}
		return true;
	}

	void registration()
	{

		string arr[1488];
		fstream file;
		file.open("C:\\Users\\User\\Desktop\\qwerqwerqwer.txt");
		int counterLines = 0;
		for (int i = 0; getline(file, arr[i]); i++)
		{
			counterLines++;
		}
		file.close();

		cout << "Введите логин: ";
		cin >> login;


		cout << "Введите пароль: ";
		cin >> password;



	}

	void PassTest()
	{
		scors[scorsAmount] = Pass();
		scorsAmount++;

	}

	void SaveUser()
	{


		ofstream file;
		file.open("C:\\Users\\User\\Desktop\\qwerqwerqwer.txt", ios::app);

		file << login << endl << password << endl;

		for (int i = 0; i < scorsAmount - 1; i++)
		{
			file << to_string(scors[i]) << ';';
		}

		file.close();


	}



	void ShowResults()
	{
		for (int i = 0; i < 1; i++)
		{
			cout << scors[i];
		}
		cout << '%';
	}
};

int main()
{
	setlocale(LC_ALL, "RU");
	User user;
	cout << "Введите 1, если вы хотите создать пользователя; Введите 2, если вы хоите войти;";
	cout << endl;
	int x;
	cin >> x;

	switch (x)
	{
	case 1:
		user.registration();
		;
		break;
	case 2:
		user.GetUser();
		;
	}
	user.SaveUser();
	user.PassTest();
	user.ShowResults();
}