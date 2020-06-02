#include<graphics.h>

extern IMAGE imgStand[2];//��ɫվ��
extern IMAGE imgWalk[2];//��ɫ�ƶ�
extern IMAGE imgAttack[2][4];//����
extern int playerX, playerY;
extern int speedX, speedY;//�ٶ�
extern int direction;//��ҷ���
extern int isAttack;//�Ƿ񹥻�
int standFrames;//վ��֡��
int standVar = 0;//վ������
int walkFrames;//��·֡��
int walkVar;//��·����
int walkStopDelay;//��·ֹͣ�ӳ�
int attackType = 0;//��������
int attackFrames = 0;//����֡��
int attackDelay[4] = { 30,30,30,40 };//��ͬ�������ӳ�
int attackX[4] = { 86,90,113,116 }; //����ͼ��y�ĵ���
int attackY[4] = { 86,76,72,94 }; //����ͼ��y�ĵ���
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

/// <summary>
/// ��������
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