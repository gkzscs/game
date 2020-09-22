#include <iostream>
#include <string>
#include <list>
#include <cstdio>
using namespace std;


enum ValueType
{
	Attack,
	Defend,
	Life,
	CurLife,
	Money
};

struct Hero
{
	string name = "伏零";
	string job = "伏魔师";
	string sex = "男";
	int age = 16;
	int money = 100;
	int life = 100;
	int attack = 10;
	int defend = 10;
	int curLife = 10;

	int skill() 
	{
		cout << "你使出两剑归宗" << endl;
		return attack*2;
	}
};

struct Ghost
{
	string name;
	string job;
	string sex;
	int age;
	int money;
	int life;
	int attack;
	int defend;
	int curLife;
	virtual int skill() { return 0; }
};

struct Zombie : Ghost
{
	string name = "丧尸";
	string job = "普通怪";
	string sex = "男";
	int age = 23;
	int money = 50;
	int life = 50;
	int attack = 8;
	int defend = 5;
	int curLife = 50;	
	
	int skill() 
	{
		cout << name << "对你扑咬" << endl;
		return attack*1.5;
	}
};

struct NagaQueue : Ghost
{
	string name = "蛇妖";
	string job = "精英怪";
	string sex = "女";
	int age = 800;
	int money = 10000;
	int life = 10000;
	int attack = 388;
	int defend = 100;
	int curLife = 388;
	
	int skill() 
	{
		cout << name << "朝你娇媚一笑，似乎暗藏玄机" << endl;
		return attack*2;
	}
};

struct NashBaron : Ghost
{
	string name = "纳什男爵";
	string job = "Boss";
	string sex = "男";
	int age = 10000;
	int money = 100*10000;
	int life = 100*10000;
	int attack = 999;
	int defend = 999;
	int curLife = 100*10000;
	
	int skill() 
	{
		cout << name << "发出怒吼，吐出龙息" << endl;
		return attack*2;
	}
};


static char key = '0';
static Hero hero;

void startGame();
void endGame();
void archiveGame();
void tellStory();
void up();
void chooseMainAction();
void purchaseTool();
void vanquishGhost();
void heroInfo();
bool checkPurchase(int n);
void changeValue(ValueType type, int n);
void fightZombie();
void fightNagaQueue();
void fightNashBaron();
void fight(Ghost &ghost);
void fightInfo(Ghost &ghost);
void heroFightRound(Ghost &ghost);
void ghostFightRound(Ghost &ghost);
void endFight(Ghost &ghost);


int main()
{
	startGame();

	return 0;
}

void startGame()
{
	// 游戏背景讲述
	tellStory();

	// 游戏主线
	while (key != 'q')
	{
		chooseMainAction();
	}
}

void endGame()
{
	key = 'q';
	string str = "胜败乃兵家常事，少侠请重新来过！";
	cout << str << endl;
}

void archiveGame()
{

}

void tellStory()
{
	string story = "很久很久以前，华夏大地遍布妖魔鬼怪，它们侵蚀着人类的地盘。\n"
		"为了谋得一丝存活空间，英雄们站了出来，纷纷成立正道门派，以对抗妖魔！\n"
		"这些门派中，有一个小门派名为伏魔派，以降妖伏魔为己任，虽力量弱小，却义无反顾。\n"
		"我们故事的主角，便是你——" + hero.name + "，来自伏魔派的入门弟子。\n"
		"如今天下大乱，是时候出发了……";
	cout << story << endl;
}

void up()
{
	cout << "按`0`键返回上一级" << endl;
	cin >> key;
}

void chooseMainAction()
{
	string act = "1.打怪升级刷装备\n"
		"2.购买道具\n"
		"3.角色信息\n"
		"按`Q`键退出游戏\n";
	cout << act << endl;

	cin >> key;
	if (key == 'q' || key == 'Q') endGame();
	else if (key == '1') vanquishGhost();
	else if (key == '2') purchaseTool();
	else if (key == '3') heroInfo();
}

void heroInfo()
{
	string info = "名称：" + hero.name + "\n"
		"职业：" + hero.job + "\n"
		"性别：" + hero.sex + "\n"
		"年龄：" + to_string(hero.age) + "\n"
		"金钱：" + to_string(hero.money) + "\n"
		"生命值：" + to_string(hero.curLife) + "/" + to_string(hero.life) + "\n"
		"攻击力：" + to_string(hero.attack) + "\n"
		"防御力：" + to_string(hero.defend);
	cout << info << endl;

	up();
	while (key != '0') cin >> key;
}

void purchaseTool()
{
	string str = "1.木剑（攻击力+10） - 10铜币\n"
		"2.铜剑（攻击力+30） - 30铜币\n"
		"3.干将莫邪（攻击力+999） - 10000金币\n"
		"4.屠龙宝刀（攻击力+1333，防御力-300） - 10000金币\n"
		"5.布衣（防御力+10） - 10铜币\n"
		"6.锁子甲（防御力+50） - 88银币\n"
		"7.白开水（可回复50点生命值）- 5铜币\n"
		"8.天山雪莲（提高生命上限100点） - 100金币\n"
		"9.复活十字架（战斗死亡后，可自动重生一次） - 1000金币";
	cout << endl << str << endl;

	// Tip how to choose
	up();
	while (!(key >= '0' && key <= '9'))
	{
		purchaseTool();
	}

	// Deal with choose
	if (key == '0') return;
	bool res = checkPurchase(key - '0');
	if (!res) 
	{
		purchaseTool();
		return;
	}

	if (key == '1') changeValue(Attack, 10);
	else if (key == '2') changeValue(Attack, 30);
	else if (key == '3') changeValue(Attack, 999);
	else if (key == '4') 
	{
		changeValue(Attack, 1333);
		changeValue(Defend, -300);
	}
	else if (key == '5') changeValue(Defend, 10);
	else if (key == '6') changeValue(Defend, 50);

	// You can purchase again
	purchaseTool();
}

