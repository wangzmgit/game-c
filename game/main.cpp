#include<graphics.h>
#include<conio.h>

#define Width 900 //������
#define Height 600 //����߶�
/***********************ȫ�ֱ���*************************/
IMAGE imgStand[2];//��ɫվ��
IMAGE imgWalk[2];//��ɫ�ƶ�
IMAGE imgAttack[2][4];//����
int leftMargin = 10;//��߾�
int rightMargin = Width - 86;//�ұ߾�,������76+�߾�10
int playerX, playerY;//�������
int direction = 1;//��ҷ���
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
	loadimage(&imgAttack[0][0], _T("..\\images\\Character\\attack\\attack_01.bmp"));//����
	loadimage(&imgAttack[1][0], _T("..\\images\\Character\\attack\\attack_11.bmp"));
	loadimage(&imgAttack[0][1], _T("..\\images\\Character\\attack\\attack_02.bmp"));
	loadimage(&imgAttack[1][1], _T("..\\images\\Character\\attack\\attack_12.bmp"));
	loadimage(&imgAttack[0][2], _T("..\\images\\Character\\attack\\attack_03.bmp"));
	loadimage(&imgAttack[1][2], _T("..\\images\\Character\\attack\\attack_13.bmp"));
	loadimage(&imgAttack[0][3], _T("..\\images\\Character\\attack\\attack_04.bmp"));
	loadimage(&imgAttack[1][3], _T("..\\images\\Character\\attack\\attack_14.bmp"));
}