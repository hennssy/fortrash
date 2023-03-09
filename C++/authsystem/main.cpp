#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <cstdio>

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

void admindel()
{
	cin.ignore();
	system("cls");
	cout << setw(50) << "Удаление Администратора\n\n";
	string insert, login, password, chose, check;
	int flag = 1;
	cout << "Введите логин и пароль Администратора, которого необходимо удалить, в формате логин:пароль: ";
	getline(cin, insert);
	insert = formatcheck(insert);
	ifstream superuser("superusers.txt");
	
	while(getline(superuser, check))
	{
		while(getline(superuser, check))
		{
			if(check == insert) flag = 0;
		}
		
		while(flag)
		{
			cout << "Указанного администратора не существует\n";
			cout << "Повторите попытку: ";
			getline(cin, insert);
			insert = formatcheck(insert);
			superuser.clear();
			superuser.seekg(0);
			
			while(getline(superuser, check))
			{
				if(check == insert) flag = 0;
			}
		}
	}
	
	login = loginadd(insert);
	password = passwordadd(insert);
	cout << "Вы уверены, что хотите удалить Администратора " << login << "?\n";
	getline(cin, chose);
	
	if(chose == "Да" || chose == "да")
	{
		cout << "Администратор успешно удалён";
	}
	
	if(chose == "Нет" || chose == "нет")
	{
		cout << "Возвращаемся в меню";
		Sleep(3000);
		return void();
	}
	
	ofstream temp;
	temp.open("temp.txt");
	superuser.clear();
	superuser.seekg(0);
	
	while(getline(superuser, check))
	{
		if(check == insert) continue;
		else temp << check << "\n";
	}
	
	temp.close();
	superuser.close();
	remove("superusers.txt");
	rename("temp.txt", "superusers.txt");
	Sleep(3000);
}

void adminadd()
{
	cin.ignore();
	system("cls");
	cout << setw(50) << "Добавление Администратора\n\n";
	string login, password, insert, chose, check;
	int flag;
	cout << "Введите логин и пароль администратора в формате логин:пароль: ";
	getline(cin, insert);
	insert = formatcheck(insert);
	ofstream superusers;
	ifstream superuser("superusers.txt");
	superusers.open("superusers.txt", ios::app);
	
	while(getline(superuser, check))
	{
		if(check == insert)
		{
			flag = 1;
			
			while(flag)
			{
				cout << "Указанный Администратор уже существует\n";
				cout << "Вы хотите продолжить?(да/нет)\n";
				string continuechose;
				getline(cin, continuechose);
				
				if(continuechose == "Да" || continuechose == "да")
				{
					cout << "Введите логин и пароль: ";
					getline(cin, insert);
					insert = formatcheck(insert);
					
					if(check != insert)
					{
						flag = 0;
						superuser.clear();
						superuser.seekg(0);
					}
				}
				
				if(continuechose == "Нет" || continuechose == "нет") 
				{
					cout << "Возвращаемся в меню";
					flag = 0;
					Sleep(3000);
					system("cls");
					return void();	
				} 									
			}
		}
	}
	
	login = loginadd(insert);
	password = passwordadd(insert);
	cout << "Добавить Администратора " << login << " с паролем " << password << "?(да/нет)\n";
	getline(cin, chose);
	
	if(chose == "Да" || chose == "да")
	{
		if(superusers.is_open())
		{
			superusers << insert << "\n";
		}
	
		superusers.close();
		
		cout << "\nАдминистратор успешно добавлен, возвращаемся в меню";
		Sleep(3000);
		return void();
	}
	
	if(chose == "Нет" || chose == "нет")
	{
		cout << "Вы отказались добавлять администратора, возвращаемся в меню";
		Sleep(3000);
		system("cls");
		return void();
	}
}

void useradd()
{
	cin.ignore();
	system("cls");
	cout << setw(50) << "Добавление Пользователя\n\n";
	string login, password, insert, chose, check;
	int flag;
	cout << "Введите логин и пароль нового Пользователя в формате логин:пароль: ";
	getline(cin, insert);
	insert = formatcheck(insert);
	ofstream users;
	ifstream user("users.txt");
	users.open("users.txt", ios::app);
	
	while(getline(user, check))
	{
		if(check == insert)
		{
			flag = 1;
			
			while(flag)
			{
				cout << "Указанный Пользователь уже существует\n";
				cout << "Вы хотите продолжить?(да/нет)\n";
				string continuechose;
				getline(cin, continuechose);
				
				if(continuechose == "Да" || continuechose == "да")
				{
					cout << "Введите логин и пароль: ";
					getline(cin, insert);
					insert = formatcheck(insert);
					
					if(check != insert)
					{
						flag = 0;
						user.clear();
						user.seekg(0);
					}
				}
				
				if(continuechose == "Нет" || continuechose == "нет") 
				{
					cout << "Возвращаемся в меню";
					flag = 0;
					Sleep(3000);
					system("cls");
					return void();	
				} 									
			}
		}
	}
	
	login = loginadd(insert);
	password = passwordadd(insert);
	cout << "Добавить Пользователя " << login << " с паролем " << password << "?(да/нет)\n";
	getline(cin, chose);
	
	if(chose == "Да" || chose == "да")
	{
		if(users.is_open())
		{
			users << insert << "\n";
		}
	
		users.close();
		
		cout << "\nПользователь успешно добавлен, возвращаемся в меню";
		Sleep(3000);
		return void();
	}
	
	if(chose == "Нет" || chose == "нет")
	{
		cout << "Вы отказались добавлять Пользователя, возвращаемся в меню";
		Sleep(3000);
		system("cls");
		return void();
	}
}

