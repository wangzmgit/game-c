#include<graphics.h>
#define MaxWidth 1990
#define TopMargin 300
#define BottomMargin 520
/***********************ȫ�ֱ���*************************/
IMAGE imgTouch[2];//����λ��ͼƬ
IMAGE imgNPC[1][2];//NPC
IMAGE imgDialogBox;//�Ի���
IMAGE backgroundTown;//����ͼ
int backgroundTownX = 0;
extern int walkStopDelay;//��·ֹͣ�ӳ�
extern int speedX, speedY;//�ٶ�
extern int playerX, playerY;//�������
extern int direction;//��ҷ���
extern int leftMargin, rightMargin;
/***********************��������*************************/
void load_town();
void show_town();
void Stand();//վ��������λ��player
void walk();//���߶�����λ��player
void forest();//ɭ�ֳ���
void touchSite();
void clickContinue();
void updateWithInput_town();
void staticResourceLoading();
/// <summary>
/// ����������
/// </summary>
void town()
{
	load_town();
	while (true)
	{
		show_town();
		updateWithInput_town();
		Sleep(20);
	}
}
/// <summary>
/// ����
/// </summary>
void load_town()
{	
	playerX = 250;
	playerY = 450;
	loadimage(&backgroundTown, _T("..\\images\\Scenes\\town.jpg"));//����ͼ
	loadimage(&imgNPC[0][0], _T("..\\images\\NPC\\NPC_10.jpg"));//NPC1
	loadimage(&imgNPC[0][1], _T("..\\images\\NPC\\NPC_11.jpg"));
	loadimage(&imgTouch[0], _T("..\\images\\other\\touch_0.jpg"));
	loadimage(&imgTouch[1], _T("..\\images\\other\\touch_1.jpg"));
	loadimage(&imgDialogBox, _T("..\\images\\other\\DialogBox.png"));
}

/// <summary>
/// ��ʾ
/// </summary>
void show_town()
{
	staticResourceLoading();
	if (speedX == 0&&speedY==0)
	{
		Stand();
	}
	else if(speedX!=0||speedY!=0)
	{
		walk();	
	}
	//�����Ի�
	touchSite();
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
void updateWithInput_town()
{
	if ((GetAsyncKeyState(0x41) & 0x8000))//����
	{
		speedX = -2;
		direction = 0;
		if (playerX >= leftMargin)
		{
			playerX += speedX;
			if (backgroundTownX > 0)
				backgroundTownX += speedX;
		}
		else
		{
			playerX = leftMargin;
			if (backgroundTownX > 0)
				backgroundTownX += (2 * speedX);
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
			if(backgroundTownX <MaxWidth)
				backgroundTownX += speedX;
		}
		else
		{
			playerX = rightMargin;
			if (backgroundTownX <MaxWidth)
				backgroundTownX += (2*speedX);
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
}

/// <summary>
/// ��̬ͼƬ����
/// </summary>
void staticResourceLoading()
{
	//BeginBatchDraw();
	putimage(0, 0, 900, 600, &backgroundTown, backgroundTownX, 0);
	//��һNPC�ʹ�����Ȧ
	putimage(420 - backgroundTownX, 270, &imgNPC[0][0], NOTSRCERASE);
	putimage(420 - backgroundTownX, 270, &imgNPC[0][1], SRCINVERT);
	putimage(445 - backgroundTownX, 365, &imgTouch[0], NOTSRCERASE);
	putimage(445 - backgroundTownX, 365, &imgTouch[1], SRCINVERT);
	//EndBatchDraw();
}

/// <summary>
/// �����Ի���
/// </summary>
void touchSite()
{
	if (playerX > (430 - backgroundTownX) && playerX < (480 - backgroundTownX)&&playerY<325)
	{
		if ((GetAsyncKeyState(VK_TAB) & 0x8000))
		{
			forest();
			putimage(10, 395, &imgDialogBox);
			setbkmode(TRANSPARENT);

			outtextxy(50, 470,_T("���"));//�������
			clickContinue();//�ȴ������
			putimage(10, 395, &imgDialogBox);//���¼��ضԻ���

			outtextxy(50, 470, _T("��Ҫ���ʲô"));
			clickContinue();
			putimage(10, 395, &imgDialogBox);
			
			outtextxy(50, 470, _T("..."));
			clickContinue();
			putimage(10, 395, &imgDialogBox);

			outtextxy(50, 470, _T("�ټ�"));
			clickContinue();
		}	
	}
}

/// <summary>
/// ��ͣ����굥�������
/// </summary>
void clickContinue()
{
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
			return;
	}
}

