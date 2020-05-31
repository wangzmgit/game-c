#include<graphics.h>
#include<conio.h>

#define Width 900 //界面宽度
#define Height 600 //界面高度
/***********************全局变量*************************/
int playerX=0, playerY=0;//玩家坐标
int leftMargin = 50, rightMargin = Width - 50-76;//左右边距,76为人物宽度
int direction=0;//玩家方向


/***********************函数声明*************************/
extern void town();

int main()
{

	initgraph(Width, Height);
	town();
	_getch();
	closegraph();
	return 0;
}