/**************************************************************
Filename��ach.c   Author: ������   Version:1.0   Date:10.19
Description:���ļ������˳ɾͽ������غ���
Function List:
	1.ach_main//�ɾ�ҳ��ġ��������������������������
	2.page3_screen//�ɾ�ҳ��Ļ�ͼ����
	3.ach_judge//�ɾ��жϺ���
	4.put_ach//���ɾ���һһд��
History�� 10.22дע��
<author>  <time> <version> <desc>
������    19/10/19  1.0    build this module
***************************************************************/
#include"common.h"
#include"ach.h"
/**************************************************************
Function:ach_main
Description:�ɾ�ҳ��ġ��������������������������
Calls:
	 1.page3_screen
	 2.MouseOn
	 3.MouseStatus
	 4.mouse_press
	 5.draw_exit_button
Input:User0 *user
Return:page
Others:
***************************************************************/
int ach_main(User0* user)
{
	int page = 3;
	int ach_page = 1;//�ɾ�ҳ������ҳ
	int i;//����
	int exit_status = 0;//�˳���ť��״̬
	Button ach_button[20];//ÿһ���ɾ�


	MouseOff();
	delay(100);
	/*��ʼ��ÿ����ť�������û���Ϣ���ֳ���*/

	for (i = 0; i < 20; i++)
	{
		ach_button[i].x1 = 50;
		ach_button[i].y1 = 110 + 90 * (i % 4);
		ach_button[i].x2 = 590;
		ach_button[i].y2 = 110 + 90 * (i % 4) + 70;
		ach_button[i].status = 0;
		if ((*user).ach[i] == 1)
		{
			ach_button[i].btcolor1 = GREEN;
		}
		else {
			ach_button[i].btcolor1 = LIGHTGRAY;
		}
	}
	change_achscore(user);
	page3_screen(ach_button, ach_page, user);
	MouseOn(MouseX,MouseY);

	while (page == 3)
	{
		MouseStatus();
		/******************�˳���ťģ��*******************************/
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
			page = 0;
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
		/*********************��ҳģ��****************************/
		if (mouse_press(525, 454, 545, 476) == 1)
		{
			if (ach_page > 1)
			{
				ach_page--;
				page3_screen(ach_button, ach_page, user);
				MouseOn(MouseX, MouseY);
			}
			delay(150);
		}
		if (mouse_press(603, 454, 623, 476) == 1)
		{
			if (ach_page < 5)
			{
				ach_page++;
				page3_screen(ach_button, ach_page, user);
				MouseOn(MouseX, MouseY);
			}
			delay(150);
		}

	}
	ach_page = 1;
	return page;
}

/**************************************************************
Function:page3_screen
Description:�ɾ�ҳ��Ļ�ͼ����
Calls:
	 1.put_ach
Input:Button *button,int ach_page,User0 *user
Return:��
Others������  2019.9.19
***************************************************************/
void page3_screen(Button* button, int ach_page, User0* user)
{
	int i;
	char ach_page_num[2];//ҳ��
	int r_trg[] = { 603,454,603,476,623,465,603,454 };
	int l_trg[] = { 545,454,545,476,525,465,545,454 };
	char ach_score[5];

	cleardevice();
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 0, 640, 480);
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(BLACK);
	drawpoly(4, r_trg);
	drawpoly(4, l_trg);
	floodfill(610, 460, BLACK);
	floodfill(540, 460, BLACK);

	settextstyle(0, HORIZ_DIR, 2);
	setcolor(WHITE);
	itoa(ach_page, ach_page_num, 10);
	outtextxy(550, 460, ach_page_num);
	outtextxy(565, 460, "/");
	outtextxy(580, 460, "5");
	draw_exit_button(0);
	puthz(250, 20, "�ɾ�", 48, 96, WHITE);

	for (i = (ach_page - 1) * 4; i < (ach_page - 1) * 4 + 4; i++)
	{
		drawbutton(button + i);
	}

	put_ach(ach_page, user);
	setcolor(WHITE);
	settextstyle(0, 0, 3);
	itoa(user->score[2], ach_score, 10);
	outtextxy(580, 10, ach_score);
}

