#include<graphics.h>

#define MaxWidth 1200
#define TopMargin 350
#define BottomMargin 520
#define MaxEnemyCount 3//最大同时存在怪物量

struct snowball {
	int startX;
	int x;
	int y;
	int ballDirection;
	int flag;//是否存在
};
struct enemy {
	int x;
	int y;
	int enemyDirection;
	int walkVar;//行走的变量
	int speed;
	float blood;
	int flag;
};
snowball ball;
enemy monkey[MaxEnemyCount];
IMAGE backgroundForest;//背景图
IMAGE imgSnowball[2][2];//雪球图片
IMAGE imgMonkey[2];//猴子图片
int backgroundForestX = 0;
int isAttack = 0;//是否攻击
int attackCount = 0;//用于记录攻击动画的帧数
int walkFrames =0;//走路帧数
int enemyCount = 1;//刷怪量，刷怪成功+1

extern int walkStopDelay;//走路停止延迟
extern int speedX, speedY;//速度
extern int playerX, playerY;//玩家坐标
extern int direction;//玩家方向
extern int leftMargin, rightMargin;//左右边界
extern int gold;//金币数量

void stand();//站立动画，位于player
void walk();//行走动画，位于player
void playerUI();//玩家UI，位于player
void attack();//攻击动画，位于player
void forest();
void monkeyWalk();
void createEnemy();
void load_forest();
void show_forest();
void enemyBehavior();
void createSnowball();
void drawSnowballAndEnemy();
void updateWithInput_forest();
void updateWithoutInput_forest();

/// <summary>
/// 森林场景主函数
/// </summary>
void forest()
{
	load_forest();
	while (true)
	{
		show_forest();
		updateWithInput_forest();
		updateWithoutInput_forest();
		Sleep(30);
	}
}

/// <summary>
/// 加载资源及初始化
/// </summary>
void load_forest()
{
	//初始化玩家坐标
	playerX = 250;
	playerY = 450;
	//初始化雪球
	ball.flag = 0;//0表示不存在
	//设置填充颜色
	setfillcolor(RED);
	//初始化敌人
	for (int i = 0; i < MaxEnemyCount; i++)
	{	
		monkey[i].flag= 0;
		monkey[i].enemyDirection = 0;
		monkey[i].walkVar = 0;
		monkey[i].speed = 2;
	}
	//加载背景图
	loadimage(&backgroundForest, _T("..\\images\\Scenes\\forest.jpg"));//背景图
	//加载雪球图
	loadimage(&imgSnowball[0][0], _T("..\\images\\other\\snowball00.jpg"));
	loadimage(&imgSnowball[0][1], _T("..\\images\\other\\snowball01.jpg"));
	loadimage(&imgSnowball[1][0], _T("..\\images\\other\\snowball10.jpg"));
	loadimage(&imgSnowball[1][1], _T("..\\images\\other\\snowball11.jpg"));
	//加载猴子图
	loadimage(&imgMonkey[0], _T("..\\images\\NeutralCreature\\monkey_0.jpg"));
	loadimage(&imgMonkey[1], _T("..\\images\\NeutralCreature\\monkey_1.jpg"));
}

/// <summary>
/// 显示内容
/// </summary>
void show_forest()
{
	putimage(0, 0, 900, 600, &backgroundForest, backgroundForestX, 0);
	//绘制玩家UI
	playerUI();
	//根据玩家行为显示动画
	if (speedX == 0 && speedY == 0&&isAttack==0)
	{
		stand();
	}
	else if (speedX != 0 || speedY != 0)
	{
		walk();
	}
	else if (isAttack == 1)
	{		
		attack();
		++attackCount;
		if(attackCount%25==0)
			createSnowball();
	}

	//绘制雪球和猴子
	drawSnowballAndEnemy();
	
	//防止玩家上下越界
	if (playerY < TopMargin) playerY = TopMargin;
	if (playerY > BottomMargin) playerY = BottomMargin;

	//走路延迟和停止
	if (walkStopDelay != 0)
	{
		walkStopDelay--;
	}
	else
	{
		speedX = 0;
		speedY = 0;
	}
	FlushBatchDraw();// 执行未完成的绘制任务
}

/// <summary>
/// 与用户输入有关的更新
/// </summary>
void updateWithInput_forest()
{
	//左右移动
	if ((GetAsyncKeyState(0x41) & 0x8000))//向左
	{
		speedX = -2;
		direction = 0;
		if (playerX >= leftMargin)
		{
			playerX += speedX;
			if (backgroundForestX > 0)
				backgroundForestX += speedX;
		}
		else
		{
			playerX = leftMargin;
			if (backgroundForestX > 0)
				backgroundForestX += (2 * speedX);
		}
		walkStopDelay = 1;
	}
	else if ((GetAsyncKeyState(0x44) & 0x8000))
	{
		speedX = 2;
		direction = 1;
		if (playerX <= rightMargin)
		{
			playerX += speedX;
			if (backgroundForestX < MaxWidth)
				backgroundForestX += speedX;
		}
		else
		{
			playerX = rightMargin;
			if (backgroundForestX < MaxWidth)
				backgroundForestX += (2 * speedX);
		}
		walkStopDelay = 1;
	}

	//上下移动
	if ((GetAsyncKeyState(0x57) & 0x8000))
	{
		if (playerY > TopMargin)
		{
			speedY = -2;
			walkStopDelay = 1;
		}
	}
	else if ((GetAsyncKeyState(0x53) & 0x8000))
	{
		if (playerY < BottomMargin)
		{
			speedY = 2;
			walkStopDelay = 1;
		}
	}

	if ((GetAsyncKeyState(0x4A) & 0x8000))//攻击
	{
		isAttack = 1;
	}
}

