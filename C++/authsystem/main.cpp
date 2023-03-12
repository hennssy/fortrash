#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <fstream>

using namespace std;

string formatcheck(string insert)
{
	while(insert.find(":") == string::npos)
	{
		cout << "Логин и пароль введены не по формату\n";
		cout << "Повторите попытку: ";
		getline(cin, insert);
	}
	
	return insert;
}

string loginadd(string insert)
{
	string login;
	
	for(int i = 0; i < insert.find(":"); i++)
	{
		login += insert[i];
	}
	
	return login;
}

string passwordadd(string insert)
{
	string password;
	
	for(int i = insert.find(":") + 1; i < insert.length(); i++)
	{
		password += insert[i];
	}
	
	return password;
}

void userdel(string insert)
{
	ifstream users("users.txt");
	ofstream temp("temp.txt");
	int position;
	string check;
	
	while(getline(users, check))
	{
		position = check.find(":");
		
		if(check.find(insert) != string::npos) continue;
		else temp << check << "\n"; 
	}
	
	users.close();
	temp.close();
	remove("users.txt");
	rename("temp.txt", "users.txt");
}

void useradd(string insert, string flag)
{
	ofstream users("users.txt", ios::app);
	if(flag == "Да" || flag == "да") users << insert << " SU\n";
	else if(flag == "Нет" || flag == "нет") users << insert << "\n"; 
	
	else
	{
		cout << "\nУказан неправильный ответ, возврат в меню...";
		return void();
	}
	
	cout << "\nПользователь успешно добавлен\nВозврат в меню...";
	users.close();
}

int rolecheck(string insert)
{
	string check;
	int flag = 0, position;
	ifstream users("users.txt");
	
	while(getline(users, check))
	{
		position = check.find(":");
		
		if(check.find(insert) != string::npos)
		{
			if(check.find("SU", position) != string::npos) 
			{
				flag = 1;
				break;
			}
			
			else 
			{
				flag = 0;
				break;
			}
		}
		
		else flag = 2;
	}
	
	users.close();
	return flag;
}

void menudel(string insert)
{
	string adminchoise;
	cout << "\nВы хотите его удалить?\n\nВаш выбор(да/нет):";
	getline(cin, adminchoise);
			
	if(adminchoise == "Да" || adminchoise == "да")
	{
		userdel(insert);
		cout << "\nУдаление успешно завершено\nВозврат в меню...";
		Sleep(3000);
	}
			
	else if(adminchoise == "Нет" || adminchoise == "нет")
	{
		cout << "\nВозврат в меню...";
		Sleep(3000);
		return void();
	}
			
	else
	{
		cout << "\nУказан неправильный ответ, возврат в меню...";
		Sleep(3000);
		return void();
	}
}

void menuadd(string insert)
{
	string adminchoise, flag;
	cout << "\nВы хотите его добавить?\n\nВаш выбор(да/нет): ";
	getline(cin, adminchoise);
			
	if(adminchoise == "Да" || adminchoise == "да")
	{
		cout << "\nДать пользователю права администратора?\n\nВаш выбор: ";
		getline(cin, flag);
		useradd(insert, flag);
		Sleep(3000);
	}
			
	else if(adminchoise == "Нет" || adminchoise == "нет")
	{
		cout << "\nВозврат в меню...";
		Sleep(3000);
		return void();
	}
			
	else
	{
		cout << "\nУказан неправильный ответ, возврат в меню...";
		Sleep(3000);
		return void();
	}
}

void userchange(string insert)
{
	system("cls");
	cout << setw(50) << "Редактирование пользователей\n\n";
	cout << "Проверка " << insert << "...\n";
	int flag = rolecheck(insert);
	string login = loginadd(insert), password = passwordadd(insert);
	
	switch(flag)
	{
		case 0:
			cout << "\nПользователь " << login << " существует и имеет обычные права";
			menudel(insert);
			break;
		case 1: 
			cout << "\nПользователь " << login << " существует и имеет права администратора";
			menudel(insert);
			break;
		case 2:
			cout << "\nУказанный пользователь отсутствует";
			menuadd(insert);
			break;
	}
}

void superuser()
{
	int choise;
	
	do
	{
		system("cls");
		cout << setw(50) << "Меню администратора\n\n";
		cout << "Доступны следующие функции:\n1 - Изменение списка пользователей\n2 - Открытие файла\n3 - Выход из системы\n\n";
		cout << "Ваш выбор: ";
		cin >> choise;
		string insert;
		
		switch(choise)
		{
			case 1: 
				cout << "\nВведите логин и пароль пользователя: ";
				cin.ignore();
				getline(cin, insert);
				insert = formatcheck(insert);
				userchange(insert);
				break;
			case 2:
				cout << "\nОткрытие файла...";
				system("userpass.txt");
				cout << "\nРабота с файлом завершена...";
				Sleep(3000);
				system("cls");
				break;
		}
	} while (choise != 3);
	
	return void();
}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string insert;
	int flag;
	cout << setw(50) << "Авторизация\n\n";
	cout << "Введите логин и пароль: ";
	getline(cin, insert);
	insert = formatcheck(insert);
	flag = rolecheck(insert);
	
	switch(flag)
	{
		case 0:
			cout << "\nВы вошли в систему как обычный пользователь\n";
			cout << "Открытие файла...";
			Sleep(3000);
			system("userpass.txt");
			cout << "\n\nРабота с системой завершена. Всего доброго!";
			Sleep(3000);
			break;
		case 1:
			cout << "\nВы вошли в систему как администратор\nПереход в меню...";
			Sleep(3000);
			superuser();
			cout << "\n\nРабота с системой завершена. Всего доброго!";
			Sleep(3000);
			break;
		case 2:
			cout << "\nУказанный пользователь не внесён в систему\n";
			cout << "Обратитесь к администратору";
			break;
	}
}
