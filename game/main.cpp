#include<graphics.h>
#include<conio.h>

#define Width 900 //������
#define Height 600 //����߶�
/***********************ȫ�ֱ���*************************/
IMAGE imgStand[2];//��ɫվ��
IMAGE imgWalk[2];//��ɫ�ƶ�
int leftMargin = 50;//��߾�
int rightMargin = Width - 126;//�ұ߾�,������76+�߾�50
int playerX, playerY;//�������
int direction = 0;//��ҷ���
int speedX = 0, speedY = 0;//�ٶ�
/***********************��������*************************/
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
	loadimage(&imgStand[0], _T("..\\images\\Character\\stand\\stand_0.jpg"));//վ��
	loadimage(&imgStand[1], _T("..\\images\\Character\\stand\\stand_1.jpg"));
	loadimage(&imgWalk[0], _T("..\\images\\Character\\walk\\walk_0.jpg"));//�˶�
	loadimage(&imgWalk[1], _T("..\\images\\Character\\walk\\walk_1.jpg"));
}