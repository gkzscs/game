#include <iostream>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
using namespace std;


typedef struct Point
{
	int row;
	int col;

	Point() { row = 0; col = 0; }

	Point(int r, int c) 
	{
		row = r;
		col = c;
	}
} Map;


static Map map;
static Point point;
static char **arr;


void setColor(int n);
void restoreColor();
void startGame();
void endGame();
void tellStory();
void initMap();
void playerRound(int n);
bool isValidRowCol(const Map &m);
bool isValid(const Point &p);
bool win(int n);
void showBoard();


int main()
{
	startGame();
}

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
#endif	// WIN32
#ifdef __linux
void setColor(int n)
{
	cout << "\033[" << to_string(n) + "m";
}
	
void restoreColor()
{
	cout << "\033[39m";
	cout << "\033[49m";
}
#endif	// __linux

void startGame()
{
	string info = "五子棋游戲開始！";
	setColor(31);
	cout << info << endl;
	restoreColor();
	
	// Tell story
	tellStory();

	// Initialize the map by player
	initMap();

	// Play round, use a loop to control the game
	for (int i = 0; i < 10000; ++i)
	{
		playerRound(i%2+1);
	}
}

void endGame()
{
	string info = "勝負已分，游戲結束！";
	setColor(31);
	cout << endl << info << endl;
	restoreColor();

	// Exit the process
	exit(0);
}

void tellStory()
{
	string story = "滾滾長江東逝水，浪花淘儘英雄。是非成敗轉頭空，青山依舊在，幾度夕陽紅。\n"
		"一代五子棋天才少年——江流兒，欲與棋聖林心誠一決高下！今天就是他倆的決鬥之日……";
	setColor(32);
	cout << story << endl << endl;
	restoreColor();
}

void initMap()
{
	// Initialize the map by player
	setColor(34);
	cout << "初始化地圖，請輸入網格地圖行列數……" << endl;

	setColor(31);
	do 
	{
		cout << "網格地圖行數：";
		cin >> map.row;
		cout << "網格地圖列數：";
		cin >> map.col;
	} while (!isValidRowCol(map));

	// Create board, assign to array
	arr = new char*[map.row];
	for (int i = 0; i < map.row; ++i)
	{
		arr[i] = new char[map.col];
		for (int j = 0; j < map.col; ++j)
		{
			arr[i][j] = '-';
		}
	}

	setColor(31);
	cout << "各位棋手，地圖初始化已完成，游戲正式啓動！" << endl;
	restoreColor();

	// Show the chess board
	showBoard();
}

void playerRound(int n)
{
	string info = "輪到棋手" + to_string(n) + "的回合！";
	setColor(31);
	cout << info << endl;

	// Input the position of chess
	setColor(32);
	do 
	{
		cout << "請決定棋子放置位置……" << endl;
		cout << "行：";
		cin >> point.row;
		cout << "列：";
		cin >> point.col;
	} while (!isValid(point));
	restoreColor();

	// Set chess
	arr[point.row-1][point.col-1] = (n == 1 ? 'X' : 'O');

	// Judge win
	bool res = win(n);
	if (res)
	{
		setColor(31);
		cout << "恭喜棋手" << to_string(n) << "取得了本局勝利！" << endl;
		restoreColor();

		showBoard();
		endGame();
	}

	// Show the board
	showBoard();
}

bool isValidRowCol(const Map &m)
{
	if (m.row > 0 && m.col > 0 && m.row < 100 && m.col < 100) return true;
	return false;
}

bool isValid(const Point &p)
{
	int r = p.row-1, c = p.col-1;

	if (r < 0 || c < 0 || r >= map.row || c >= map.col) 
	{
		setColor(31);
		cout << "不可在此位置擺放棋子，請再三考慮!" << endl;
		restoreColor();
		return false;
	}

	if (arr[r][c] == '-') return true;
	else 
	{
		setColor(31);
		cout << "不可在此位置擺放棋子，請再三考慮!" << endl;
		restoreColor();
	}

	return false;
}

bool win(int n)
{
#define CLEAR	\
	count = 0;	\
	last = tmp = '-';

#define JUDGE	\
	{	\
	tmp = arr[i][j];	\
	if (tmp == '-' || last != tmp) count = 0;	\
	last = tmp;	\
	++count;	\
	if (count >= 5) return true;	\
	}

	int count = 0;
	char last = '-';
	char tmp = '-';

	for (int i = 0; i < map.row; ++i)
	{
		CLEAR
		for (int j = 0; j < map.col; ++j) JUDGE
	}

	for (int i = -1; i < map.row; ++i)
	{
		CLEAR
		int j = -1;
		while (++j < map.col && ++i < map.row) JUDGE
	}

	for (int j = 0; j < map.col; ++j)
	{
		CLEAR
		for (int i = 0; i < map.row; ++i) JUDGE
	}

	for (int j = -1; j < map.col; ++j)
	{
		CLEAR
		int i = -1;
		while (++i < map.row && ++j < map.col) JUDGE
	}

	return false;
#undef CLEAR
#undef JUDGE
}

void showBoard()
{
	string info = "當前棋盤格局為：";
	setColor(34);
	cout << endl << info << endl;
	
	// Show chess board
	setColor(32);
	for (int i = 0; i < map.row; ++i)
	{
		for (int j = 0; j < map.col; ++j)
		{
			cout << " " << arr[i][j];
		}
		cout << endl;
	}
	restoreColor();
}
