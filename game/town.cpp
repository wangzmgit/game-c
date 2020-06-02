#include<graphics.h>
#define MaxWidth 1990
#define TopMargin 300
#define BottomMargin 520
/***********************全局变量*************************/
IMAGE imgTouch[2];//触发位置图片
IMAGE imgNPC[1][2];//NPC
IMAGE imgDialogBox;//对话框
IMAGE backgroundTown;//背景图
int backgroundTownX = 0;
extern int walkStopDelay;//走路停止延迟
extern int speedX, speedY;//速度
extern int playerX, playerY;//玩家坐标
extern int direction;//玩家方向
extern int leftMargin, rightMargin;
/***********************函数声明*************************/
void load_town();
void show_town();
void Stand();//站立动画，位于player
void walk();//行走动画，位于player
void forest();//森林场景
void touchSite();
void clickContinue();
void updateWithInput_town();
void staticResourceLoading();
/// <summary>
/// 城镇主函数
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
/// 加载
/// </summary>
void load_town()
{	
	playerX = 250;
	playerY = 450;
	loadimage(&backgroundTown, _T("..\\images\\Scenes\\town.jpg"));//背景图
	loadimage(&imgNPC[0][0], _T("..\\images\\NPC\\NPC_10.jpg"));//NPC1
	loadimage(&imgNPC[0][1], _T("..\\images\\NPC\\NPC_11.jpg"));
	loadimage(&imgTouch[0], _T("..\\images\\other\\touch_0.jpg"));
	loadimage(&imgTouch[1], _T("..\\images\\other\\touch_1.jpg"));
	loadimage(&imgDialogBox, _T("..\\images\\other\\DialogBox.png"));
}

/// <summary>
/// 显示
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
	//触发对话
	touchSite();
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
void updateWithInput_town()
{
	if ((GetAsyncKeyState(0x41) & 0x8000))//向左
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
/// 静态图片绘制
/// </summary>
void staticResourceLoading()
{
	//BeginBatchDraw();
	putimage(0, 0, 900, 600, &backgroundTown, backgroundTownX, 0);
	//左一NPC和触发光圈
	putimage(420 - backgroundTownX, 270, &imgNPC[0][0], NOTSRCERASE);
	putimage(420 - backgroundTownX, 270, &imgNPC[0][1], SRCINVERT);
	putimage(445 - backgroundTownX, 365, &imgTouch[0], NOTSRCERASE);
	putimage(445 - backgroundTownX, 365, &imgTouch[1], SRCINVERT);
	//EndBatchDraw();
}

/// <summary>
/// 触发对话框
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

			outtextxy(50, 470,_T("你好"));//输出文字
			clickContinue();//等待鼠标点击
			putimage(10, 395, &imgDialogBox);//重新加载对话框

			outtextxy(50, 470, _T("需要买点什么"));
			clickContinue();
			putimage(10, 395, &imgDialogBox);
			
			outtextxy(50, 470, _T("..."));
			clickContinue();
			putimage(10, 395, &imgDialogBox);

			outtextxy(50, 470, _T("再见"));
			clickContinue();
		}	
	}
}

/// <summary>
/// 暂停，鼠标单击后继续
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