/**************************************************************
Function: ach_judge
Description:�ɾ��жϺ���
Calls:
	 1.put_ach
Input:User0 *user,int ap��ƻ������,int ba���㽶����,int wa�������� ��,int score
Return:new_ach������ɵĳɾͣ�
Others��
1.�е���һ��ˮ��
2.�õ�50��
3.�õ�100��
4.�ܹ��е�150��ˮ��
5.�ܹ��е�500��ˮ��
6.�ܹ��е�1000��ˮ��
7.һ����Ϸ�е�11��ƻ��
8.һ����Ϸ�е�22���㽶
9.һ����Ϸ�е�33������
10.ȡ��һ��������߷�����ͬ�ķ���
***************************************************************/
int  ach_judge(User0* user, int ap, int ba, int wa, int score)
{
	int new_ach = 0;

	if (score > 0)
	{
		if (user->ach[0] == 0)
		{
			new_ach++;
		}
		user->ach[0] = 1;
	}

	if (score >= 50)
	{
		if (user->ach[1] == 0)
		{
			new_ach++;
		}
		user->ach[1] = 1;
	}

	if (score >= 100)
	{
		if (user->ach[2] == 0)
		{
			new_ach++;
		}
		user->ach[2] = 1;
	}

	if (user->total_fruits >= 150)
	{
		if (user->ach[3] == 0)
		{
			new_ach++;
		}
		user->ach[3] = 1;
	}

	if (user->total_fruits >= 500)
	{
		if (user->ach[4] == 0)
		{
			new_ach++;
		}
		user->ach[4] = 1;
	}

	if (user->total_fruits >= 1000)
	{
		if (user->ach[5] == 0)
		{
			new_ach++;
		}
		user->ach[5] = 1;
	}

	if (ap == 11)
	{
		if (user->ach[6] == 0)
		{
			new_ach++;
		}
		user->ach[6] = 1;
	}

	if (ba == 22)
	{
		if (user->ach[7] == 0)
		{
			new_ach++;
		}
		user->ach[7] = 1;
	}

	if (wa == 33)
	{
		if (user->ach[8] == 0)
		{
			new_ach++;
		}
		user->ach[8] = 1;
	}

	if (score == user->score[0] && score != 0)
	{
		if (user->ach[9] == 0)
		{
			new_ach++;
		}
		user->ach[9] = 1;
	}

	return new_ach;
}
/**************************************************************
Function: ach_judge2
Description:�ɾ��жϺ���
Calls:
	 1.put_ach
Input:User0* user, int ap, int ba, int wa, int bo, int st, int le, int peach, int pear, int score
Return:new_ach������ɵĳɾͣ�
Others��
11.�ֻ�ģʽ�е�ʮ��ը��
12.�ֻ�ģʽ�õ�50��
13.�ֻ�ģʽ�õ�100��
14.�ֻ�ģʽÿ��ˮ���Լ�ը�����е�һ��
15.ÿ�ѵ�������һ��
16.�鿴һ�ο�����־
***************************************************************/
int  ach_judge2(User0* user, int ap, int ba, int wa, int bo, int st, int le, int peach, int pear, int score)
{
	int new_ach;
	if (bo == 10)
	{
		if (user->ach[10] == 0)
		{
			new_ach++;
		}
		user->ach[10] = 1;
	}
	if (score >= 50)
	{
		if (user->ach[11] == 0)
		{
			new_ach++;
		}
		user->ach[11] = 1;
	}

	if (score >= 100)
	{
		if (user->ach[12] == 0)
		{
			new_ach++;
		}
		user->ach[12] = 1;
	}
	if (ap >= 1 && bo >= 1 && pear >= 1 && peach >= 1 && le >= 1 && wa >= 1 && st >= 1 && ba >= 1)
	{
		if (user->ach[13] == 0)
		{
			new_ach++;
		}
		user->ach[13] = 1;
	}
	return new_ach;
}

