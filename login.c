/**************************************************************
Filename��login.c   Author: ����   Version:1.0   Date:10.19
Description:���ļ������˵�¼ע��������غ���
Function List:
	1.LogIn//��¼ע��ҳ��ġ���ʼ���ƺ�����
	2.Choose//��¼ע��������������������ƺ͵�����������
	3.SignIn//��¼���������ƺͽ��е�¼����
	4.SignUp//ע�ắ�������ƺͽ���ע�Ṧ��
History�� 10.22дע��
<author>  <time> <version> <desc>
����    19/10/19  1.0    build this module
***************************************************************/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<stdlib.h>
#include <graphics.h>
#include "login.h"
#include "mouse.h"
#include "hz.h"
#include "fruits.h"
#include "hz1.h"
#include "user.h"
#include  "main.h"
#include "common.h"
#include "fruits.h"


/**************************************************************
Function:LogIn
Description:��¼ע��ҳ��ġ���ʼ���ƺ�����
Calls:
	 1.Choose
	 2.bkground
	 3.strawberry
Input:User0* p
Return:
Others:
***************************************************************/
void LogIn(User0* p)
{

	setbkcolor(BROWN);
	bkground();
	puthz(210, 70, "ˮ������", 48, 64, WHITE);
	strawberry(140, 190);//li han shu
	strawberry(140, 290);//li han shu
	Choose(p);
}


/**************************************************************
Function:Choose
Description:���ƣ�����ѡ��
Calls:
	 1.MouseOn
	 2.bkground
	 3.strawberry
	 4.MouseDelay
	 5.draw_exit_button
	 6.MouseOff
	 7.MouseGetXY
	 8.drawbutton
	 9.SignIn
	 10.SignUp
Input:User0* p
Return:
Others:
***************************************************************/
void Choose(User0* p)
{
	int x0, y0;
	int i, j, k, sta;
	int exit_status = 0;
	Button button[3];
	Button* but = NULL;
	but = button;
	button[0].x1 = 260;
	button[0].y1 = 220;
	button[0].x2 = 400;
	button[0].y2 = 280;
	button[1].x1 = 260;
	button[1].y1 = 320;
	button[1].x2 = 400;
	button[1].y2 = 380;
	button[0].btcolor1 = LIGHTGRAY;
	button[0].btcolor2 = CYAN;
	button[1].btcolor1 = LIGHTGRAY;
	button[1].btcolor2 = LIGHTGREEN;
	MouseOff();
	button[0].status = 0;
	button[1].status = 0;
	cleardevice();
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, BROWN);
	MouseOff();
	bar(0, 0, 640, 480);
	bkground();
	puthz(210, 70, "ˮ������", 48, 64, WHITE);//li han shu
	strawberry(140, 190);//li han shu
	strawberry(140, 290);
	MouseOn(MouseX, MouseY);
	MouseOff();
	for (i = 0; i < 2; i++)
	{
		drawbutton(but + i);
	}
	draw_exit_button(0);
	puthz(300, 230, "ע��", 32, 32, CYAN);
	puthz(300, 330, "��¼", 32, 32, LIGHTGREEN);
	MouseOn(MouseX, MouseY);
	while (1)
	{
		MouseDelay(3);
		MouseGetXY(&x0, &y0);

		/*****************
		�������ɫ
		������ָ�
		*****************/
		if(mouse_press(260, 210, 460, 280) == 2)
		{
			if (button[0].status!= 2)
			{
				MouseOff();
				button[0].status=2;
				drawbutton(&button[0]);
				puthz(300, 230, "ע��", 32, 32, LIGHTGRAY);
				MouseOn(MouseX, MouseY);
			}
		}
		if(mouse_press(260, 210, 460, 280) == 1)
		{
			if (button[0].status!= 1)
			{
				MouseOff();
				button[0].status=1;
				drawbutton(&button[0]);
				puthz(300, 230, "ע��", 32, 32, LIGHTGRAY);
				MouseOn(MouseX, MouseY);
				delay(100);
				sta = 2;
				break;
			}
		}
		if(mouse_press(260, 210, 460, 280) == 0)
		{
			if (button[0].status!= 0)
			{
				MouseOff();
				button[0].status=0;
				drawbutton(&button[0]);
				puthz(300, 230, "ע��", 32, 32, CYAN);
				MouseOn(MouseX, MouseY);
			}
		}
		
		if(mouse_press(260, 310, 460, 380) == 2)
		{
			if (button[1].status!= 2)
			{
				MouseOff();
				button[1].status=2;
				drawbutton(&button[1]);
				puthz(300, 330, "��¼", 32, 32, LIGHTGRAY);
				MouseOn(MouseX, MouseY);
			}
		}
		if(mouse_press(260, 310, 460, 380) == 1)
		{
			if (button[1].status!= 1)
			{
				MouseOff();
				button[1].status=1;
				drawbutton(&button[1]);
				puthz(300, 330, "��¼", 32, 32, LIGHTGRAY);
				MouseOn(MouseX, MouseY);
				delay(100);
				sta = 1;
				break;
			}
		}
		if(mouse_press(260, 310, 460, 380) == 0)
		{
			if (button[1].status!= 0)
			{
				MouseOff();
				button[1].status=0;
				drawbutton(&button[1]);
				puthz(300, 330, "��¼", 32, 32, LIGHTGREEN);
				MouseOn(MouseX, MouseY);
			}
		}
		
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
			sta =3;
			break;
		}
		if (mouse_press(0, 435, 50, 475) == 0)
		{
			if (exit_status != 0)
			{
				draw_exit_button(0);
				exit_status = 0;
			}
		}
		
	}
	switch (sta)
	{
	case 1:
	{
		SignIn(p);             //��¼
		break;
	}
	case 2:
	{
		SignUp(p);	          //ע��
		break;
	}
	case 3:
	{
		exit(0);            //�˳�
		break;
	}
	default:   break;
	}

}


/**************************************************************
Function:SignIn
Description:��¼���������ƺͽ��е�¼����
Calls:
	 1.Choose
	 2.Log
Input:User0* p
Return:
Others:
***************************************************************/
void SignIn(User0* p)
{
	User user;
	int  ssta = 0;
	int i;
	ssta = Log(&user);
	strcpy((*p).ID, user.username);
	strcpy((*p).key, user.password);
	if (ssta == 1)
	{
		Choose(p);
	}
}

/**************************************************************
Function:SignUp
Description:ע�ắ�������ƺͽ���ע�Ṧ��
Calls:
	 1.Choose
	 2.Reg
	 3.AddUser
Input:User0* p
Return:
Others:
***************************************************************/
void SignUp(User0* p)
{
	User user;
	int sta = 0;
	sta = Reg(&user);
	if (sta == 2)
	{
		AddUser(user);
		Choose(p);
	}
	if (sta == 1)
	{
		Choose(p);
	}
}
