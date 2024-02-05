#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void showvs()
{
	cout << R"(
 ##   ##   #####
 ##   ##  ##   ##
  ## ##   #
  ## ##    #####
   ###         ##
   ###    ##   ##
    #      #####)";
}
struct artifact
{
	char name[100]{};
	int damage;
};
struct player
{
	char name[100];
	int hp;
	artifact sword;
	artifact shield;
	int lvl;
};

artifact shieldgenerator(int lvl)
{
	char first[8][100]{ "Дубо","громо","Мега","ультра","Гипер" };
	char second[8][100]{ "Щит","рог","електрик","китти" };
	int f = rand() % 5;
	int s = rand() % 5;
	artifact result;
	result.damage = rand() % 5 + (lvl * 2);
	int n = strlen(first[f]);
	int n2 = strlen(second[s]);
	for (int i = 0; i < n + n2; i++)
	{
		if (i < n)
			result.name[i] = first[f][i];
		else
			result.name[i] = second[s][i - n];
	}
	return result;
}

artifact swordgenerator(int lvl)
{
	char first[8][100]{ "меч ","дубина ","палица ","копье ","кулак " };
	char second[8][100]{ "ледяной ","огненный ","ветрянный ","водяной " };
	char third[8][100]{ "ядовитый ","сабакины ","лютой ","пяточной ","долмы " };
	int f = rand() % 5;
	int s = rand() % 4;
	int t = rand() % 5;
	artifact result;
	result.damage = rand() % 5 + (lvl * 2);
	int n = strlen(first[f]);
	int n2 = strlen(second[s]);
	int n3 = strlen(third[t]);
	for (int i = 0; i < n + n2 + n3; i++)
	{
		if (i < n)
			result.name[i] = first[f][i];
		else if (i < n2+n)
			result.name[i] = second[s][i - n];
		else
			result.name[i] = third[t][i - n-n2];
	}
	return result;
}

void show_arr(artifact art)
{
	cout << art.name << "\n";
	cout << "УРОН\\БЛОК " << art.damage << "ед.\n";
}

player enemygenerator(int lvl)
{
	player play;
	play.hp = 100;
	play.lvl = rand() % 5; 
	char first[8][100]{ "Деструктор ","Тень ","вдова ","яд ","разрушитель " };
	char second[8][100]{ "Мракошептун","молот","теньокут","змееглаз","мародер" };
	int f = rand() % 5;
	int s = rand() % 5;
	play.shield = shieldgenerator(rand() %15);
	play.sword = swordgenerator(rand() % 20);

	int n = strlen(first[f]);
	int n2 = strlen(second[s]);
	for (int i = 0; i <n+n2; i++)
	{
		if (i < f)
		{
			play.name[i] = first[f][i];
		}
		else
			play.name[i] = second[s][i - f];
	}
	return play;
}

void showplayer(player pl)
{
	cout << "*******************************************"<<endl;
	cout << "\t\t" << pl.name << ' ' << pl.lvl << "урвоень: " << endl;
	cout << "\t\tжизней: " << pl.hp<<endl ;
	cout << "оружие: " << endl;
	show_arr(pl.sword);
	cout << "\nщит: " << endl;
	show_arr(pl.shield);
	cout << "*******************************************" << endl;
}

void fight(player &p1, player &enemy)
{
	while (p1.hp > 0 && enemy.hp > 0)
	{
		int d= p1.sword.damage + p1.lvl + rand() % p1.lvl - enemy.shield.damage;
		if (d < 0)d = 0;
		cout << "удар" << p1.name << "! наносит " << d<<"урона!"<<enemy.name<<" в шоке";
		d = enemy.sword.damage + enemy.lvl + rand() % enemy.lvl - p1.shield.damage;
		if (d < 0)d = 0;
		cout << "удар " << enemy.name << " наносит " << d << "урона! " << p1.name << " заплакал";
		p1.hp -= d;
		if (p1.hp <= 0)
			cout << "вы лузер" << endl;
		else
		{
			cout << "урааа победа, что делаем?";
			cout << "1.забрать щит"<< endl;
			cout << "2.забрать меч" << endl;
			cout << "3.идти дальше" << endl;
			int x;
			cin >> x;
			if (x == 1)
			{
				p1.shield = enemy.shield;
			}
			if (x == 2)
			{
				p1.sword = enemy.sword;
			}
		}
	}
	system("pause");
	system("cls");
}


void ReadFile(player &Hero)
{
	ifstream fin("D:\\вася\\dadad.txt");
	while (!fin.eof())
	{
		char h[1000];
		fin.getline(h, 1000);
		if (h[0] == '!' && h[1] == 'f' && h[2] == 'i' && h[3] == 'g' && h[4] == 'h' && h[5] == 't')
		{
			int lvl;
			fin >> lvl;
			player enemy = enemygenerator(lvl);
			fight(Hero, enemy);
		}
		else
		{
			cout << h;
		}
	}
}

int main()
{
	showvs();
	srand(time(0));
	system("chcp 1251");
	system("cls");
	player p;
	p.hp = 50;
	p.lvl = 1;
	p.shield = { "пусто-",0 };
	p.sword = { "-пусто-",2 };
	cout << "Добрый день, путник, назови себя!" << endl;
	cin.getline(p.name, 100);
	cout << "После того как проклятый культ начал распространять свою зловещую власть по стране, вашему персонажу предстоит отправиться в опасное путешествие через запретные земли, чтобы найти древние артефакты и собрать армию сторонников света. Во время путешествия он сталкивается с могущественными врагами, проходит через испытания и раскрывает тайны, скрытые веками. В конце концов, ваш персонаж должен сразиться с вождем культа в эпической финальной битве на краю мира, где судьба всего человечества висит на волоске.Процветание или погибель — все зависит от исхода этой древней битвы.";
	cout << "1.выпить энергетика"; 
	cout << "2.поспать еще";
	int x = 0;
	cin >> x;
	if (x == 1)
	{
		cout << "выпив энергетика, вам стало еще хуже! -10hp";
		p.hp -= 10;
		p.sword = { "бутылка", 5 };
	}
	if (x == 2)
	{
		cout << "поспав еще, ты пройдещь дальше1";
		p.sword = { "подушка",2 };
	}
	cout << "о ужас на тебя напал таракан" << endl;
	player pl2 = enemygenerator(1);
	strcpy(pl2.name, "таракан");
	showplayer(p);
	showvs();
	showplayer(pl2);
	fight(p, pl2);
	ReadFile(p);
}