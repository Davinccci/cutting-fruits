
/**************************************************************
Filename��start.c  Author: ������   Version:1.0   Date:10.19
Description:���ļ������˹��ڲ˵�����غ���
Function List:
	   1int menu(void)     //���˵�
	   2.void menu_screen(Button* button1)  //���˵�����
History�� 10.22дע��
<author>  <time> <version> <desc>
������    19/10/19  1.0    build this module
***************************************************************/
#include"common.h"
#include"start.h"
int menu(void)
{
	int page = 0;
	int exit_status = 0;
	MouseOff();
	delay(100);

	menu_screen();
	MouseOn(MouseX, MouseY);

	draw_exit_button(0);

	while (page == 0)
	{
		MouseStatus();
		/*******************************************************/
		if (mouse_press(10, 455, 50, 475) == 2)
		{
			if (exit_status != 2)
			{
				MouseOff();
				draw_exit_button(2);
				MouseOn(MouseX, MouseY);
				exit_status = 2;
			}
		}
		if (mouse_press(10, 455, 50, 475) == 1)
		{
			draw_exit_button(1);
			delay(200);
			page = 99;
			exit_status = 1;
		}
		if (mouse_press(0, 435, 50, 475) == 0)
		{
			if (exit_status != 0)
			{
				draw_exit_button(0);
				exit_status = 0;
			}
		}
		/*************************************************************/
		if (mouse_press(180, 200, 250, 270) == 1)
		{
			delay(150);
			page = 1;//��ʼ��Ϸ


		}
		else if (mouse_press(180, 330, 250, 400) == 1)
		{
			page = 2;//���а�
		}
		else if (mouse_press(380, 200, 470, 270) == 1)
		{
			page = 3;//�ɾ�
		}
		else if (mouse_press(380, 330, 470, 400) == 1)
		{
			page = 4;//ѡ��
		}
		// else if (mouse_press(540, 460, 640, 480) == 1)
		// {
			// page = 5;//�����ּ�
		// }
		else if (mouse_press(0, 460, 50, 480) == 1)
		{
			page = 99;//�˳�
		}
	}
	return page;
}

void menu_screen()
{
	cleardevice();
	bkground();
	setbkcolor(BLACK);

	// setfillstyle(SOLID_FILL, BROWN);
	// bar(0, 0, 640, 480);
	apple(170, 190);
	pear(370, 190);
	watermelon(160, 300);
	banana(370, 330);
	setfillstyle(SOLID_FILL, BLUE);

	//bar(170,290,270,310);
	puthz(190, 290, "��ʼ��Ϸ", 16, 16, WHITE);
	//bar(170,430,270,450);
	puthz(200, 430, "���а�", 16, 16, WHITE);
	//bar(370,290,470,310);
	puthz(400, 290, "�ɾ�", 16, 16, WHITE);
	//bar(370,430,470,450);
	puthz(400, 430, "ѡ��", 16, 16, WHITE);
	//bar(0,460,50,480);
	puthz(10, 460, "�˳�", 16, 16, WHITE);
	//bar(540,460,640,480);
	//puthz(550, 460, "�����ּ�", 16, 16, WHITE);
	puthz(210, 70, "ˮ������", 48, 64, WHITE);

}