#include <iostream>
#include <string>
#include <list>
#include <cstdio>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

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
	int curLife = 100;

	int skill()
	{
		cout << "你使出两剑归宗" << endl;
		return attack * 2;
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
	Zombie()
	{
		name = "丧尸";
		job = "普通怪";
		sex = "男";
		age = 23;
		money = 50;
		life = 50;
		attack = 8;
		defend = 5;
		curLife = 50;
	}

	int skill()
	{
		cout << name << "对你扑咬" << endl;
		return attack * 1.5;
	}
};

struct NagaQueue : Ghost
{
	NagaQueue()
	{
		name = "蛇妖";
		job = "精英怪";
		sex = "女";
		age = 800;
		money = 10000;
		life = 10000;
		attack = 388;
		defend = 100;
		curLife = 388;
	}

	int skill()
	{
		cout << name << "朝你娇媚一笑，似乎暗藏玄机" << endl;
		return attack * 2;
	}
};

struct NashBaron : Ghost
{
	NashBaron()
	{
		name = "纳什男爵";
		job = "Boss";
		sex = "男";
		age = 10000;
		money = 100 * 10000;
		life = 100 * 10000;
		attack = 999;
		defend = 999;
		curLife = 100 * 10000;
	}

	int skill()
	{
		cout << name << "发出怒吼，吐出龙息" << endl;
		return attack * 2;
	}
};


static char key = '0';
static Hero hero;

void startGame();
void endGame();
void archiveGame();
void setColor(int n);
void restoreColor();
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
void fight(Ghost *ghost);
void fightInfo(Ghost *ghost);
void heroFightRound(Ghost *ghost);
void ghostFightRound(Ghost *ghost);
void endFight(Ghost *ghost);


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
	setColor(43);
	setColor(31);
	cout << str << endl;
	restoreColor();

	exit(0);
}

void archiveGame()
{

}

#ifdef __linux
void setColor(int n)
{
	cout << "\033[" + to_string(n) + "m";
}

void restoreColor()
{
	cout << "\033[39m";
	cout << "\033[49m";
}
#endif // __linux
#ifdef _WIN32
void setColor(int n)
{
	WORD attr;
	if (n == 31) attr = FOREGROUND_RED;
	else if (n == 34) attr = FOREGROUND_BLUE;
	else if (n > 30 && n < 39) attr = FOREGROUND_GREEN;
	else if (n == 41) attr = BACKGROUND_RED;
	else if (n == 42) attr = BACKGROUND_GREEN;
	else if (n > 40 && n < 49) attr = BACKGROUND_BLUE;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}

void restoreColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}
#endif // _WIN32

void tellStory()
{
	string story = "很久很久以前，华夏大地遍布妖魔鬼怪，它们侵蚀着人类的地盘。\n"
		"为了谋得一丝存活空间，英雄们站了出来，纷纷成立正道门派，以对抗妖魔！\n"
		"这些门派中，有一个小门派名为伏魔派，以降妖伏魔为己任，虽力量弱小，却义无反顾。\n"
		"我们故事的主角，便是你——" + hero.name + "，来自伏魔派的入门弟子。\n"
		"如今天下大乱，是时候出发了……";
	setColor(44);
	setColor(32);
	cout << story << endl;
	restoreColor();
}

void up()
{
	setColor(34);
	cout << "按`0`键返回上一级" << endl;
	restoreColor();
	cin >> key;
}

void chooseMainAction()
{
	string act = "1.打怪升级刷装备\n"
		"2.购买道具\n"
		"3.角色信息\n"
		"按`Q`键退出游戏\n";
	setColor(32);
	cout << endl << act << endl;
	restoreColor();

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
	setColor(32);
	cout << info << endl;
	restoreColor();

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
	setColor(32);
	cout << endl << str << endl;
	restoreColor();

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
	else if (key == '7') changeValue(CurLife, 50);
	else if (key == '8') changeValue(Life, 100);

	// You can purchase again
	purchaseTool();
}

