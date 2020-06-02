#include<graphics.h>

extern IMAGE imgStand[2];//角色站立
extern IMAGE imgWalk[2];//角色移动
extern int playerX, playerY;
extern int speedX, speedY;//速度
extern int direction;//玩家方向
int standFrames;//站立帧数
int standVar = 0;//站立变量
int walkFrames;//走路帧数
int walkVar;//走路变量


/// <summary>
/// 站立动画
/// </summary>
void Stand()
{
	//loadPlayer();
	standFrames = 25;
	for (int i = 0; i < 2; i++)
	{
		//65,76为绘制的高度和宽度
		putimage(playerX, playerY, 65, 76, &imgStand[0], standVar / standFrames * 65, direction * 76, NOTSRCERASE);
		putimage(playerX, playerY, 65, 76, &imgStand[1], standVar / standFrames * 65, direction * 76, SRCINVERT);
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
	playerY += speedY;
	for (int i = 0; i < 2; i++)
	{
		putimage(playerX, playerY, 67, 76, &imgWalk[0], walkVar / walkFrames * 67, direction * 76, NOTSRCERASE);
		putimage(playerX, playerY, 67, 76, &imgWalk[1], walkVar / walkFrames * 67, direction * 76, SRCINVERT);
		FlushBatchDraw();// 执行未完成的绘制任务
		walkVar++;
		if (walkVar == 4 * walkFrames)
			walkVar = 0;
	}
}