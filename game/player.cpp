#include<graphics.h>

extern IMAGE imgStand[2];//��ɫվ��
extern IMAGE imgWalk[2];//��ɫ�ƶ�
extern int playerX, playerY;
extern int speedX, speedY;//�ٶ�
extern int direction;//��ҷ���
int standFrames;//վ��֡��
int standVar = 0;//վ������
int walkFrames;//��·֡��
int walkVar;//��·����


/// <summary>
/// վ������
/// </summary>
void Stand()
{
	//loadPlayer();
	standFrames = 25;
	for (int i = 0; i < 2; i++)
	{
		//65,76Ϊ���Ƶĸ߶ȺͿ��
		putimage(playerX, playerY, 65, 76, &imgStand[0], standVar / standFrames * 65, direction * 76, NOTSRCERASE);
		putimage(playerX, playerY, 65, 76, &imgStand[1], standVar / standFrames * 65, direction * 76, SRCINVERT);
		FlushBatchDraw();// ִ��δ��ɵĻ�������
		standVar++;
		if (standVar == 4 * standFrames)
			standVar = 0;
	}
}

/// <summary>
/// ��·����
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
		FlushBatchDraw();// ִ��δ��ɵĻ�������
		walkVar++;
		if (walkVar == 4 * walkFrames)
			walkVar = 0;
	}
}