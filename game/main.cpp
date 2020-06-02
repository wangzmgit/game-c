#include<graphics.h>
#include<conio.h>

#define Width 900 //界面宽度
#define Height 600 //界面高度
/***********************全局变量*************************/
IMAGE imgStand[2];//角色站立
IMAGE imgWalk[2];//角色移动
int leftMargin = 50;//左边距
int rightMargin = Width - 126;//右边距,人物宽度76+边距50
int playerX, playerY;//玩家坐标
int direction = 0;//玩家方向
int speedX = 0, speedY = 0;//速度
/***********************函数声明*************************/
void town();
void loadMain();

int main()
{
	initgraph(Width, Height);
	loadMain();
	town();
	_getch();
	closegraph();
	return 0;
}

void loadMain()
{
	loadimage(&imgStand[0], _T("..\\images\\Character\\stand\\stand_0.jpg"));//站立
	loadimage(&imgStand[1], _T("..\\images\\Character\\stand\\stand_1.jpg"));
	loadimage(&imgWalk[0], _T("..\\images\\Character\\walk\\walk_0.jpg"));//运动
	loadimage(&imgWalk[1], _T("..\\images\\Character\\walk\\walk_1.jpg"));
}