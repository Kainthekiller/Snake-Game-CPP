#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
// Setup Draw Input Logic 
#pragma region Methods
// X = Width // Y = Height
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100];
int tailY[100];
int nTail; // Length of the tail
enum class eDriection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDriection direction;

void Setup() 
{
	gameOver = false;
	direction = eDriection::STOP;
	x = width / 2; // Went to start in the center of the map
	y = height / 2;
	fruitX = rand() % width; //Returns Range of  0 - 19
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls"); // Clears the screen
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";  // Top Side
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#"; // Right Side
				
			}
			if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				
				}
				if (!print)
				{
					cout << " ";
				}
			
			}
			
			if (j == width - 1)
			{
				cout << "#"; // Left Side
			}
			
		}
		cout << endl;
	}
	
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";   // Bottom Side
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input()
{
	if (_kbhit()) // If Keyboard is Hit
	{
		switch (_getch())
		{
		case 'a':
			direction = eDriection::LEFT;		
			break;
		case 'd':
			direction = eDriection::RIGHT;
			break;
		case 'w':
			direction = eDriection::UP;
			break;
		case 's':
			direction = eDriection::DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}

	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (direction)
	{
	case eDriection::LEFT:
		x--;
		break;
	case eDriection::RIGHT:
		x++;
		break;
	case eDriection::UP:
		y--;
		break;
	case eDriection::DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)  // OUT OF BOUNDS LOGIC 
	{
		gameOver = true;
	}
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y) // If you hit your self you die.
		{
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY)  // Score Logic Grab the fruit
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++; //Increase Length By 1
	}
}




#pragma endregion

int main()
{
	Setup();


	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(200);
	}


	return 0;
}