/// <summary>
/// 与用户输入无关的更新
/// </summary>
void updateWithoutInput_forest()
{
	//雪球移动
	if (ball.flag == 1)
	{		
		//向右运动
		if (ball.ballDirection == 1)
		{
			if (ball.x - ball.startX < 350)
			{
				ball.x += 20;
				
			}
			else
			{
				ball.flag = 0;
			}
		}
		else
		{
			if (ball.startX-ball.x < 274)
			{
				//274为350-身宽76
				ball.x -= 20;
			}
			else
			{
				ball.flag = 0;
			}
		}
	}

	if (enemyCount <= 10)
	{
		//10为最大怪物生成量
		createEnemy();//生成怪物
	}

	//执行敌人的行为
	enemyBehavior();

	//击中敌人
	for (int i = 0; i < MaxEnemyCount; i++)
	{
		if ((ball.x >= monkey[i].x) && (ball.x <= monkey[i].x + 61) && (ball.y >= monkey[i].y) && (ball.y <= monkey[i].y + 45))
		{
			ball.flag = 0;
			monkey[i].blood -=0.05;		
			if (monkey[i].blood <= 0)
			{
				monkey[i].flag = 0;
				gold += rand() % 3;
			}
		}		
	}	
}

/// <summary>
/// 创建攻击雪球
/// </summary>
void createSnowball()
{
	if (ball.flag == 0)
	{
		ball.x = playerX+38;
		ball.y = playerY+25;
		ball.startX = playerX;
		ball.ballDirection = direction;
		ball.flag = 1;
	}
}

/// <summary>
/// 绘制雪球和敌人
/// </summary>
void drawSnowballAndEnemy()
{
	//绘制雪球
	if (ball.flag == 1)
	{
		putimage(ball.x, ball.y, &imgSnowball[ball.ballDirection][0], NOTSRCERASE);
		putimage(ball.x, ball.y, &imgSnowball[ball.ballDirection][1], SRCINVERT);
	}

	monkeyWalk();
	FlushBatchDraw();// 执行未完成的绘制任务
}

/// <summary>
/// 创建敌人
/// </summary>
void createEnemy()
{
	//每次执行有 %概率创建敌人
	if (rand() % 100 < 50)
	{
		for (int i = 0; i < MaxEnemyCount; i++)
		{
			if (monkey[i].flag == 0)
			{
				monkey[i].x = playerX + (rand() % 601-250);
				monkey[i].y = playerY + (rand() % 301 - 150);
				monkey[i].blood = 3;
				monkey[i].flag = 1;
				//坐标可用性检查
				if (monkey[i].y < TopMargin || monkey[i].y > BottomMargin)
				{
					monkey[i].flag = 0;
				}

				if (monkey[i].flag == 1)
				{
					//如果刷怪成功，记录
					enemyCount++;
				}
				break;
			}
		}
	}
}

/// <summary>
/// 猴子走动
/// </summary>
void monkeyWalk()
{
	walkFrames = 10;//走路帧数
	for (int i = 0; i < MaxEnemyCount; i++)
	{
		if (monkey[i].flag == 1)
		{
			putimage(monkey[i].x - backgroundForestX, monkey[i].y, 61, 55, &imgMonkey[0], monkey[i].walkVar / walkFrames * 61, monkey[i].enemyDirection * 55, NOTSRCERASE);
			putimage(monkey[i].x - backgroundForestX, monkey[i].y, 61, 55, &imgMonkey[1], monkey[i].walkVar / walkFrames * 61, monkey[i].enemyDirection * 55, SRCINVERT);
			//绘制血条
			rectangle(monkey[i].x - backgroundForestX + 10, monkey[i].y - 10, monkey[i].x - backgroundForestX + 55, monkey[i].y - 5);
			fillrectangle(monkey[i].x - backgroundForestX + 10, monkey[i].y - 10, monkey[i].x - backgroundForestX + (10+(int)((monkey[i].blood/3)*45 )),monkey[i].y - 5);
			FlushBatchDraw();// 执行未完成的绘制任务

		}
		monkey[i].walkVar++;
		if (monkey[i].walkVar == 3 * walkFrames)
			monkey[i].walkVar = 0;
	}
}

/// <summary>
/// 敌人行为
/// </summary>
void enemyBehavior()
{
	for (int i = 0; i < MaxEnemyCount; i++)
	{
		int choose = rand() % 2;//1/2的概率移动
		switch (choose)
		{
		case 0:
			//左右移动
			if (monkey[i].x > leftMargin - backgroundForestX && monkey[i].enemyDirection == 0)
			{
				monkey[i].x -= monkey[i].speed;
			}
			else if (monkey[i].x <= leftMargin - backgroundForestX)
			{
				monkey[i].x = leftMargin;
				monkey[i].enemyDirection = 1;
				monkey[i].x += 61;
			}
			else if (monkey[i].x < rightMargin + backgroundForestX && monkey[i].enemyDirection == 1)
			{
				monkey[i].x += monkey[i].speed;
			}
			else if (monkey[i].x >= rightMargin + backgroundForestX)
			{
				monkey[i].x = rightMargin + backgroundForestX;
				monkey[i].enemyDirection = 0;
			}
			break;
		}
		if (monkey[i].blood < 2.5)
		{
			//如果血量低于2.5，运动速度变快
			monkey[i].speed = 4;
		}
	}
	
}

