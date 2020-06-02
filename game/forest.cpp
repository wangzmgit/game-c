#include<graphics.h>
#define MaxWidth 1200
#define TopMargin 350
#define BottomMargin 520

struct snowball {
	int startX;
	int x;
	int y;
	int ballDirection;
	int flag;//是否存在
};
snowball ball;
IMAGE backgroundForest;//背景图
IMAGE imgSnowball[2][2];
int backgroundForestX = 0;
int isAttack = 0;//是否攻击
int attackCount = 0;//用于记录攻击动画的帧数

extern int walkStopDelay;//走路停止延迟
extern int speedX, speedY;//速度
extern int playerX, playerY;//玩家坐标
extern int direction;//玩家方向
extern int leftMargin, rightMargin;

void Stand();//站立动画，位于player
void walk();//行走动画，位于player
void attack();
void forest();
void load_forest();
void show_forest();
void createSnowball();
void drawSnowball();
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
		Sleep(20);
	}
}

/// <summary>
/// 加载资源
/// </summary>
void load_forest()
{
	playerX = 250;
	playerY = 450;
	//初始化雪球
	ball.flag = 0;//0表示不存在
	loadimage(&backgroundForest, _T("..\\images\\Scenes\\forest.jpg"));//背景图
	//雪球
	loadimage(&imgSnowball[0][0], _T("..\\images\\other\\snowball00.jpg"));
	loadimage(&imgSnowball[0][1], _T("..\\images\\other\\snowball01.jpg"));
	loadimage(&imgSnowball[1][0], _T("..\\images\\other\\snowball10.jpg"));
	loadimage(&imgSnowball[1][1], _T("..\\images\\other\\snowball11.jpg"));
}

/// <summary>
/// 显示内容
/// </summary>
void show_forest()
{
	putimage(0, 0, 900, 600, &backgroundForest, backgroundForestX, 0);
	drawSnowball();//绘制雪球
	if (speedX == 0 && speedY == 0&&isAttack==0)
	{
		Stand();
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

	//防止上下越界
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
}

/// <summary>
/// 与用户输入有关的更新
/// </summary>
void updateWithInput_forest()
{
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

	if ((GetAsyncKeyState(0x4A) & 0x8000))//攻击延迟
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
/// 绘制雪球
/// </summary>
void drawSnowball()
{
	if (ball.flag == 1)
	{
		putimage(ball.x , ball.y, &imgSnowball[ball.ballDirection][0], NOTSRCERASE);
		putimage(ball.x , ball.y, &imgSnowball[ball.ballDirection][1], SRCINVERT);
	}
}
