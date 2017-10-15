#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <vector>
using namespace std;

struct Location {
	int x;
	int y;
};


enum SETUP {
	Empty,
	Wall,
	Food,
	Player,
	Taill
};

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

const int rows = 20, cols = 50;
int field[rows][cols] = {};
vector<Location> snakePath;
void Cells(int& cell, const int& complexity, int& playerX, int& playerY, int& foodX, int& foodY) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cell = rand() % complexity;
			if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
			{
				field[i][j] = Wall;
			}
			else if (cell == 0)
			{
				field[i][j] = Empty;
			}
			else if (cell == 1)
			{
				field[i][j] = Empty;
			}
		}
	}
	field[foodX][foodY] = Food;
	field[playerX][playerY] = Player;
}
void Drawing(int& playerX, int& playerY, int& score) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));
	SetConsoleCursorPosition(h, { 0,0 });
	cout << "Score:" << score << '\n';
	field[playerX][playerY] = Player;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (field[i][j] == Wall)
			{
				SetConsoleTextAttribute(h, 666);
				cout << char(219);
			}
			else if (field[i][j] == Food)
			{
				SetConsoleTextAttribute(h, 12);
				cout << '*';
			}
			else if (field[i][j] == Player)
			{
				SetConsoleTextAttribute(h, 14);
				cout << '@';
			}
			else if (field[i][j] == Taill)
			{
				SetConsoleTextAttribute(h, 10);
				cout << 'x';
			}
			else
			{
				SetConsoleTextAttribute(h, 7);
				cout << " ";
			}
		}
		cout << endl;
	}
}

void Action(int& playerX, int& playerY, int& foodX, int& foodY, Direction& dir, int& score) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (_getch())
	{
	case 'a':
		dir = LEFT;
		break;
	case 'd':
		dir = RIGHT;
		break;
	case 'w':
		dir = UP;
		break;
	case 's':
		dir = DOWN;
		break;
	case 'x':
		exit(0);
		break;
	case 'f':
		foodX = rand() % (19 - 2) + 2;
		foodY = rand() % (19 - 2) + 2;
		field[foodX][foodY] = Food;
		cout << field[foodX][foodY];
		break;

	}
	switch (dir)
	{
	case UP:
		playerX--;
		break;
	case DOWN:
		playerX++;
		break;
	case LEFT:
		playerY--;
		break;
	case RIGHT:
		playerY++;
		break;
	}


	if (field[playerX][playerY] == Food)
	{
		score++;
		foodX = rand() % (19 - 2) + 2;
		foodY = rand() % (19 - 2) + 2;
		field[foodX][foodY] = Food;
		cout << field[foodX][foodY];
	}

	if (field[playerX][playerY] == Wall || field[playerX][playerY] == Taill)
	{
		system("cls");
		for (int gm = 0; gm < 10000; gm++)
		{
			if (gm % 2 == 0)
			{
				SetConsoleTextAttribute(h, 12);
				cout << "GAMEOVER";
			}
			else
			{
				SetConsoleTextAttribute(h, 7);
				cout << "GAMEOVER";
			}
		}
		exit(0);
	}

	if (field[foodX][foodY] == Taill)
	{
		foodX = rand() % (19 - 2) + 2;
		foodY = rand() % (19 - 2) + 2;
		field[foodX][foodY] = Food;
		cout << field[foodX][foodY];
	}
}

void Tail(int& playerX, int& playerY, int& score)
{
	if (field[playerX][playerY] == Player) {
		field[playerX][playerY] = Taill;
		snakePath.push_back(Location{ playerX, playerY });
	}
	Sleep(50);
	cout << "path size: " << snakePath.size() << endl;

	vector<Location>::iterator it;

	if (snakePath.size() > score) {
		vector<Location>::iterator it;
		for (it = snakePath.begin(); it < snakePath.begin() + snakePath.size() - score; it++) {
			field[(*it).x][(*it).y] = Empty;
			cout << "Rm tail at x: " << (*it).x << "; y: " << (*it).y << endl;
		}

		snakePath.erase(snakePath.begin(), snakePath.begin() + snakePath.size() - score);
	}
}


void main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int playerX = 5, playerY = 5;
	int foodX = rand() % (19 - 2) + 2, foodY = rand() % (19 - 2) + 2;
	const int complexity = 5;
	Direction dir = STOP;
	int cell;
	int score = 0;

	char answer[100];

	SetConsoleTextAttribute(h, 1);
	cout << "made by Teymur Sadixov\n";
	cout << "PLAY FULL SCREEN!!!";
	SetConsoleTextAttribute(h, 14);
	cout << "\t\tWelcome to \"TSnake\"!!!\n";
	cout << "\t\tMOVEMET:\n";
	cout << "\t\t  W  [UP]\n";
	cout << "\t\tA + D[LEFT + RIGHT]\n";
	cout << "\t\t  S  [DOWN]\n";
	cout << "\t\tF [RESET FOOD]\n";
	cout << "\t\tX [EXIT]\n";
	SetConsoleTextAttribute(h, 12);
	cout << "\t\tAre you ready?\n";
	cout << "Answer:";
	cin.getline(answer, 100);

	if (answer != "No"|| answer != "no"|| answer != "NO" || answer == "Yes" || answer == "YES" || answer == "yes" )
	{
		system("cls");
		Cells(cell, complexity, playerX, playerY, foodX, foodY);
		while (true)
		{
			Drawing(playerX, playerY, score);
			Tail(playerX, playerY, score);
			Action(playerX, playerY, foodX, foodY, dir, score);
		}
	}
	else
	{
		exit(0);
	}
}
