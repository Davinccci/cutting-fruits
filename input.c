/**************************************************************
Filename��input.c   Author: ����   Version:1.0   Date:10.19
Description:���ļ�������ʵ�ֵ�¼��ע�����غ���
Function List:
	1.Log//�ɾ�ҳ��ġ��������������������������
	2.Reg//�ɾ�ҳ��Ļ�ͼ����
	3.Input//�ɾ��жϺ���
History�� 10.22дע��
<author>  <time> <version> <desc>
����    19/10/19  1.0    build this module
***************************************************************/

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include"user.h"
#include"login.h"
#include"hz1.h"
#include"hz.h"
#include"common.h"
#include "fruits.h"
#include"mouse.h"

/**************************************************************
Function:Log
Description:���е�¼����
Calls:
	 1.puthz
	 2.MouseOn
	 3.Input
	 4.MouseOff
	 5.SearchUser
	 6.bkground
Input:User0 *user
Return:wsta
Others:
***************************************************************/
int Log(User* user)
{
	void *buffer = NULL;
	unsigned s;
	char* name = NULL;
	char* pass = NULL;
	int n, sta, ssta, wsta = 0;
	name = (char*)malloc(20 * sizeof(char));
	pass = (char*)malloc(20 * sizeof(char));
	cleardevice();
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, BROWN);
	MouseOff();
	bar(0, 0, 640, 480);
	bkground();
	puthz(210, 70, "ˮ������", 48, 64, WHITE);
	drawtextput(200, 200);
	drawtextput(200, 265);
	drawoutbutton(200, 390, LIGHTCYAN);
	drawoutbutton(380, 390, LIGHTCYAN);
	puthz(110, 205, "�û���", 16, 16, BLACK);
	puthz(110, 270, "����", 16, 16, BLACK);
	puthz(214, 400, "��¼", 16, 16, BLACK);
	puthz(394, 400, "�˳�", 16, 16, BLACK);
	MouseOn(MouseX, MouseY);
	sta = 2;
	while (1)
	{
		MouseDelay(3);
		switch (sta)
		{
		case 0: {                //�˳�
			wsta = 1;
			free(name);
			name = NULL;
			free(pass);
			pass = NULL;
			break;
		}
		case 1: {                        //��¼
			strcpy(user->username, name);
			strcpy(user->password, pass);
			ssta = SearchUser(*user);
			if (ssta != 0)               //��¼�ɹ�
			{
				//  Choose(); 					   
				free(name);
				name = NULL;
				free(pass);
				pass = NULL;
				wsta = 2;
			}
			else
			{
				sta = 2;                  //ƥ��ʧ�ܣ����½��е�¼
				MouseOff();
				drawtextput(200, 200);
				drawtextput(200, 265);
				s = imagesize(499,209,639,230);
				buffer = malloc(s);
				getimage(499,209,639,230,buffer);
				puthz(500, 210, "�û������벻ƥ��", 16, 16, WHITE);
				delay(1000);
				//puthz(500, 210, "�û������벻ƥ��", 16, 16, BROWN);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				MouseOn(MouseX, MouseY);
			}

			break;
		}
		case 2: {                       //�����û���
			name[0] = '\0';
			Input(name, 0, &sta, 150, 200);
			n = strlen(name);
			if (sta == 0)
			{
				break;
			}
			if (n < 1)
			{
				sta = 2;
				MouseOff();
				s = imagesize(499,209,639,230);
				buffer = malloc(s);
				getimage(499,209,639,230,buffer);
				puthz(500, 210, "�������û���", 16, 16, WHITE);
				delay(1000);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				MouseOn(MouseX, MouseY);
				break;
			}

			if (sta == 1)
			{
				sta = 3;
				MouseOff();
				s = imagesize(499,274,639,304);
				buffer = malloc(s);
				getimage(499,274,639,304,buffer);
				puthz(500, 275, "����������", 16, 16, WHITE);
				delay(2000);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 275, "����������", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
			}
			break;
		}
		case 3: {                       //��������
			pass[0] = '\0';
			Input(pass, 1, &sta, 150, 205);
			n = strlen(pass);
			if (sta == 0)
			{
				break;
			}

			break;
		}
		case 4: {                      //���е�¼����
			strcpy(user->username, name);
			strcpy(user->password, pass);
			ssta = SearchUser(*user);
			if (ssta != 0)              //��¼�ɹ�
			{					   
				free(name);
				name = NULL;
				free(pass);
				pass = NULL;
				wsta = 2;
			}
			else                      //��¼ʧ�ܣ����½��е�¼
			{
				sta = 2;
				MouseOff();
				s = imagesize(499,209,639,239);
				buffer = malloc(s);
				getimage(499,209,639,239,buffer);
				drawtextput(200, 200);
				drawtextput(200, 265);
				puthz(500, 210, "�û������벻ƥ��", 16, 16, WHITE);
				delay(1000);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				MouseOn(MouseX, MouseY);
			}

			break;

		}
		default:break;
		}
		if (wsta != 0)
			break;
	}
	return wsta;
}

