#include <iostream>
#include <list>
using namespace std;


typedef struct Node
{
	int x;
	int y;

	Node() { x = 0; y = 0; }
	Node(int a, int b) { x = a; y = b; }
} Point;

struct Map
{
	int row;
	int col;
};

struct Snake
{
	int length;
	int direction;
	list<Node *> body;
};


static Snake snake;
static Point p;
static Map map;


void initMap();
void startGame();
void endGame();
void tellStory();
void updateMap();
void drawBoarder();
void drawFood();
void drawSnake();

int main()
{
	startGame();
}

void initMap()
{
	string info = "";
	cout << info << endl;

	// Enter row and col
	cout << "";
	cin >> map.row;
	cout << "";
	cin >> map.col;

	// Create map
	updateMap();
}

void startGame()
{
	// Tell story
	string info = "";
	cout << info << endl;

	// Initialize map
	initMap();

	// Start play

}

void endGame()
{
	string info = "";
	cout <<info << endl;

	// Exit the process
	exit(0);
}

void tellStory()
{
	string story = "";
	cout << story << endl;
}

void updateMap()
{
	drawBoarder();
	drawFood();
	drawSnake();
}

void drawBoarder()
{
	// Save cursor
	cout << "\033[s";

	for (int i = 0; i < map.col; ++i) cout << "▁";
	cout << "\033[" << map.row << "B\033[" << map.col << "D";
	for (int i = 0; i < map.col; ++i) cout << "▔";
	for (int i = 0; i < map.row-1; ++i) cout << "\033[1D\033[1A" << "█";
	cout << "\033[" << map.col-1 << "D\033[1A";
	for (int i = 0; i < map.row-1; ++i) cout << "\033[1D\033[1B" << "█";
	cout << endl << endl;

	// Restore cursor
	//cout << "\033[u";
}

void drawSnake()
{

}

void drawFood()
{

}