void vanquishGhost()
{
	string info = "1.丧尸\n"
		"2.蛇妖\n"
		"3.纳什男爵";
	setColor(31);
	cout << info << endl;
	restoreColor();

	up();
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
		price = 10000 * 10000;
		name = "干将莫邪";
		break;
	case 4:
		price = 10000 * 10000;
		name = "屠龙宝刀";
		break;
	case 5:
		price = 10;
		name = "布衣";
		break;
	case 6:
		price = 88 * 100;
		name = "锁子甲";
		break;
	case 7:
		price = 5;
		name = "白开水";
		break;
	case 8:
		price = 100 * 10000;
		name = "天山雪莲";
		break;
	case 9:
		price = 1000 * 10000;
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
		setColor(33);
		cout << info << endl;
		restoreColor();
		return false;
	}
	else
	{
		setColor(32);
		info = "购买成功，获得" + name;
		restoreColor();
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

	setColor(35);
	cout << info << endl;
	*value += n;
	cout << "你的" + valueName + "由" << to_string(*value - n) << "变为了" << to_string(*value) << endl;
	restoreColor();
}

void fightZombie()
{
	string info = "站在你面前的是一只样貌丑陋的丧尸，它嘴里流着恶心的液体，扭曲着四肢，顶着碎掉一半的脑子向你扑了过来……";
	setColor(34);
	cout << endl << info << endl;
	restoreColor();

	Zombie zombie;
	fight(&zombie);
}

void fightNagaQueue()
{
	string info = "你看向那妖艳的蛇发女子，不由地怔住了……";
	setColor(35);
	cout << endl << info << endl;
	restoreColor();

	NagaQueue nagaQueue;
	fight(&nagaQueue);
}

void fightNashBaron()
{
	string info = "峡谷传来一声怒吼，整个地面都开始颤动起来，一头巨龙高昂起头颅，口吐龙息，声势滔天。你定了定神，握紧手中长剑，踏步向前……";
	setColor(31);
	cout << endl << info << endl;
	restoreColor();

	NashBaron nashBaron;
	fight(&nashBaron);
}

void fight(Ghost *ghost)
{
	while (hero.curLife > 0 && ghost->curLife > 0)
	{
		// Hero's fight round
		fightInfo(ghost);
		heroFightRound(ghost);

		if (hero.curLife <= 0 || ghost->curLife <= 0) break;
		// Ghost's fight round
		fightInfo(ghost);
		ghostFightRound(ghost);
	}

	// End fight
	endFight(ghost);
}

void fightInfo(Ghost *ghost)
{
	string info = "战斗信息：\n"
		+ ghost->name + "(" + to_string(ghost->curLife) + "/" + to_string(ghost->life) + ")\n"
		+ hero.name + "(" + to_string(hero.curLife) + "/" + to_string(hero.life) + ")\n"
		"-------------------------";
	setColor(46);
	setColor(33);
	cout << endl << info << endl;
	restoreColor();
}

void heroFightRound(Ghost *ghost)
{
	setColor(36);
	cout << "你的回合……" << endl;
	string str = "1.普通攻击（默認） 2.技能 3.逃跑";
	setColor(33);
	cout << str << endl;
	restoreColor();

	cin >> key;
	if (key == '2')
	{
		int n = hero.skill();
		int damage = (n - ghost->defend < 1 ? 1 : n - ghost->defend);
		setColor(31);
		cout << "对" << ghost->name << "造成了" << damage << "点伤害" << endl;
		restoreColor();
		ghost->curLife -= damage;
	}
	// No use now
	else if (key == '3')
	{
		setColor(31);
		cout << "逃跑失败！" << endl;
		restoreColor();
	}
	else
	{
		int n = hero.attack;
		int damage = (n - ghost->defend < 1 ? 1 : n - ghost->defend);
		setColor(31);
		cout << "你使出普通攻击，对" << ghost->name << "造成了" << damage << "点伤害" << endl;
		restoreColor();
		ghost->curLife -= damage;
	}
}

void ghostFightRound(Ghost *ghost)
{
	setColor(36);
	cout << ghost->name << "的回合……" << endl;
	int n = ghost->skill();
	int damage = (n - hero.defend < 1 ? 1 : n - hero.defend);
	setColor(31);
	cout << ghost->name << "对你" << "造成了" << damage << "点伤害" << endl;
	restoreColor();
	hero.curLife -= damage;
}

void endFight(Ghost *ghost)
{
	if (ghost->curLife <= 0)
	{
		setColor(32);
		cout << "战斗胜利！你击败了" << ghost->name << "，获得了" << ghost->money << "个铜币" << endl;
		restoreColor();
		hero.money += ghost->money;
		return;
	}

	// If you die, then end the game
	if (hero.curLife <= 0)
	{
		setColor(31);
		cout << "惜败！你被" << ghost->name << "杀死了！" << endl;
		restoreColor();
		endGame();
	}
}