/**************************************************************
Function: put_ach
Description:���ɾ���һһд��
Calls:
Input:int ach_page,User0 *user
Return:new_ach������ɵĳɾͣ�
Others��
***************************************************************/
void put_ach(int ach_page, User0* user)
{
	switch (ach_page)
	{
	case 1://��һҳ
		//�ɾ�1
		if (user->ach[0] == 1)
		{
			puthz(252, 120, "����é®", 32, 32, WHITE);
			puthz(260, 160, "�е���һ��ˮ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 130, "5");
		}
		else
		{
			puthz(252, 120, "����é®", 32, 32, BLACK);
			puthz(260, 160, "�е���һ��ˮ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 130, "5");
		}
		//�ɾ�2
		if (user->ach[1] == 1)
		{
			puthz(252, 210, "С��ţ��", 32, 32, WHITE);
			puthz(280, 250, "�õ���ʮ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}
		else {
			puthz(252, 210, "С��ţ��", 32, 32, BLACK);
			puthz(280, 250, "�õ���ʮ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}

		if (user->ach[2] == 1)
		{
			puthz(252, 300, "��������", 32, 32, WHITE);
			puthz(280, 340, "�õ�һ�ٷ�", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 310, "10");
		}
		else {
			puthz(252, 300, "��������", 32, 32, BLACK);
			puthz(280, 340, "�õ�һ�ٷ�", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 310, "10");
		}

		if (user->ach[3] == 1)
		{
			puthz(252, 390, "ˮ��ɳ��", 32, 32, WHITE);
			puthz(240, 430, "�ܹ��е�һ����ʮ��ˮ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(252, 390, "ˮ��ɳ��", 32, 32, BLACK);
			puthz(240, 430, "�ܹ��е�һ����ʮ��ˮ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;

	case 2:
		if (user->ach[4] == 1)
		{
			puthz(252, 120, "ˮ����ʦ", 32, 32, WHITE);
			puthz(250, 160, "�ܹ��е���ٸ�ˮ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}
		else
		{
			puthz(252, 120, "ˮ����ʦ", 32, 32, BLACK);
			puthz(250, 160, "�ܹ��е���ٸ�ˮ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}

		if (user->ach[5] == 1)
		{
			puthz(252, 210, "ˮ��ɱ��", 32, 32, WHITE);
			puthz(250, 250, "�ܹ��е�һǧ��ˮ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 220, "20");
		}
		else {
			puthz(252, 210, "ˮ��ɱ��", 32, 32, BLACK);
			puthz(250, 250, "�ܹ��е�һǧ��ˮ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 220, "20");
		}

		if (user->ach[6] == 1)
		{
			puthz(265, 300, "�����", 32, 32, WHITE);
			puthz(235, 340, "һ����Ϸ�е�ʮһ��ƻ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		else {
			puthz(265, 300, "�����", 32, 32, BLACK);
			puthz(235, 340, "һ����Ϸ�е�ʮһ��ƻ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		if (user->ach[7] == 1)
		{
			puthz(265, 390, "�㽶��", 32, 32, WHITE);
			puthz(230, 430, "һ����Ϸ�е���ʮ�����㽶", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(265, 390, "�㽶��", 32, 32, BLACK);
			puthz(230, 430, "һ����Ϸ�е���ʮ�����㽶", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;

	case 3:
		if (user->ach[8] == 1)
		{
			puthz(252, 120, "�Թ�Ⱥ��", 32, 32, WHITE);
			puthz(230, 160, "һ����Ϸ�е���ʮ��������", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}
		else {
			puthz(252, 120, "�Թ�Ⱥ��", 32, 32, BLACK);
			puthz(230, 160, "һ����Ϸ�е���ʮ��������", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}

		if (user->ach[9] == 1)
		{
			puthz(252, 210, "������ʶ", 32, 32, WHITE);
			puthz(220, 250, "ȡ��һ��������߷�����ͬ�ķ���", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 220, "20");
		}
		else {
			puthz(252, 210, "������ʶ", 32, 32, BLACK);
			puthz(220, 250, "ȡ��һ��������߷�����ͬ�ķ���", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 220, "20");
		}

		if (user->ach[10] == 1)
		{
			puthz(252, 300, "��ר��", 32, 32, WHITE);
			puthz(230, 340, "�ֻ�ģʽ�е�ʮ��ը��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		else {
			puthz(252, 300, "��ר��", 32, 32, BLACK);
			puthz(230, 340, "�ֻ�ģʽ�е�ʮ��ը��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}

		if (user->ach[11] == 1)
		{
			puthz(252, 390, "���Խֻ�", 32, 32, WHITE);
			puthz(240, 430, "�ֻ�ģʽ�õ���ʮ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(252, 390, "���Խֻ�", 32, 32, BLACK);
			puthz(240, 430, "�ֻ�ģʽ�õ���ʮ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;

	case 4:

		if (user->ach[12] == 1)
		{
			puthz(252, 120, "�ֻ�����", 32, 32, WHITE);
			puthz(240, 160, "�ֻ�ģʽ�õ�һ�ٷ�", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}
		else {
			puthz(252, 120, "�ֻ�����", 32, 32, BLACK);
			puthz(240, 160, "�ֻ�ģʽ�õ�һ�ٷ�", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}

		if (user->ach[13] == 1)
		{
			puthz(252, 210, "���ӻ�", 32, 32, WHITE);
			puthz(200, 250, "�ֻ�ģʽÿ��ˮ���Լ�ը�����е�һ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}
		else {
			puthz(252, 210, "���ӻ�", 32, 32, BLACK);
			puthz(200, 250, "�ֻ�ģʽÿ��ˮ���Լ�ը�����е�һ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}

		if (user->ach[14] == 1)
		{
			puthz(260, 300, "����", 32, 32, WHITE);
			puthz(230, 340, "����һ����������", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		else {
			puthz(260, 300, "����", 32, 32, BLACK);
			puthz(230, 340, "����һ����������", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}

		if (user->ach[15] == 1)
		{
			puthz(252, 390, "������", 32, 32, WHITE);
			puthz(230, 430, "�鿴һ�ο�����־", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(252, 390, "������", 32, 32, BLACK);
			puthz(230, 430, "�鿴һ�ο�����־", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;
		
	case 5:
		if (user->ach[16] == 1)
		{
			puthz(252, 120, "СС����", 32, 32, WHITE);
			//puthz(240, 160, "�ֻ�ģʽ�õ�һ�ٷ�", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}
		else {
			puthz(252, 120, "СС����", 32, 32, BLACK);
			//puthz(240, 160, "�ֻ�ģʽ�õ�һ�ٷ�", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(520, 130, "10");
		}

		if (user->ach[17] == 1)
		{
			puthz(252, 210, "����", 32, 32, WHITE);
			//puthz(200, 250, "�ֻ�ģʽÿ��ˮ���Լ�ը�����е�һ��", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}
		else {
			puthz(252, 210, "����", 32, 32, BLACK);
			//puthz(200, 250, "�ֻ�ģʽÿ��ˮ���Լ�ը�����е�һ��", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 220, "5");
		}

		if (user->ach[18] == 1)
		{
			puthz(260, 300, "����", 32, 32, WHITE);
			//puthz(230, 340, "����һ����������", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}
		else {
			puthz(260, 300, "����", 32, 32, BLACK);
			//puthz(230, 340, "����һ����������", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 310, "5");
		}

		if (user->ach[19] == 1)
		{
			puthz(252, 390, "��ʤ��", 32, 32, WHITE);
			//puthz(230, 430, "�鿴һ�ο�����־", 16, 16, WHITE);
			setcolor(WHITE);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		else {
			puthz(252, 390, "��ʤ��", 32, 32, BLACK);
			//puthz(230, 430, "�鿴һ�ο�����־", 16, 16, BLACK);
			setcolor(BLACK);
			settextstyle(0, HORIZ_DIR, 4);
			outtextxy(540, 400, "5");
		}
		break;
	}
}
/**************************************************************
Function: change_achscore
Description:�ı�ṹ����ķ���
Calls:
Input:User0 *user
Return:
Others��
***************************************************************/
void change_achscore(User0 *user)
{
		int i;
		user->score[2] = 0;
		for (i = 0; i < 20; i++)
		{
			user->score[2] = user->score[2] + user->ach[i] * 5;
		}
		if (user->ach[2] == 1)
		{
			user->score[2] = user->score[2] + 5;
		}
		if (user->ach[4] == 1)
		{
			user->score[2] = user->score[2] + 5;
		}
		if (user->ach[8] == 1)
		{
			user->score[2] = user->score[2] + 5;
		}
		if (user->ach[12] == 1)
		{
			user->score[2] = user->score[2] + 5;
		}
		if (user->ach[5] == 1)
		{
			user->score[2] = user->score[2] + 15;
		}
		if (user->ach[9] == 1)
		{
			user->score[2] = user->score[2] + 15;
		}
}







