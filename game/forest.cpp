#include<graphics.h>

#define MaxWidth 1200
#define TopMargin 350
#define BottomMargin 520
#define MaxEnemyCount 3//���ͬʱ���ڹ�����

struct snowball {
	int startX;
	int x;
	int y;
	int ballDirection;
	int flag;//�Ƿ����
};
struct enemy {
	int x;
	int y;
	int enemyDirection;
	int walkVar;//���ߵı���
	int speed;
	float blood;
	int flag;
};
snowball ball;
enemy monkey[MaxEnemyCount];
IMAGE backgroundForest;//����ͼ
IMAGE imgSnowball[2][2];//ѩ��ͼƬ
IMAGE imgMonkey[2];//����ͼƬ
int backgroundForestX = 0;
int isAttack = 0;//�Ƿ񹥻�
int attackCount = 0;//���ڼ�¼����������֡��
int walkFrames =0;//��·֡��
int enemyCount = 1;//ˢ������ˢ�ֳɹ�+1

extern int walkStopDelay;//��·ֹͣ�ӳ�
extern int speedX, speedY;//�ٶ�
extern int playerX, playerY;//�������
extern int direction;//��ҷ���
extern int leftMargin, rightMargin;//���ұ߽�
extern int gold;//�������

void stand();//վ��������λ��player
void walk();//���߶�����λ��player
void playerUI();//���UI��λ��player
void attack();//����������λ��player
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
		Sleep(30);
	}
}

/// <summary>
/// ������Դ����ʼ��
/// </summary>
void load_forest()
{
	//��ʼ���������
	playerX = 250;
	playerY = 450;
	//��ʼ��ѩ��
	ball.flag = 0;//0��ʾ������
	//���������ɫ
	setfillcolor(RED);
	//��ʼ������
	for (int i = 0; i < MaxEnemyCount; i++)
	{	
		monkey[i].flag= 0;
		monkey[i].enemyDirection = 0;
		monkey[i].walkVar = 0;
		monkey[i].speed = 2;
	}
	//���ر���ͼ
	loadimage(&backgroundForest, _T("..\\images\\Scenes\\forest.jpg"));//����ͼ
	//����ѩ��ͼ
	loadimage(&imgSnowball[0][0], _T("..\\images\\other\\snowball00.jpg"));
	loadimage(&imgSnowball[0][1], _T("..\\images\\other\\snowball01.jpg"));
	loadimage(&imgSnowball[1][0], _T("..\\images\\other\\snowball10.jpg"));
	loadimage(&imgSnowball[1][1], _T("..\\images\\other\\snowball11.jpg"));
	//���غ���ͼ
	loadimage(&imgMonkey[0], _T("..\\images\\NeutralCreature\\monkey_0.jpg"));
	loadimage(&imgMonkey[1], _T("..\\images\\NeutralCreature\\monkey_1.jpg"));
}

/// <summary>
/// ��ʾ����
/// </summary>
void show_forest()
{
	putimage(0, 0, 900, 600, &backgroundForest, backgroundForestX, 0);
	//�������UI
	playerUI();
	//���������Ϊ��ʾ����
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

	//����ѩ��ͺ���
	drawSnowballAndEnemy();
	
	//��ֹ�������Խ��
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
	FlushBatchDraw();// ִ��δ��ɵĻ�������
}

/// <summary>
/// ���û������йصĸ���
/// </summary>
void updateWithInput_forest()
{
	//�����ƶ�
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

	//�����ƶ�
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

	if ((GetAsyncKeyState(0x4A) & 0x8000))//����
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

	if (enemyCount <= 10)
	{
		//10Ϊ������������
		createEnemy();//���ɹ���
	}

	//ִ�е��˵���Ϊ
	enemyBehavior();

	//���е���
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
/// ����ѩ��͵���
/// </summary>
void drawSnowballAndEnemy()
{
	//����ѩ��
	if (ball.flag == 1)
	{
		putimage(ball.x, ball.y, &imgSnowball[ball.ballDirection][0], NOTSRCERASE);
		putimage(ball.x, ball.y, &imgSnowball[ball.ballDirection][1], SRCINVERT);
	}

	monkeyWalk();
	FlushBatchDraw();// ִ��δ��ɵĻ�������
}

/// <summary>
/// ��������
/// </summary>
void createEnemy()
{
	//ÿ��ִ���� %���ʴ�������
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
				//��������Լ��
				if (monkey[i].y < TopMargin || monkey[i].y > BottomMargin)
				{
					monkey[i].flag = 0;
				}

				if (monkey[i].flag == 1)
				{
					//���ˢ�ֳɹ�����¼
					enemyCount++;
				}
				break;
			}
		}
	}
}

/// <summary>
/// �����߶�
/// </summary>
void monkeyWalk()
{
	walkFrames = 10;//��·֡��
	for (int i = 0; i < MaxEnemyCount; i++)
	{
		if (monkey[i].flag == 1)
		{
			putimage(monkey[i].x - backgroundForestX, monkey[i].y, 61, 55, &imgMonkey[0], monkey[i].walkVar / walkFrames * 61, monkey[i].enemyDirection * 55, NOTSRCERASE);
			putimage(monkey[i].x - backgroundForestX, monkey[i].y, 61, 55, &imgMonkey[1], monkey[i].walkVar / walkFrames * 61, monkey[i].enemyDirection * 55, SRCINVERT);
			//����Ѫ��
			rectangle(monkey[i].x - backgroundForestX + 10, monkey[i].y - 10, monkey[i].x - backgroundForestX + 55, monkey[i].y - 5);
			fillrectangle(monkey[i].x - backgroundForestX + 10, monkey[i].y - 10, monkey[i].x - backgroundForestX + (10+(int)((monkey[i].blood/3)*45 )),monkey[i].y - 5);
			FlushBatchDraw();// ִ��δ��ɵĻ�������

		}
		monkey[i].walkVar++;
		if (monkey[i].walkVar == 3 * walkFrames)
			monkey[i].walkVar = 0;
	}
}

/// <summary>
/// ������Ϊ
/// </summary>
void enemyBehavior()
{
	for (int i = 0; i < MaxEnemyCount; i++)
	{
		int choose = rand() % 2;//1/2�ĸ����ƶ�
		switch (choose)
		{
		case 0:
			//�����ƶ�
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
			//���Ѫ������2.5���˶��ٶȱ��
			monkey[i].speed = 4;
		}
	}
	
}

