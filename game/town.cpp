#include<graphics.h>
#define MaxWidth 1990
/***********************全局变量*************************/
IMAGE imgWalk[2];//角色移动
IMAGE imgStand[2];//角色站立
IMAGE backgroundTown;//背景图
int standFrames;//站立帧数
int standVar = 0;//站立变量
int walkFrames;//走路帧数
int walkVar;//走路变量
int walkStopDelay;//走路停止延迟
int speedX = 0, speedY = 0;//速度
int backgroundX = 0;
extern int playerX, playerY;
extern int direction;
extern int leftMargin, rightMargin;
/***********************函数声明*************************/
void load();
void show();
void Stand();
void walk();
void updateWithInput();

/// <summary>
/// 城镇主函数
/// </summary>
void town()
{
	load();
	while (true)
	{
		show();
		updateWithInput();
	}
}
/// <summary>
/// 加载城镇
/// </summary>
void load()
{	
	playerX = 250;
	playerY = 450;
	loadimage(&backgroundTown, _T("..\\images\\Scenes\\town.jpg"));//背景图
	loadimage(&imgStand[0], _T("..\\images\\Character\\stand\\stand_0.jpg"));//站立
	loadimage(&imgStand[1], _T("..\\images\\Character\\stand\\stand_1.jpg"));
	loadimage(&imgWalk[0], _T("..\\images\\Character\\walk\\walk_0.jpg"));//运动
	loadimage(&imgWalk[1], _T("..\\images\\Character\\walk\\walk_1.jpg"));	
}

/// <summary>
/// 显示
/// </summary>
void show()
{
	putimage(0, 0,900,600, &backgroundTown, backgroundX,0);
	if (speedX == 0)
	{
		Stand();
	}
	else if(speedX!=0)
	{
		walk();
	}

	if (walkStopDelay != 0)
		walkStopDelay--;
	else
		speedX = 0;
	Sleep(20);
}

/// <summary>
/// 站立动画
/// </summary>
void Stand()
{
	standFrames = 25;
	for (int i = 0; i < 2; i++)
	{
		//65,76为绘制的高度和宽度
		putimage(playerX, playerY , 65, 76, &imgStand[0], standVar / standFrames * 65, direction * 76, NOTSRCERASE);
		putimage(playerX, playerY , 65, 76, &imgStand[1], standVar / standFrames * 65, direction * 76, SRCINVERT);
		FlushBatchDraw();// 执行未完成的绘制任务
		standVar++;
		if (standVar == 4 * standFrames)
			standVar = 0;
	}
}

/// <summary>
/// 走路动画
/// </summary>
void walk()
{
	walkFrames = 10;
	playerX += speedX;
	for (int i = 0; i < 2; i++)
	{
		putimage(playerX, playerY , 67, 76, &imgWalk[0], walkVar / walkFrames * 67, direction * 76, NOTSRCERASE);
		putimage(playerX, playerY , 67, 76, &imgWalk[1], walkVar / walkFrames * 67, direction * 76, SRCINVERT);
		FlushBatchDraw();// 执行未完成的绘制任务
		walkVar++;
		if (walkVar == 4 * walkFrames)
			walkVar = 0;
	}
}


/// <summary>
/// 与用户输入有关的更新
/// </summary>
void updateWithInput()
{
	if ((GetAsyncKeyState(0x41) & 0x8000))//向左
	{
		speedX = -2;
		direction = 0;
		if (playerX >= leftMargin)
		{
			playerX += speedX;
			if (backgroundX > 0)
				backgroundX += speedX;
		}
		else
		{
			playerX = leftMargin;
			if (backgroundX > 0)
				backgroundX += (2 * speedX);
		}
		walkStopDelay = 1;
	}
	else if ((GetAsyncKeyState(0x44) & 0x8000))
	{
		speedX = 2;
		direction = 1;	
		if (playerX<=rightMargin)
		{			
			playerX += speedX;
			if(backgroundX <MaxWidth)
				backgroundX += speedX;
		}
		else
		{
			playerX = rightMargin;
			if (backgroundX <MaxWidth)
				backgroundX += (2*speedX);
		}
		walkStopDelay = 1;
	}
}
