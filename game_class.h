#pragma once
#ifndef GAME_CLASS_H
#define GAME_CLASS_H
#include"stdc++.h"
#include"game_funcation.h"
#include"game_struct.h"
class Game
{
public:
	COORD position[10];
	COORD bullet[10];
	Frame enemy[8];
	int score;
	int rank;
	int rankf;
	string title;
	int flag_rank;

	Game();

	//初始化所有  
	void initPlane();
	void initBullet();
	void initEnemy();

	//初始化其中一个  
	//void initThisBullet( COORD );  
	//void initThisEnemy( Frame );  

	void planeMove(char);
	void bulletMove();
	void enemyMove();

	//填充所有  
	void drawPlane();
	void drawPlaneToNull();
	void drawBullet();
	void drawBulletToNull();
	void drawEnemy();
	void drawEnemyToNull();

	//填充其中一个  
	void drawThisBulletToNull(COORD);
	void drawThisEnemyToNull(Frame);

	void Pause();
	void Playing();
	void judgePlane();
	void judgeEnemy();

	void Shoot();

	void GameOver();
	void printScore();
};

Game::Game()
{
	initPlane();
	initBullet();
	initEnemy();
	score = 0;
	rank = 25;
	rankf = 0;
	flag_rank = 0;
}

void Game::initPlane()
{
	COORD centren = { 39, 22 };
	position[0].X = position[5].X = position[7].X = position[9].X = centren.X;
	position[1].X = centren.X - 2;
	position[2].X = position[6].X = centren.X - 1;
	position[3].X = position[8].X = centren.X + 1;
	position[4].X = centren.X + 2;
	for (int i = 0; i <= 4; i++)
		position[i].Y = centren.Y;
	for (int i = 6; i <= 8; i++)
		position[i].Y = centren.Y + 1;
	position[5].Y = centren.Y - 1;
	position[9].Y = centren.Y - 2;
}

void Game::drawPlane()
{
	for (int i = 0; i<9; i++)
	{
		SetPos(position[i]);
		if (i != 5)
			cout << "O";
		else if (i == 5)
			cout << "|";
	}
}

void Game::drawPlaneToNull()
{
	for (int i = 0; i<9; i++)
	{
		SetPos(position[i]);
		cout << " ";
	}
}

void Game::initBullet()
{
	for (int i = 0; i<10; i++)
		bullet[i].Y = 30;
}

void Game::drawBullet()
{
	for (int i = 0; i<10; i++)
	{
		if (bullet[i].Y != 30)
		{
			SetPos(bullet[i]);
			cout << "^";
		}
	}
}

void Game::drawBulletToNull()
{
	for (int i = 0; i<10; i++)
		if (bullet[i].Y != 30)
		{
			COORD pos = { bullet[i].X, bullet[i].Y + 1 };
			SetPos(pos);
			cout << " ";
		}
}

void Game::initEnemy()
{
	COORD a = { 1, 1 };
	COORD b = { 45, 15 };
	for (int i = 0; i<8; i++)
	{
		enemy[i].position[0] = random(a, b);
		enemy[i].position[1].X = enemy[i].position[0].X + 3;
		enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
	}
}

void Game::drawEnemy()
{
	for (int i = 0; i<8; i++)
		drawFrame(enemy[i].position[0], enemy[i].position[1], '-', '|');
}

void Game::drawEnemyToNull()
{
	for (int i = 0; i<8; i++)
	{
		drawFrame(enemy[i].position[0], enemy[i].position[1], ' ', ' ');
	}
}

void Game::Pause()
{
	SetPos(61, 2);
	cout << "               ";
	SetPos(61, 2);
	cout << "暂停中...";
	char c = _getch();
	while (c != 'p')
		c = _getch();
	SetPos(61, 2);
	cout << "         ";
}

void Game::planeMove(char x)
{
	if (x == 'a')
		if (position[1].X != 1)
			for (int i = 0; i <= 9; i++)
				position[i].X -= 2;

	if (x == 's')
		if (position[7].Y != 23)
			for (int i = 0; i <= 9; i++)
				position[i].Y += 1;

	if (x == 'd')
		if (position[4].X != 47)
			for (int i = 0; i <= 9; i++)
				position[i].X += 2;

	if (x == 'w')
		if (position[5].Y != 3)
			for (int i = 0; i <= 9; i++)
				position[i].Y -= 1;
}

void Game::bulletMove()
{
	for (int i = 0; i<10; i++)
	{
		if (bullet[i].Y != 30)
		{
			bullet[i].Y -= 1;
			if (bullet[i].Y == 1)
			{
				COORD pos = { bullet[i].X, bullet[i].Y + 1 };
				drawThisBulletToNull(pos);
				bullet[i].Y = 30;
			}

		}
	}
}

