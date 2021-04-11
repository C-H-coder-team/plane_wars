#pragma once
#ifndef PLANE_FUNCATION_H 
#define PLANE_FUNCATION_H 
#include"stdc++.h"
#include"game_struct.h"
void SetPos(COORD a)// set cursor   
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}

void SetPos(int i, int j)// set cursor  
{
	COORD pos = { i, j };
	SetPos(pos);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//把第y行，[x1, x2) 之间的坐标填充为 ch  
void drawRow(int y, int x1, int x2, char ch)
{
	SetPos(x1, y);
	for (int i = 0; i <= (x2 - x1); i++)
		cout << ch;
}

//在a, b 纵坐标相同的前提下，把坐标 [a, b] 之间填充为 ch  
void drawRow(COORD a, COORD b, char ch)
{
	if (a.Y == b.Y)
		drawRow(a.Y, a.X, b.X, ch);
	else
	{
		SetPos(0, 25);
		cout << "error code 01：无法填充行，因为两个坐标的纵坐标(x)不相等";
		system("pause");
	}
}

//把第x列，[y1, y2] 之间的坐标填充为 ch  
void drawCol(int x, int y1, int y2, char ch)
{
	int y = y1;
	while (y != y2 + 1)
	{
		SetPos(x, y);
		cout << ch;
		y++;
	}
}

//在a, b 横坐标相同的前提下，把坐标 [a, b] 之间填充为 ch  
void drawCol(COORD a, COORD b, char ch)
{
	if (a.X == b.X)
		drawCol(a.X, a.Y, b.Y, ch);
	else
	{
		SetPos(0, 25);
		cout << "error code 02：无法填充列，因为两个坐标的横坐标(y)不相等";
		system("pause");
	}
}

//左上角坐标、右下角坐标、用row填充行、用col填充列  
void drawFrame(COORD a, COORD  b, char row, char col)
{
	drawRow(a.Y, a.X + 1, b.X - 1, row);
	drawRow(b.Y, a.X + 1, b.X - 1, row);
	drawCol(a.X, a.Y + 1, b.Y - 1, col);
	drawCol(b.X, a.Y + 1, b.Y - 1, col);
}

void drawFrame(int x1, int y1, int x2, int y2, char row, char col)
{
	COORD a = { x1, y1 };
	COORD b = { x2, y2 };
	drawFrame(a, b, row, col);
}

void drawFrame(Frame frame, char row, char col)
{
	COORD a = frame.position[0];
	COORD b = frame.position[1];
	drawFrame(a, b, row, col);
}

void drawPlaying()
{
	drawFrame(0, 0, 48, 24, '=', '|');//    draw map frame;  
	drawFrame(49, 0, 79, 4, '-', '|');//        draw output frame  
	drawFrame(49, 4, 79, 9, '-', '|');//        draw score frame  
	drawFrame(49, 9, 79, 20, '-', '|');//   draw operate frame  
	drawFrame(49, 20, 79, 24, '-', '|');//  draw other message frame  
	SetPos(52, 6);
	cout << "得分：";
	SetPos(52, 7);
	cout << "称号：";
	SetPos(52, 10);
	cout << "操作方式：";
	SetPos(52, 12);
	cout << "  a,s,d,w 控制战机移动。";
	SetPos(52, 14);
	cout << "  p 暂停游戏。";
	SetPos(52, 16);
	cout << "  e 退出游戏。";
}

//在[a, b)之间产生一个随机整数  
int random(int a, int b)
{
	int c = (rand() % (a - b)) + a;
	return c;
}

//在两个坐标包括的矩形框内随机产生一个坐标  
COORD random(COORD a, COORD b)
{
	int x = random(a.X, b.X);
	int y = random(a.Y, b.Y);
	COORD c = { x, y };
	return c;
}

bool  judgeCoordInFrame(Frame frame, COORD spot)
{
	if (spot.X >= frame.position[0].X)
		if (spot.X <= frame.position[1].X)
			if (spot.Y >= frame.position[0].Y)
				if (spot.Y <= frame.position[0].Y)
					return true;
	return false;
}

void printCoord(COORD a)
{
	cout << "( " << a.X << " , " << a.Y << " )";
}

void printFrameCoord(Frame a)
{
	printCoord(a.position[0]);
	cout << " - ";
	printCoord(a.position[1]);
}

int drawMenu()
{
	SetPos(30, 1);
	cout << "P l a n e  W a r";
	drawRow(3, 0, 79, '-');
	drawRow(5, 0, 79, '-');
	SetPos(28, 4);
	cout << "w 和 s 选择， k 确定";
	SetPos(15, 11);
	cout << "1. 简单的敌人";
	SetPos(15, 13);
	cout << "2. 冷酷的敌人";
	drawRow(20, 0, 79, '-');
	drawRow(22, 0, 79, '-');
	SetPos(47, 11);
	cout << "简单的敌人：";
	SetPos(51, 13);
	cout << "简单敌人有着较慢的移动速度。";
	SetPos(24, 21);
	cout << "制作：fanjun";
	int j = 11;
	SetPos(12, j);
	cout << ">>";

	//drawFrame(45, 9, 79, 17, '=', '|');  

	while (1)
	{
		if (_kbhit())
		{
			char x = _getch();
			switch (x)
			{
			case 'w':
			{
				if (j == 13)
				{
					SetPos(12, j);
					cout << "　";
					j = 11;
					SetPos(12, j);
					cout << ">>";
					SetPos(51, 13);
					cout << "　　　　　　　　　　　　";
					SetPos(47, 11);
					cout << "简单的敌人：";
					SetPos(51, 13);
					cout << "简单敌人有着较慢的移动速度，比较容易对付";
				}
				break;
			}
			case 's':
			{
				if (j == 11)
				{
					SetPos(12, j);
					cout << "　";
					j = 13;
					SetPos(12, j);
					cout << ">>";
					SetPos(51, 13);
					cout << "　　　　　　　　　　　　　　";
					SetPos(47, 11);
					cout << "冷酷的敌人：";
					SetPos(51, 13);
					cout << "冷酷的敌人移动速度较快，难对付哟。";
				}
				break;
			}
			case 'k':
			{
				if (j == 8) return 1;
				else return 2;
			}
			}
		}
	}
}


#endif