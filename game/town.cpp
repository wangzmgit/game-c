#include<graphics.h>
#define MaxWidth 1990
/***********************ȫ�ֱ���*************************/
IMAGE imgWalk[2];//��ɫ�ƶ�
IMAGE imgStand[2];//��ɫվ��
IMAGE backgroundTown;//����ͼ
int standFrames;//վ��֡��
int standVar = 0;//վ������
int walkFrames;//��·֡��
int walkVar;//��·����
int walkStopDelay;//��·ֹͣ�ӳ�
int speedX = 0, speedY = 0;//�ٶ�
int backgroundX = 0;
extern int playerX, playerY;
extern int direction;
extern int leftMargin, rightMargin;
/***********************��������*************************/
void load();
void show();
void Stand();
void walk();
void updateWithInput();

/// <summary>
/// ����������
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
/// ���س���
/// </summary>
void load()
{	
	playerX = 250;
	playerY = 450;
	loadimage(&backgroundTown, _T("..\\images\\Scenes\\town.jpg"));//����ͼ
	loadimage(&imgStand[0], _T("..\\images\\Character\\stand\\stand_0.jpg"));//վ��
	loadimage(&imgStand[1], _T("..\\images\\Character\\stand\\stand_1.jpg"));
	loadimage(&imgWalk[0], _T("..\\images\\Character\\walk\\walk_0.jpg"));//�˶�
	loadimage(&imgWalk[1], _T("..\\images\\Character\\walk\\walk_1.jpg"));	
}

/// <summary>
/// ��ʾ
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
/// վ������
/// </summary>
void Stand()
{
	standFrames = 25;
	for (int i = 0; i < 2; i++)
	{
		//65,76Ϊ���Ƶĸ߶ȺͿ��
		putimage(playerX, playerY , 65, 76, &imgStand[0], standVar / standFrames * 65, direction * 76, NOTSRCERASE);
		putimage(playerX, playerY , 65, 76, &imgStand[1], standVar / standFrames * 65, direction * 76, SRCINVERT);
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
	for (int i = 0; i < 2; i++)
	{
		putimage(playerX, playerY , 67, 76, &imgWalk[0], walkVar / walkFrames * 67, direction * 76, NOTSRCERASE);
		putimage(playerX, playerY , 67, 76, &imgWalk[1], walkVar / walkFrames * 67, direction * 76, SRCINVERT);
		FlushBatchDraw();// ִ��δ��ɵĻ�������
		walkVar++;
		if (walkVar == 4 * walkFrames)
			walkVar = 0;
	}
}


/// <summary>
/// ���û������йصĸ���
/// </summary>
void updateWithInput()
{
	if ((GetAsyncKeyState(0x41) & 0x8000))//����
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