void Game::enemyMove()
{
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<2; j++)
			enemy[i].position[j].Y++;

		if (24 == enemy[i].position[1].Y)
		{
			COORD a = { 1, 1 };
			COORD b = { 45, 3 };
			enemy[i].position[0] = random(a, b);
			enemy[i].position[1].X = enemy[i].position[0].X + 3;
			enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
		}
	}
}

void Game::judgePlane()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j<9; j++)
			if (judgeCoordInFrame(enemy[i], position[j]))
			{
				SetPos(62, 1);
				cout << "坠毁";
				drawFrame(enemy[i], '+', '+');
				Sleep(1000);
				GameOver();
				break;
			}
}

void Game::drawThisBulletToNull(COORD c)
{
	SetPos(c);
	cout << " ";
}

void Game::drawThisEnemyToNull(Frame f)
{
	drawFrame(f, ' ', ' ');
}

void Game::judgeEnemy()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 10; j++)
			if (judgeCoordInFrame(enemy[i], bullet[j]))
			{
				score += 5;
				drawThisEnemyToNull(enemy[i]);
				COORD a = { 1, 1 };
				COORD b = { 45, 3 };
				enemy[i].position[0] = random(a, b);
				enemy[i].position[1].X = enemy[i].position[0].X + 3;
				enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
				drawThisBulletToNull(bullet[j]);
				bullet[j].Y = 30;
			}
}

void Game::Shoot()
{
	for (int i = 0; i<10; i++)
		if (bullet[i].Y == 30)
		{
			bullet[i].X = position[5].X;
			bullet[i].Y = position[5].Y - 1;
			break;
		}
}

void Game::printScore()
{
	if (score == 120 && flag_rank == 0)
	{
		rank -= 3;
		flag_rank = 1;
	}

	else if (score == 360 && flag_rank == 1)
	{
		rank -= 5;
		flag_rank = 2;
	}
	else if (score == 480 && flag_rank == 2)
	{
		rank -= 5;
		flag_rank = 3;
	}
	int x = rank / 5;
	SetPos(60, 6);
	cout << score;

	if (rank != rankf)
	{
		SetPos(60, 7);
		if (x == 5)
			title = "初级飞行员";
		else if (x == 4)
			title = "中级飞行员";
		else if (x == 3)
			title = "高级飞行员";
		else if (x == 2)
			title = "王牌飞行员";
		cout << title;
	}
	rankf = rank;
}

void Game::Playing()
{
	//HANDLE MFUN;  
	//MFUN= CreateThread(NULL, 0, MusicFun, NULL, 0, NULL);   

	drawEnemy();
	drawPlane();

	int flag_bullet = 0;
	int flag_enemy = 0;

	while (1)
	{
		Sleep(8);
		if (_kbhit())
		{
			char x = _getch();
			if ('a' == x || 's' == x || 'd' == x || 'w' == x)
			{
				drawPlaneToNull();
				planeMove(x);
				drawPlane();
				judgePlane();
			}
			else if ('p' == x)
				Pause();
			else if ('k' == x)
				Shoot();
			else if ('e' == x)
			{
				//CloseHandle(MFUN);  
				GameOver();
				break;
			}

		}
		/* 处理子弹 */
		if (0 == flag_bullet)
		{
			bulletMove();
			drawBulletToNull();
			drawBullet();
			judgeEnemy();
		}
		flag_bullet++;
		if (5 == flag_bullet)
			flag_bullet = 0;

		/* 处理敌人 */
		if (0 == flag_enemy)
		{
			drawEnemyToNull();
			enemyMove();
			drawEnemy();
			judgePlane();
		}
		flag_enemy++;
		if (flag_enemy >= rank)
			flag_enemy = 0;

		/* 输出得分 */
		printScore();
	}
}

void Game::GameOver()
{
	system("cls");
	COORD p1 = { 28,9 };
	COORD p2 = { 53,15 };
	drawFrame(p1, p2, '=', '|');
	SetPos(36, 12);
	string str = "Game Over!";
	for (int i = 0; i<str.size(); i++)
	{
		Sleep(80);
		cout << str[i];
	}
	Sleep(1000);
	system("cls");
	drawFrame(p1, p2, '=', '|');
	SetPos(31, 11);
	cout << "击落敌机：" << score / 5 << " 架";
	SetPos(31, 12);
	cout << "得　　分：" << score;
	SetPos(31, 13);
	cout << "获得称号：" << title;
	SetPos(30, 16);
	Sleep(1000);
	cout << "继续？ 是（y）| 否（n）制作：fanjun";
as:
	char x = _getch();
	if (x == 'n')
		exit(0);
	else if (x == 'y')
	{
		system("cls");
		Game game;
		int a = drawMenu();
		if (a == 2)
			game.rank = 20;
		system("cls");
		drawPlaying();
		game.Playing();
	}
	else goto as;
}

#endif // !GAME_CLASS_H
