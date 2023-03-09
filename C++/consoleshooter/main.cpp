#include <iostream>
#include <windows.h>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

class Person;

class Gun {
	public:
		virtual void Shoot(Person *enemy, Person *player, int _shoot) = 0;
};

class Person {
	public:
		int HP = 100;
		int Armour = 100;
		int map_position;
		
		Person(int _pos) {
			map_position = _pos;
		}
		
		void GetHP() {
			cout << "HP = " << HP << ", Armour = " << Armour << "\n";
		}
		
		int GetDamage(int damage) {
			if(Armour > 0) {
				if((Armour - damage) > 0) {
					Armour -= damage;
				}
				
				else {
					HP = HP + Armour - damage;
					Armour = 0;
				}
			}
			
			else if(HP - damage > 0) HP -= damage;
			else if(HP - damage <= 0) HP = 0;
		}
		
		void Fire(Gun *gun, Person *enemy, Person *player, int _shoot) {
			gun -> Shoot(enemy, player, _shoot);
		}
};

class Pistol : public Gun {
	public:
		void Shoot(Person *enemy, Person *player, int _shoot) {
			if(_shoot != 1) {
				enemy -> GetDamage(15);
				cout << "Здоровье противника: ";
				enemy -> GetHP();
			}
			
			if(_shoot == 1) {
				player -> GetDamage(15);
				cout << "Ваше здоровье: ";
				player -> GetHP();
			}
		}
};

class Automat : public Gun {
	public:
		void Shoot(Person *enemy, Person *player, int _shoot) {
			if(_shoot != 1) {
				enemy -> GetDamage(50);
				cout << "Здоровье противника: ";
				enemy -> GetHP();
			}
			
			if(_shoot == 1) {
				player -> GetDamage(50);
				cout << "Ваше здоровье: ";
				player -> GetHP();
			}
		}
};

class Bazooka : public Gun {
	public:
		void Shoot(Person *enemy, Person *player, int _shoot) {
			if(_shoot != 1) {
				if(abs(player -> map_position - enemy -> map_position) < 3) {
					cout << "Вы себя убили взрывом! Завершение боя!\nОставшееся здоровье у противника:\n";
					player -> HP = 0;
					player -> Armour = 0;
					cout << "Здоровье противника: ";
					enemy -> GetHP();
				}
				
				else {
					enemy -> GetDamage(150);
					cout << "Ваше здоровье: ";
					enemy -> GetHP();
				}
			}
			
			if(_shoot == 1) {
				if(abs(enemy -> map_position - player -> map_position) < 3) {
					cout << "Противник себя убил взрывом! Вы победили, завершение боя!\n";
					enemy -> HP = 0;
					enemy -> Armour = 0;
				}
				
				else {
					player -> GetDamage(150);
					cout << "Ваше здоровье: ";
					player -> GetHP();
				}
			}
		}
};

int check_HP(Person *Enemy, Person *Player) {
	if(Enemy -> Armour == 0 && Enemy -> HP == 0) {
		cout << "Противник мертв, вы победили!\n";
		return 1;
	}
	
	if(Player -> Armour == 0 && Player -> HP == 0) {
		cout << "Вы мертвы, бой проигран!\n";
		return 0;
	}
	
	return 2;
}

int main() {
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Person Enemy = Person(rand()%11);
	Person Player = Person(rand()%11);
	string guns[] = {"Автомата", "Пистолета", "Базуки"};
	
	while(true) {
		int enemy_shoot = rand()%5;
		int random_gun_number = rand()%3;
		int HP_flag = check_HP(&Enemy, &Player);
		
		if(HP_flag == 0 || HP_flag == 1) return 0;
		
		if(enemy_shoot == 1) {
			cout << "\nПротивник стреляет в вас из " << guns[random_gun_number] << "\n";
		}
		
		if(enemy_shoot != 1) {
			string answer = "";
			cout << "\nВыстрелить из " << guns[random_gun_number] << "?(y/n) ";
			cin >> answer;
			
			if(answer == "n") {
				cout << "Вы пропускаете выстрел!\n";
				Sleep(250);
				continue;
			}
		}
		
		if(random_gun_number == 0) {
			Automat automat;
			Player.Fire(&automat, &Enemy, &Player, enemy_shoot);
			if(enemy_shoot != 1) continue;
			HP_flag = check_HP(&Enemy, &Player);
			if(HP_flag == 0) return 0;
			if(rand()%5 == 1) {
				cout << "\nВы стреляете в противника в ответ из автомата!\n";
				Player.Fire(&automat, &Enemy, &Player, 0);
			}
		}
		
		else if(random_gun_number == 1) {
			Pistol pistol;
			Player.Fire(&pistol, &Enemy, &Player, enemy_shoot);
			if(enemy_shoot != 1) continue;
			HP_flag = check_HP(&Enemy, &Player);
			if(HP_flag == 0) return 0;
			if(rand()%5 == 1) {
				cout << "\nВы стреляете в противника в ответ из пистолета!\n";
				Player.Fire(&pistol, &Enemy, &Player, 0);
			}
		}
			
		else if(random_gun_number == 2) {
			Bazooka bazooka;
			Player.Fire(&bazooka, &Enemy, &Player, enemy_shoot);
			if(enemy_shoot != 1) continue;
			HP_flag = check_HP(&Enemy, &Player);
			if(HP_flag == 0) return 0;
			if(HP_flag == 1) return 0;
			if(rand()%5 == 1) {
				cout << "\nВы стреляете в противника в ответ из базуки!\n";
				Player.Fire(&bazooka, &Enemy, &Player, 0);
			}
		}
	}
}
