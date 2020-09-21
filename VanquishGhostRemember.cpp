#include <iostream>
#include <string>
#include <list>
using namespace std;


struct Hero
{
	string name = "伏零";
	string job = "伏魔师";
	string sex = "男";
	int age = 16;
	int life = 100;
	int attack = 10;
	int defend = 10;
	int curLife = 10;
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
	cout << str << endl;

	// Tip how to choose
	up();
	while (!(key >= '0' && key <= '9'))
	{
		purchaseTool();
	}

	// Deal with choose
	if (key == '0') return;
	else if (key == '1') ;
	else if (key == '2') ;
}

void vanquishGhost()
{

}
