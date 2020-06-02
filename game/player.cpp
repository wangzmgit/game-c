#include<graphics.h>

extern IMAGE imgStand[2];//角色站立
extern IMAGE imgWalk[2];//角色移动
extern IMAGE imgAttack[2][4];//攻击
extern int playerX, playerY;
extern int speedX, speedY;//速度
extern int direction;//玩家方向
extern int isAttack;//是否攻击
int standFrames;//站立帧数
int standVar = 0;//站立变量
int walkFrames;//走路帧数
int walkVar;//走路变量
int walkStopDelay;//走路停止延迟
int attackType = 0;//攻击类型
int attackFrames = 0;//攻击帧数
int attackDelay[4] = { 30,30,30,40 };//不同攻击的延迟
int attackX[4] = { 86,90,113,116 }; //攻击图像y的调整
int attackY[4] = { 86,76,72,94 }; //攻击图像y的调整
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

/// <summary>
/// 攻击动画
/// </summary>
void attack()
{
	putimage(playerX, playerY- attackY[attackType]+76, attackX[attackType], attackY[attackType], &imgAttack[0][attackType], attackFrames / 10 * attackX[attackType], direction * attackY[attackType], SRCAND);
	putimage(playerX, playerY - attackY[attackType]+76, attackX[attackType], attackY[attackType], &imgAttack[1][attackType], attackFrames / 10 * attackX[attackType], direction * attackY[attackType], SRCPAINT);
	attackFrames++;
	if (attackFrames == attackDelay[attackType])
	{
		attackFrames = 0;
		attackType = rand() % 4;
		isAttack = 0;
	}
	FlushBatchDraw();
}