void userdel()
{
	cin.ignore();
	system("cls");
	cout << setw(50) << "Удаление Пользователя\n\n";
	string insert, login, password, chose, check;
	int flag = 1;
	cout << "Введите логин и пароль Пользователя, которого необходимо удалить, в формате логин:пароль: ";
	getline(cin, insert);
	insert = formatcheck(insert);
	ifstream user("users.txt");
	
	while(getline(user, check))
	{
		while(getline(user, check))
		{
			if(check == insert) flag = 0;
		}
		
		while(flag)
		{
			cout << "Указанного Пользователя не существует\n";
			cout << "Повторите попытку: ";
			getline(cin, insert);
			insert = formatcheck(insert);
			user.clear();
			user.seekg(0);
			
			while(getline(user, check))
			{
				if(check == insert) flag = 0;
			}
		}
	}
	
	login = loginadd(insert);
	password = passwordadd(insert);
	cout << "Вы уверены, что хотите удалить Пользователя " << login << "?\n";
	getline(cin, chose);
	
	if(chose == "Да" || chose == "да")
	{
		cout << "Пользователь успешно удалён";
	}
	
	if(chose == "Нет" || chose == "нет")
	{
		cout << "Возвращаемся в меню";
		Sleep(3000);
		return void();
	}
	
	ofstream temp;
	temp.open("temp.txt");
	user.clear();
	user.seekg(0);
	
	while(getline(user, check))
	{
		if(check == insert) continue;
		else temp << check << "\n";
	}
	
	temp.close();
	user.close();
	remove("users.txt");
	rename("temp.txt", "users.txt");
	Sleep(3000);
}

void superuser()
{
	int chose;
	
	do
	{
		cout << setw(75) << "Вы вошли в систему как пользователь с правами Администратора\n"
			"Вам доступны следующие функции: \n"
			"1. Изменение списка Администраторов\n"
			"2. Изменение списка Пользователей\n"
			"3. Получить доступ к файлу\n"
			"4. Возврат в меню аутентификации\n\n"
			"Выберите функцию из списка: ";
		cin >> chose;
		int adminchose;
		
		if(chose == 3)
		{
			system("cls");
			system("userpass.txt");
		}
		
		do
		{
			switch(chose)
			{
				case 1:
					system("cls");
					cout << setw(50) << "Изменение списка Администраторов\n";
					cout << "1. Добавление нового Администратора\n"
						"2. Удаление уже существующего Администратора\n"
						"3. Возврат в предыдущее меню\n\n"
						"Выберите функцию из списка: ";
					cin >> adminchose;
					if(adminchose == 1) adminadd();
					if(adminchose == 2) admindel();
					break;
				
				case 2:
					system("cls");
					cout << setw(50) << "Изменение списка Пользователей\n";
					cout << "1. Добавление нового Пользователя\n"
						"2. Удаление уже существующего Пользователя\n"
						"3. Возврат в предыдущее меню\n\n"
						"Выберите функцию из списка: ";
					cin >> adminchose;
					if(adminchose == 1) useradd();
					if(adminchose == 2) userdel();
					break;

				case 3:
					adminchose = 3;
					break;

				case 4:
					system("cls");
					return void();
					break;
			} 
			system("cls");
		} while (adminchose != 3);
		system("cls");
	} while (chose != 4);
}

int auth(string insert)
{
	ifstream users("users.txt");
	string check;
	int flag = 2;
	
	while(getline(users, check))
	{
		if(check == insert) flag = 0;
	}
	
	users.close();
	ifstream superusers("superusers.txt");
	
	while(getline(superusers, check))
	{
		if(check == insert) flag = 1;
	}
	
	superusers.close();
	return flag;
}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << setw(50) << "Авторизация\n";
	cout << "Введите логин и пароль: ";
	string insert;
	getline(cin, insert);
	insert = formatcheck(insert);
	int flag = auth(insert);

	if(flag == 0)
	{
		cout << "Вы авторизовались как обычный Пользователь\n"
			"Открытие файла...";
		Sleep(3000);
		system("userpass.txt");
		system("cls");
	}
	
	if(flag == 1)
	{
		cout << "Вы авторизовались с правами Администратора\n"
			"Открытие меню...";
		Sleep(3000);
		system("cls");
		superuser();
	}
	
	if(flag == 2)
	{
		cout << "Указанного пользователя не существует\n"
			"Повторите попытку или обратитесь к Администратору";
	}
	
	cout << "Работа с системой успешно завершена. Хорошего дня!";
	return 0;
}