void vanquishGhost()
{
	string info = "1.丧尸\n"
		"2.蛇妖\n"
		"3.纳什男爵";
	cout << info << endl;
	up();

	cin >> key;
	while (key != '0')
	{
		if (key == '1') fightZombie();
		else if (key == '2') fightNagaQueue();
		else if (key == '3') fightNashBaron();
		else cout << "未找到怪物" << endl;

		// You can fight again
		vanquishGhost();
	}
}

bool checkPurchase(int n)
{
	int price = 0;
	string name = "";

	switch (n)
	{
	case 1:
		price = 10;
		name = "木剑";
		break;
	case 2:
		price = 30;
		name = "铜剑";
		break;
	case 3:
		price = 10000*10000;
		name = "干将莫邪";
		break;
	case 4:
		price = 10000*10000;
		name = "屠龙宝刀";
		break;
	case 5:
		price = 10;
		name = "布衣";
		break;
	case 6:
		price = 88*100;
		name = "锁子甲";
		break;
	case 7:
		price = 5;
		name = "白开水";
		break;
	case 8:
		price = 100*10000;
		name = "天山雪莲";
		break;
	case 9:
		price = 1000*10000;
		name = "复活十字架";
		break;
	default:
		break;
	}

	// Check the price with your money
	string info;
	if (price > hero.money) 
	{
		info = "金币不够，购买失败！";
		cout << info << endl;
		return false;
	}
	else 
	{
		info = "购买成功，获得" + name;
	}
	cout << info << endl;

	// Change gold
	changeValue(Money, -price);
	return true;
}

void changeValue(ValueType type, int n)
{
	string info;
	string valueName = "";
	int *value = nullptr;

	switch (type)
	{
	case Attack:
		valueName = "攻击力";
		value = &hero.attack;
		break;
	case Defend:
		valueName = "防御力";
		value = &hero.defend;
		break;
	case Life:
		valueName = "生命上限";
		value = &hero.life;
		break;
	case CurLife:
		valueName = "当前生命值";
		value = &hero.curLife;
		break;
	case Money:
		valueName = "金钱数量";
		value = &hero.money;
		break;
	default:
		cout << "发现奇奇怪怪的东东" << endl;
		return;
	}
	
	if (n > 0) info = valueName + "+" + to_string(n);
	else if (n == 0) info = valueName + "不变";
	else if (n < 0) info = valueName + "-" + to_string(n);

	cout << info << endl;
	*value += n;
	cout << "你的" + valueName + "由" << to_string(*value-n) << "变为了" << to_string(*value) << endl;
}

void fightZombie()
{
	string info = "站在你面前的是一只样貌丑陋的丧尸，它嘴里流着恶心的液体，扭曲着四肢，顶着碎掉一半的脑子向你扑了过来……";
	cout << endl << info << endl;

	Zombie zombie;
	fight(zombie);
}

void fightNagaQueue()
{

}

void fightNashBaron()
{

}

void fight(Ghost &ghost)
{
	while (hero.curLife > 0 && ghost.curLife > 0)
	{
		// Hero's fight round
		fightInfo(ghost);
		heroFightRound(ghost);

		// Ghost's fight round
		fightInfo(ghost);
		ghostFightRound(ghost);
	}

	// End fight
	endFight(ghost);
}

void fightInfo(Ghost &ghost)
{
	string info = "战斗信息：\n"
		+ ghost.name + "(" + to_string(ghost.curLife) + "/" + to_string(ghost.life) + ")\n"
		+ hero.name + "(" + to_string(hero.curLife) + "/" + to_string(hero.life) + ")\n"
		"-------------------------";
	cout << info << endl;
}

void heroFightRound(Ghost &ghost)
{
	cout << "你的回合……" << endl;
	string str = "1.普通攻击（默認） 2.技能 3.逃跑";

	cin >> key;
	if (key == '2') 
	{
		int n = hero.skill();
		int damage = (n-ghost.defend < 1 ? 1 : n-ghost.defend);
		cout << "对" << ghost.name << "造成了" << damage << "点伤害" << endl;
		ghost.curLife -= damage;
	}
	// No use now
	else if (key == '3')
	{
		cout << "逃跑失败！" << endl;
	}		
	else 
	{
		int n = hero.attack;
		int damage = (n-ghost.defend < 1 ? 1 : n-ghost.defend);
		cout << "对" << ghost.name << "造成了" << damage << "点伤害" << endl;
		ghost.curLife -= damage;
	}
}

void ghostFightRound(Ghost &ghost)
{
	cout << ghost.name << "的回合……" << endl;
	int n = ghost.attack;
	int damage = (n-hero.defend < 1 ? 1 : n-hero.defend);
	cout << ghost.name << "对你" << "造成了" << damage << "点伤害" << endl;
	hero.curLife -= damage;
}

void endFight(Ghost &ghost)
{
	if (ghost.curLife <= 0) 
	{
		cout << "战斗胜利！你击败了" << ghost.name << "，获得了" << ghost.money << "个铜币" << endl;
		hero.money += ghost.money;
		return;
	}

	// If you die, then end the game
	if (hero.curLife <= 0) 
	{
		cout << "惜败！你被" << ghost.name << "杀死了！" << endl;
		endGame();
	}
}


