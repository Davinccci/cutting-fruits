/**************************************************************
Filename：input.c   Author: 田铭   Version:1.0   Date:10.19
Description:该文件包含了实现登录、注册的相关函数
Function List:
	1.Log//成就页面的”主函数“，负责调用其他函数
	2.Reg//成就页面的画图函数
	3.Input//成就判断函数
History： 10.22写注释
<author>  <time> <version> <desc>
田铭    19/10/19  1.0    build this module
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
Description:进行登录功能
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
	puthz(210, 70, "水果忍者", 48, 64, WHITE);
	drawtextput(200, 200);
	drawtextput(200, 265);
	drawoutbutton(200, 390, LIGHTCYAN);
	drawoutbutton(380, 390, LIGHTCYAN);
	puthz(110, 205, "用户名", 16, 16, BLACK);
	puthz(110, 270, "密码", 16, 16, BLACK);
	puthz(214, 400, "登录", 16, 16, BLACK);
	puthz(394, 400, "退出", 16, 16, BLACK);
	MouseOn(MouseX, MouseY);
	sta = 2;
	while (1)
	{
		MouseDelay(3);
		switch (sta)
		{
		case 0: {                //退出
			wsta = 1;
			free(name);
			name = NULL;
			free(pass);
			pass = NULL;
			break;
		}
		case 1: {                        //登录
			strcpy(user->username, name);
			strcpy(user->password, pass);
			ssta = SearchUser(*user);
			if (ssta != 0)               //登录成功
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
				sta = 2;                  //匹配失败，重新进行登录
				MouseOff();
				drawtextput(200, 200);
				drawtextput(200, 265);
				s = imagesize(499,209,639,230);
				buffer = malloc(s);
				getimage(499,209,639,230,buffer);
				puthz(500, 210, "用户名密码不匹配", 16, 16, WHITE);
				delay(1000);
				//puthz(500, 210, "用户名密码不匹配", 16, 16, BROWN);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				MouseOn(MouseX, MouseY);
			}

			break;
		}
		case 2: {                       //输入用户名
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
				puthz(500, 210, "请输入用户名", 16, 16, WHITE);
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
				puthz(500, 275, "请输入密码", 16, 16, WHITE);
				delay(2000);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 275, "请输入密码", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
			}
			break;
		}
		case 3: {                       //输入密码
			pass[0] = '\0';
			Input(pass, 1, &sta, 150, 205);
			n = strlen(pass);
			if (sta == 0)
			{
				break;
			}

			break;
		}
		case 4: {                      //进行登录功能
			strcpy(user->username, name);
			strcpy(user->password, pass);
			ssta = SearchUser(*user);
			if (ssta != 0)              //登录成功
			{					   
				free(name);
				name = NULL;
				free(pass);
				pass = NULL;
				wsta = 2;
			}
			else                      //登录失败，重新进行登录
			{
				sta = 2;
				MouseOff();
				s = imagesize(499,209,639,239);
				buffer = malloc(s);
				getimage(499,209,639,239,buffer);
				drawtextput(200, 200);
				drawtextput(200, 265);
				puthz(500, 210, "用户名密码不匹配", 16, 16, WHITE);
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
Description:进行注册功能
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
	puthz(210, 70, "水果忍者", 48, 64, WHITE);
	drawtextput(200, 200);
	drawtextput(200, 265);
	drawtextput(200, 330);
	drawoutbutton(200, 390, LIGHTCYAN);
	drawoutbutton(380, 390, LIGHTCYAN);
	puthz(110, 205 + 5, "用户名", 16, 16, BLACK);
	puthz(110, 270 + 5, "密码", 16, 16, BLACK);
	puthz(110, 335 + 5, "重复密码", 16, 16, BLACK);
	puthz(214, 400, "注册", 16, 16, BLACK);
	puthz(394, 400, "退出", 16, 16, BLACK);
	MouseOn(MouseX, MouseY);
	sta = 2;
	while (1)
	{
		MouseDelay(3);
		switch (sta)
		{
		case 0: {              //点击退出
			wsta = 1;
			free(name);
			name = NULL;
			free(pass);
			pass = NULL;
			free(repass);
			repass = NULL;
			break;
		}
		case 1: {               //注册成功
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
		case 2: {                 //输入用户名
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
				
				puthz(500, 210, "用户名应多于四位", 16, 16, WHITE);
				delay(1000);
				//puthz(500, 210, "用户名应多于四位", 16, 16, BROWN);
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
				puthz(500, 210, "该账户已存在", 16, 16, WHITE);
				delay(1000);
				putimage(499,209,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 210, "该账户已存在", 16, 16, BROWN);
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
				puthz(500, 275, "请输入密码", 16, 16, WHITE);
				delay(1000);
				putimage(499,274,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 275, "请输入密码", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
				break;
			}
			break;
		}
		case 3: {                 //输入密码
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
				
				puthz(500, 275, "密码应多于四位", 16, 16, WHITE);
				delay(1000);
				putimage(499,274,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 275, "密码应多于四位", 16, 16, BROWN);
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
				
				puthz(500, 340, "请再次输入密码", 16, 16, WHITE);
				delay(1000);
				putimage(499,339,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 340, "请再次输入密码", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
				break;
			}
			break;

		}
		case 4: {                      //重复密码
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
				puthz(500, 340, "输入密码不一致", 16, 16, WHITE);
				delay(1000);
				putimage(499,339,buffer,COPY_PUT);
				free(buffer);
				buffer = NULL;
				//puthz(500, 340, "输入密码不一致", 16, 16, BROWN);
				MouseOn(MouseX, MouseY);
				break;
			}

		}
		case 5: {                         //进行注册
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
Description:进行输入功能，同时将输入的字符存入字符串
Calls:
	 1.VLine
	 2.MouseOff
	 3.MouseOn
	 4.Put_Asc16_Size
Input:char* str, int n, int* sta, int xx, int yy
Return:
Others:n=0 表示输入用户名       n=1  表示输入密码
       xx yy 表示字符输入的起始坐标
       sta 返回状态
***************************************************************/
void Input(char* str, int n, int* sta, int xx, int yy)
{
	int i, mx, my, judgeN, add = 0, m, nn = 0, nnn = 0;
	char zm;
	fflush(stdin);    //清空输入缓冲区
	i = 0;
	if (n != 0)
		add = 5;
	m = 10 + add;
	while (kbhit())     //kbhit()函数（conio.h）：检查当前是否有键盘输入，若有则返回一个非0值，否则返回0。
	{                  //是非阻塞函数，检测到用户按下某键时就会返回
		bioskey(0);    // 清除键盘缓冲区
	}
	while (1)
	{
		MouseDelay(2);
		nn += 1;
		if (nn == 25)         //缓冲的
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
							MouseOff();//消去鼠标
							VLine((xx + 10 * i + 82), yy + 66, yy + 89);
							MouseOn(MouseX, MouseY);//画鼠标
							nnn = 0;
						}
						MouseOff();//消去鼠标
						Put_Asc16_Size(xx + 80 + 10 * i, yy + 70, 1, 1, '*', BLACK);
						MouseOn(MouseX, MouseY);//画鼠标
					}
					else if (n == 2)
					{
						if (nnn == 1)
						{
							MouseOff();//消去鼠标
							VLine((xx + 10 * i + 82), yy + 70, yy + 93);
							MouseOn(MouseX, MouseY);//画鼠标
							nnn = 0;
						}
						MouseOff();//消去鼠标
						Put_Asc16_Size(xx + 80 + 10 * i, yy + 75, 1, 1, '*', BLACK);
						MouseOn(MouseX, MouseY);//画鼠标
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
						MouseOff();//消去鼠标
						Put_Asc16_Size(xx + 80 + 17 * i, yy, 2, 2, str[i], CYAN);
						setcolor(CYAN);
						line((xx + 17 * i + 99), yy + 5, (xx + 17 * i + 99), yy + 28);
						MouseOn(MouseX, MouseY);//画鼠标
					}
					else if (n == 1)
					{
						MouseOff();//消去鼠标
						Put_Asc16_Size(xx + 80 + 10 * i, yy + 70, 1, 1, '*', CYAN);
						setcolor(CYAN);
						line((xx + 10 * i + 92), yy + 66, (xx + 10 * i + 92), yy + 89);
						MouseOn(MouseX, MouseY);//画鼠标
					}
					else if (n == 2)
					{
						MouseOff();//消去鼠标
						Put_Asc16_Size(xx + 80 + 10 * i, yy + 75, 1, 1, '*', CYAN);
						setcolor(CYAN);
						line((xx + 10 * i + 92), yy + 70, (xx + 10 * i + 92), yy + 93);
						MouseOn(MouseX, MouseY);//画鼠标
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
			else if (mx < 440 && mx>380 && my > 390 && my < 425)//点击退出
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