/**************************************************************
Function:Reg
Description:����ע�Ṧ��
Calls:
	 1.puthz
	 2.MouseOn
	 3.Input
	 4.MouseOff
	 5.SearchName
	 6.bkground
Input:User0 *user
Return:wsta
Others:
***************************************************************/
int Reg(User* user)
{
	void *buffer = NULL;
	unsigned s;
	char* name = NULL;
	char* pass = NULL;
	char* repass = NULL;	
	int n, sta, wsta = 0;
	name = (char*)malloc(20 * sizeof(char));
	pass = (char*)malloc(20 * sizeof(char));
	repass = (char*)malloc(20 * sizeof(char));
	cleardevice();
	MouseOff();
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 0, 640, 480);
	bkground();
	puthz(210, 70, "ˮ������", 48, 64, WHITE);
	drawtextput(200, 200);
	drawtextput(200, 265);
	drawtextput(200, 330);
	drawoutbutton(200, 390, LIGHTCYAN);
	drawoutbutton(380, 390, LIGHTCYAN);
	puthz(110, 205 + 5, "�û���", 16, 16, BLACK);
	puthz(110, 270 + 5, "����", 16, 16, BLACK);
	puthz(110, 335 + 5, "�ظ�����", 16, 16, BLACK);
	puthz(214, 400, "ע��", 16, 16, BLACK);
	puthz(394, 400, "�˳�", 16, 16, BLACK);
	MouseOn(MouseX, MouseY);
	sta = 2;
	while (1)
	{
		MouseDelay(3);
		switch (sta)
		{
		case 0: {              //����˳�
			wsta = 1;
			free(name);
			name = NULL;
			free(pass);
			pass = NULL;
			free(repass);
			repass = NULL;
			break;
		}
		case 1: {               //ע��ɹ�
			wsta = 2;
			strcpy(user->username, name);
			strcpy(user->password, pass);
			free(name);
			name = NULL;
			free(pass);
			pass = NULL;
			free(repass);
			repass = NULL;
			break;
		}
		case 2: {                 //�����û���
			name[0] = '\0';
			Input(name, 0, &sta, 150, 200);
			if (sta == 0)
			{
				break;
			}
			n = strlen(name);
			if (n < 4)
			{
				sta = 2;
				MouseOff();
				drawtextput(200, 200);
				s = imagesize(499,209,639,230);
				buffer = malloc(s);
				getimage(499,209,639,230,buffer);
				
				puthz(500, 210, "�û���Ӧ������λ", 16, 16, WHITE);
				delay(1000);
				//puthz(500, 210, "�û���Ӧ������λ", 16, 16, BROWN);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				MouseOn(MouseX, MouseY);
			}
			strcpy(user->username, name);
			if (SearchName(*user) != 0)
			{
				sta = 2;
				MouseOff();
				drawtextput(200, 200);
				s = imagesize(499,209,639,230);
				buffer = malloc(s);
				getimage(499,209,639,230,buffer);
				puthz(500, 210, "���˻��Ѵ���", 16, 16, WHITE);
				delay(1000);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 210, "���˻��Ѵ���", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
				break;
			}
			if (sta == 1)
			{
				sta = 3;
				MouseOff();
				s = imagesize(499,274,639,295);
				buffer = malloc(s);
				getimage(499,274,639,295,buffer);
				puthz(500, 275, "����������", 16, 16, WHITE);
				delay(1000);
				putimage(499,274,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 275, "����������", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
				break;
			}
			break;
		}
		case 3: {                 //��������
			pass[0] = '\0';
			Input(pass, 1, &sta, 150, 205);
			if (sta == 0)
			{
				break;
			}
			strcpy(user->password, pass);
			n = strlen(pass);
			if (n < 4)
			{
				sta = 3;
				MouseOff();
				drawtextput(200, 265);
				s = imagesize(499,274,639,295);
				buffer = malloc(s);
				getimage(499,274,639,295,buffer);
				
				puthz(500, 275, "����Ӧ������λ", 16, 16, WHITE);
				delay(1000);
				putimage(499,274,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 275, "����Ӧ������λ", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
				break;
			}
			if (sta == 1)
			{
				sta = 4;
				MouseOff();
				s = imagesize(499,339,639,360);
				buffer = malloc(s);
				getimage(499,339,639,360,buffer);
				
				puthz(500, 340, "���ٴ���������", 16, 16, WHITE);
				delay(1000);
				putimage(499,339,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 340, "���ٴ���������", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
				break;
			}
			break;

		}
		case 4: {                      //�ظ�����
			repass[0] = '\0';
			Input(repass, 2, &sta, 150, 265);
			if (sta == 0)
			{
				break;
			}
			if (strcmp(pass, repass) != 0)
			{
				sta = 3;
				MouseOff();
				s = imagesize(499,339,639,360);
				buffer = malloc(s);
				getimage(499,339,639,360,buffer);
				drawtextput(200, 265);
				drawtextput(200, 330);
				puthz(500, 340, "�������벻һ��", 16, 16, WHITE);
				delay(1000);
				putimage(499,339,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 340, "�������벻һ��", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
				break;
			}

		}
		case 5: {                         //����ע��
			wsta = 2;
			strcpy(user->username, name);
			strcpy(user->password, pass);
			free(name);
			name = NULL;
			free(pass);
			pass = NULL;
			free(repass);
			repass = NULL;
			break;
		}
		default:break;
		}
		if (wsta != 0)
			break;
	}
	return wsta;
}

/**************************************************************
Function:Input
Description:�������빦�ܣ�ͬʱ��������ַ������ַ���
Calls:
	 1.VLine
	 2.MouseOff
	 3.MouseOn
	 4.Put_Asc16_Size
Input:char* str, int n, int* sta, int xx, int yy
Return:
Others:n=0 ��ʾ�����û���       n=1  ��ʾ��������
       xx yy ��ʾ�ַ��������ʼ����
       sta ����״̬
***************************************************************/
void Input(char* str, int n, int* sta, int xx, int yy)
{
	int i, mx, my, judgeN, add = 0, m, nn = 0, nnn = 0;
	char zm;
	fflush(stdin);    //������뻺����
	i = 0;
	if (n != 0)
		add = 5;
	m = 10 + add;
	while (kbhit())     //kbhit()������conio.h������鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0��
	{                  //�Ƿ�������������⵽�û�����ĳ��ʱ�ͻ᷵��
		bioskey(0);    // ������̻�����
	}
	while (1)
	{
		MouseDelay(2);
		nn += 1;
		if (nn == 25)         //�����
		{
			nnn++;
			nnn = nnn % 2;
			if (n == 0)
			{
				MouseOff();
				VLine((xx + 17 * i + 82), yy + 5, yy + 28);
				MouseOn(MouseX, MouseY);

			}
			else if (n == 1)
			{
				MouseOff();
				VLine((xx + 10 * i + 82), yy + 66, yy + 89);
				MouseOn(MouseX, MouseY);
			}
			else if (n == 2)
			{
				MouseOff();
				VLine((xx + 10 * i + 82), yy + 70, yy + 93);
				MouseOn(MouseX, MouseY);
			}
			nn = 0;
		}
		judgeN = 0;
		if (kbhit() != 0)
		{
			zm = getch();
			if ((zm >= 'a' && zm <= 'z') || (zm >= 'A' && zm <= 'Z') || (zm >= '0' && zm <= '9'))
			{
				if (i <= m)
				{
					str[i] = zm;
					str[i + 1] = '\0';
					if (n == 0)
					{
						if (nnn == 1)
						{
							MouseOff();
							VLine((xx + 17 * i + 82), yy + 5, yy + 28);
							MouseOn(MouseX, MouseY);
							nnn = 0;
						}
						MouseOff();
						Put_Asc16_Size(xx + 80 + 17 * i, yy, 2, 2, zm, BLACK);
						MouseOn(MouseX, MouseY);
					}
					else if (n == 1)
					{
						if (nnn == 1)
						{
							MouseOff();//��ȥ���
							VLine((xx + 10 * i + 82), yy + 66, yy + 89);
							MouseOn(MouseX, MouseY);//�����
							nnn = 0;
						}
						MouseOff();//��ȥ���
						Put_Asc16_Size(xx + 80 + 10 * i, yy + 70, 1, 1, '*', BLACK);
						MouseOn(MouseX, MouseY);//�����
					}
					else if (n == 2)
					{
						if (nnn == 1)
						{
							MouseOff();//��ȥ���
							VLine((xx + 10 * i + 82), yy + 70, yy + 93);
							MouseOn(MouseX, MouseY);//�����
							nnn = 0;
						}
						MouseOff();//��ȥ���
						Put_Asc16_Size(xx + 80 + 10 * i, yy + 75, 1, 1, '*', BLACK);
						MouseOn(MouseX, MouseY);//�����
					}
					i++;
				}
			}
			if (zm == Back)
			{
				if (i > 0)
				{
					i--;
					if (n == 0)
					{
						MouseOff();//��ȥ���
						Put_Asc16_Size(xx + 80 + 17 * i, yy, 2, 2, str[i], CYAN);
						setcolor(CYAN);
						line((xx + 17 * i + 99), yy + 5, (xx + 17 * i + 99), yy + 28);
						MouseOn(MouseX, MouseY);//�����
					}
					else if (n == 1)
					{
						MouseOff();//��ȥ���
						Put_Asc16_Size(xx + 80 + 10 * i, yy + 70, 1, 1, '*', CYAN);
						setcolor(CYAN);
						line((xx + 10 * i + 92), yy + 66, (xx + 10 * i + 92), yy + 89);
						MouseOn(MouseX, MouseY);//�����
					}
					else if (n == 2)
					{
						MouseOff();//��ȥ���
						Put_Asc16_Size(xx + 80 + 10 * i, yy + 75, 1, 1, '*', CYAN);
						setcolor(CYAN);
						line((xx + 10 * i + 92), yy + 70, (xx + 10 * i + 92), yy + 93);
						MouseOn(MouseX, MouseY);//�����
					}
					str[i] = '\0';
				}
			}
			if (zm == Enter)
			{
				setcolor(CYAN);
				line((150 + 17 * i + 82), 200 + 5, (150 + 17 * i + 82), 205 + 26);
				line((150 + 10 * i + 82), 205 + 66, (150 + 10 * i + 82), 205 + 89);
				judgeN = 1;
				*sta = *sta + 1;
			}
			if (zm == Esc)
			{
				judgeN = 1;
				*sta = 0;
			}
		}

		if (LeftPress())
		{

			MouseGetXY(&mx, &my);
			if (mx > 200 && my > 390 && mx < 260 && my < 425)
			{
				setcolor(CYAN);
				line((150 + 17 * i + 82), 200 + 5, (150 + 17 * i + 82), 205 + 26);
				line((150 + 10 * i + 82), 205 + 66, (150 + 10 * i + 82), 205 + 89);
				*sta = 1;
				break;
			}
			else if (mx < 440 && mx>380 && my > 390 && my < 425)//����˳�
			{
				*sta = 0;
				break;
			}
		}
		if (judgeN != 0)
		{
			break;
		}
	}
}

