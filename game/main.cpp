#include<graphics.h>
#include<conio.h>

#define Width 900 //������
#define Height 600 //����߶�
/***********************ȫ�ֱ���*************************/
int playerX=0, playerY=0;//�������
int leftMargin = 50, rightMargin = Width - 50-76;//���ұ߾�,76Ϊ������
int direction=0;//��ҷ���


/***********************��������*************************/
extern void town();

int main()
{

	initgraph(Width, Height);
	town();
	_getch();
	closegraph();
	return 0;
}