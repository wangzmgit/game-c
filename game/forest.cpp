#include<graphics.h>
#define MaxWidth 1200
#define TopMargin 350
#define BottomMargin 520

struct snowball {
	int startX;
	int x;
	int y;
	int ballDirection;
	int flag;//�Ƿ����
};
snowball ball;
IMAGE backgroundForest;//����ͼ
IMAGE imgSnowball[2][2];
int backgroundForestX = 0;
int isAttack = 0;//�Ƿ񹥻�
int attackCount = 0;//���ڼ�¼����������֡��

extern int walkStopDelay;//��·ֹͣ�ӳ�
extern int speedX, speedY;//�ٶ�
extern int playerX, playerY;//�������
extern int direction;//��ҷ���
extern int leftMargin, rightMargin;

void Stand();//վ��������λ��player
void walk();//���߶�����λ��player
void attack();
void forest();
void load_forest();
void show_forest();
void createSnowball();
void drawSnowball();
void updateWithInput_forest();
void updateWithoutInput_forest();

/// <summary>
/// ɭ�ֳ���������
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
/// ������Դ
/// </summary>
void load_forest()
{
	playerX = 250;
	playerY = 450;
	//��ʼ��ѩ��
	ball.flag = 0;//0��ʾ������
	loadimage(&backgroundForest, _T("..\\images\\Scenes\\forest.jpg"));//����ͼ
	//ѩ��
	loadimage(&imgSnowball[0][0], _T("..\\images\\other\\snowball00.jpg"));
	loadimage(&imgSnowball[0][1], _T("..\\images\\other\\snowball01.jpg"));
	loadimage(&imgSnowball[1][0], _T("..\\images\\other\\snowball10.jpg"));
	loadimage(&imgSnowball[1][1], _T("..\\images\\other\\snowball11.jpg"));
}

/// <summary>
/// ��ʾ����
/// </summary>
void show_forest()
{
	putimage(0, 0, 900, 600, &backgroundForest, backgroundForestX, 0);
	drawSnowball();//����ѩ��
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

	//��ֹ����Խ��
	if (playerY < TopMargin) playerY = TopMargin;
	if (playerY > BottomMargin) playerY = BottomMargin;

	//��·�ӳٺ�ֹͣ
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
/// ���û������йصĸ���
/// </summary>
void updateWithInput_forest()
{
	if ((GetAsyncKeyState(0x41) & 0x8000))//����
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

	if ((GetAsyncKeyState(0x4A) & 0x8000))//�����ӳ�
	{
		isAttack = 1;
	}
}

/// <summary>
/// ���û������޹صĸ���
/// </summary>
void updateWithoutInput_forest()
{
	//ѩ���ƶ�
	if (ball.flag == 1)
	{		
		//�����˶�
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
				//274Ϊ350-���76
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
/// ��������ѩ��
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
/// ����ѩ��
/// </summary>
void drawSnowball()
{
	if (ball.flag == 1)
	{
		putimage(ball.x , ball.y, &imgSnowball[ball.ballDirection][0], NOTSRCERASE);
		putimage(ball.x , ball.y, &imgSnowball[ball.ballDirection][1], SRCINVERT);
	}
}
